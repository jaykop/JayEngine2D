#include "World.h"
#include <hash_map>
#include "../ObjectManager/ObjectManager.h"
#include "../Graphic/Sprite.h"
#include "../Physics/RigidBody.h"
#include "../Math/MathUtils.h"

World::World()
{

}

World::~World()
{

}

void World::Init()
{

}

void World::Update(ObjectManager& objM)
{
	//Works each bodies' physics
	for (auto it1 = objM.GetList().begin(); it1 != objM.GetList().end(); ++it1)
	{
		if (it1->second->HasRigidBody())
		{
			BodyPipeline(it1->second);

			//Colision Checker
			auto next = it1;
			for (auto it2 = ++next; it2 != objM.GetList().end(); ++it2)
			{
				//If both objs are same, or one of body has no body, 
				//then skip to check.
				if (it1 != it2 && it2->second->HasRigidBody())
				{
					if (CollisionIntersect(it1->second, it2->second))
						CollisionResponse(it1->second, it2->second);
				}
			}
		}
	}
}

void World::Shutdown()
{

}

bool World::CollisionIntersect(Sprite* spt1, Sprite* spt2)
{
	//Get rectangle;s vertices
	Vertices body1 = GetVertices(spt1);
	Vertices body2 = GetVertices(spt2);

	float body1_min = 0, body1_max = 0;
	float body2_min = 0, body2_max = 0;

	//Calculate 1st body's edges
	for (int index = 0; index < 4; ++index)
	{
		vec3 edge;
		if (index == 3)
			edge = body1[0] - body1[index];
		else
			edge = body1[index + 1] - body1[index];

		edge = vec3(edge.y, -edge.x, edge.z);
		vec3 norm_edge = edge.Normalize();

		LineProjection(body1, norm_edge, body1_min, body1_max);
		LineProjection(body2, norm_edge, body2_min, body2_max);
		if (body1_min > body2_max || body2_min > body1_max)
			return false;
	}

	//Calculate 2nd body's edges
	for (int index = 0; index < 4; ++index)
	{
		vec3 edge;
		if (index == 3)
			edge = body2[0] - body2[index];
		else
			edge = body2[index + 1] - body2[index];

		edge = vec3(edge.y, -edge.x, edge.z);
		vec3 norm_edge = edge.Normalize();

		LineProjection(body1, norm_edge, body1_min, body1_max);
		LineProjection(body2, norm_edge, body2_min, body2_max);
		if (body1_min > body2_max || body2_min > body1_max)
			return false;
	}

	return true;
}

void World::LineProjection(Vertices& vert, vec3& point, float &min, float &max)
{
	//Implement edges' projection
	min = max = point.DotProduct(vert[0]);
	for (int index = 1; index < 4; ++index)
	{
		float value = point.DotProduct(vert[index]);
		if (value < min) min = value;
		else if (value > max) max = value;
	}
}

Vertices World::GetVertices(Sprite* spt)
{
	//  vert[1]     vert[2]
	//    |----------|
	//    |		     |
	//    |		     |
	//    |		     |
	//    |----------|
	//	vert[0]     vert[4]

	//Get rectangle;s vertices
	Vertices result;

	result[0] = vec3(spt->GetPosition().x - spt->GetScale().x / 2, spt->GetPosition().y - spt->GetScale().y / 2, spt->GetPosition().z);
	result[1] = vec3(spt->GetPosition().x - spt->GetScale().x / 2, spt->GetPosition().y + spt->GetScale().y / 2, spt->GetPosition().z);
	result[2] = vec3(spt->GetPosition().x + spt->GetScale().x / 2, spt->GetPosition().y + spt->GetScale().y / 2, spt->GetPosition().z);
	result[3] = vec3(spt->GetPosition().x + spt->GetScale().x / 2, spt->GetPosition().y - spt->GetScale().y / 2, spt->GetPosition().z);

	return result;
}

void World::BodyPipeline(Sprite* spt)
{
	//Set directed angle 
	vec3 norm_velocity = spt->GetRigidBody()->GetVelocity().Normalize();
	spt->GetRigidBody()->SetRotation(Math::RadToDeg(acosf(norm_velocity.DotProduct(vec3(1, 0, 0)))));
	if (norm_velocity.y < 0)
		spt->GetRigidBody()->SetRotation(360 - (spt->GetRigidBody()->GetRotation()));

	//Update body's speed and velocity
	vec3 new_speed = spt->GetRigidBody()->GetSpeed() + spt->GetRigidBody()->GetAcceleration();
	spt->GetRigidBody()->SetVelocity(vec3(new_speed.x * cosf(Math::DegToRad(spt->GetRigidBody()->GetRotation())),
		new_speed.y * sinf(Math::DegToRad(spt->GetRigidBody()->GetRotation())), 0));

	//Update position by velocity and direction
	spt->SetPosition(vec3(
		spt->GetPosition().x + spt->GetRigidBody()->GetVelocity().x,
		spt->GetPosition().y + spt->GetRigidBody()->GetVelocity().y,
		spt->GetPosition().z));
}

void World::CollisionResponse(Sprite* spt1, Sprite* spt2)
{
	//		1st case
	//    |----------||----------|
	//    |		     ||		     |
	//    |   spt1	 ||   spt2   |
	//    |		     ||		     |
	//    |----------||----------|
	//
	if (spt1->GetPosition().x < spt2->GetPosition().x)
	{
		vec3 diff = (spt2->GetPosition() - spt1->GetPosition()).Absolute();

		//		1-1st case
		//    |----------|
		//    |		     ||----------|
		//    |   spt1	 ||		     |
		//    |		     ||   spt2   |
		//    |----------||		     |
		//				  |----------|
		if (diff.x > diff.y)
		{
			spt1->SetPosition(vec3(spt2->GetPosition().x - spt2->GetScale().x / 2 - spt1->GetScale().x / 2,
				spt1->GetPosition().y, spt1->GetPosition().z));

			spt2->SetPosition(vec3(spt1->GetPosition().x + spt1->GetScale().x / 2 + spt2->GetScale().x / 2,
				spt2->GetPosition().y, spt2->GetPosition().z));
		}

		//		1-1-1st case					1-1-2nd case
		//    |----------|					|----------|
		//    |		     |					|		   |
		//    |   spt1	 |					|   spt2   |
		//    |		     |					|		   |
		//    |----------|					|----------|
		//			|----------|	|----------|
		//			|		   |	|		   |
		//			|   spt2   |	|   spt1   |
		//			|		   |	|		   |
		//			|----------|	|----------|
		//
		else
		{
			// 1-1-1st case
			if (spt1->GetPosition().y > spt2->GetPosition().y)
			{
				spt1->SetPosition(vec3(spt1->GetPosition().x,
					spt2->GetPosition().y + spt2->GetScale().y / 2 + spt1->GetScale().y / 2,
					spt1->GetPosition().z));

				spt2->SetPosition(vec3(spt2->GetPosition().x,
					spt1->GetPosition().y - spt1->GetScale().y / 2 - spt2->GetScale().y / 2,
					spt2->GetPosition().z));
			}

			// 1-1-2nd case
			else
			{
				spt1->SetPosition(vec3(spt1->GetPosition().x,
					spt2->GetPosition().y - spt2->GetScale().y / 2 - spt1->GetScale().y / 2,
					spt1->GetPosition().z));

				spt2->SetPosition(vec3(spt2->GetPosition().x,
					spt1->GetPosition().y + spt1->GetScale().y / 2 + spt2->GetScale().y / 2,
					spt2->GetPosition().z));
			}
		}
	}

	//		2nd case
	//    |----------||----------|
	//    |		     ||		     |
	//    |   spt2	 ||   spt1   |
	//    |		     ||		     |
	//    |----------||----------|
	//
	else
	{
		vec3 diff = (spt1->GetPosition() - spt2->GetPosition()).Absolute();

		//		2-1st case
		//    |----------|
		//    |		     ||----------|
		//    |   spt2	 ||		     |
		//    |		     ||   spt1   |
		//    |----------||		     |
		//				  |----------|
		if (diff.x > diff.y)
		{
			spt1->SetPosition(vec3(spt2->GetPosition().x + spt2->GetScale().x / 2 + spt1->GetScale().x / 2,
				spt1->GetPosition().y, spt1->GetPosition().z));

			spt2->SetPosition(vec3(spt1->GetPosition().x - spt1->GetScale().x / 2 - spt2->GetScale().x / 2,
				spt2->GetPosition().y, spt2->GetPosition().z));
		}

		//		2-1-1st case					2-1-2nd case
		//    |----------|					|----------|
		//    |		     |					|		   |
		//    |   spt2	 |					|   spt1   |
		//    |		     |					|		   |
		//    |----------|					|----------|
		//			|----------|	|----------|
		//			|		   |	|		   |
		//			|   spt1   |	|   spt2   |
		//			|		   |	|		   |
		//			|----------|	|----------|
		//
		else
		{
			// 2-1-1st case
			if (spt1->GetPosition().y < spt2->GetPosition().y)
			{
				spt1->SetPosition(vec3(spt1->GetPosition().x,
					spt2->GetPosition().y - spt2->GetScale().y / 2 - spt1->GetScale().y / 2,
					spt1->GetPosition().z));

				spt2->SetPosition(vec3(spt2->GetPosition().x,
					spt1->GetPosition().y + spt1->GetScale().y / 2 + spt2->GetScale().y / 2,
					spt2->GetPosition().z));
			}

			// 2-1-2nd case
			else
			{
				spt1->SetPosition(vec3(spt1->GetPosition().x,
					spt2->GetPosition().y + spt2->GetScale().y / 2 + spt1->GetScale().y / 2,
					spt1->GetPosition().z));

				spt2->SetPosition(vec3(spt2->GetPosition().x,
					spt1->GetPosition().y - spt1->GetScale().y / 2 - spt2->GetScale().y / 2,
					spt2->GetPosition().z));
			}
		}
	}
}