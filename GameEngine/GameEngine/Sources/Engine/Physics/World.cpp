#include "World.h"
#include <hash_map>
#include "../Graphic/Sprite.h"
#include "../Physics/RigidBody.h"
#include "../Utilities/Math/MathUtils.h"
#include "../ObjectManager/ObjectManager.h"

World::World()
{

}

World::~World()
{

}

void World::Init(void)
{

}

void World::Update(ObjectManager& objM)
{
	//Works each bodies' physics
	for (auto it1 = objM.GetList().begin(); it1 != objM.GetList().end(); ++it1)
	{
		// 1. If sprite has body and activated body to work.
		if (it1->second->HasRigidBody() && 
			it1->second->GetRigidBody()->GetMoveToggle())
		{
			BodyPipeline(it1->second);
			
			// 2. if sprite's colliders to be worked
			if (it1->second->GetRigidBody()->GetColliderToggle())
			{
				//Colision Checker
				auto next = it1;
				for (auto it2 = ++next; it2 != objM.GetList().end(); ++it2)
				{
					// 3. If both objs are differenct, both bodies has own body, 
					//activated body toggle and collider body,
					if (it1 != it2 && it2->second->HasRigidBody() &&
						it2->second->GetRigidBody()->GetColliderToggle())
					{
						// 4. then check the colliders.
						if (CollisionIntersect(it1->second, it2->second))
						{
							CollisionResponse(it1->second, it2->second);
							
							//Temp checker {
							if (it1->second->GetID() == 0)
								it1->second->SetColor(it2->second->GetColor());

							else if (it2->second->GetID() == 0)
								it2->second->SetColor(it1->second->GetColor());
							// }

						} // 4. Check the colliders

						//No collision, then set info diffrently
						else
						{
							it1->second->GetRigidBody()->CheckCollided(false);
							it2->second->GetRigidBody()->CheckCollided(false);
						}

					}// 3. Has Rigid Body, 2 toggles to work
				}
			}// 2. Collider Toggle
		}// 1. Body Toggle
	}
}

void World::Shutdown()
{

}

void World::BodyPipeline(Sprite* spt)
{
	//Save last position
	if (!spt->GetRigidBody()->IsCollided())
		spt->GetRigidBody()->SetLastPosition(spt->GetPosition());

	//Set directed angle 
	vec3 norm_velocity = spt->GetRigidBody()->GetVelocity().Normalize();
	spt->GetRigidBody()->SetDirectionAngle(Math::RadToDeg(acosf(norm_velocity.DotProduct(vec3(1, 0, 0)))));
	if (norm_velocity.y < 0)
		spt->GetRigidBody()->SetDirectionAngle(360 - (spt->GetRigidBody()->GetDirectionAngle()));

	//Implement frction
	spt->GetRigidBody()->SetSpeed(spt->GetRigidBody()->GetSpeed() -
		spt->GetRigidBody()->GetFriction());

	//Control the meaningless force
	if (spt->GetRigidBody()->GetSpeed().x < 0.001f)
		spt->GetRigidBody()->SetSpeed(vec3(0.f, spt->GetRigidBody()->GetSpeed().y));
	if (spt->GetRigidBody()->GetSpeed().y < 0.001f)
		spt->GetRigidBody()->SetSpeed(vec3(spt->GetRigidBody()->GetSpeed().x, 0.f));

	//Update body's speed and velocity
	vec3 new_speed = spt->GetRigidBody()->GetSpeed() + spt->GetRigidBody()->GetAcceleration();
	vec3 new_force = vec3(new_speed.x * cosf(Math::DegToRad(spt->GetRigidBody()->GetDirectionAngle())),
		new_speed.y * sinf(Math::DegToRad(spt->GetRigidBody()->GetDirectionAngle())), 0);

	//Update position by velocity and direction
	spt->SetPosition(vec3(
		spt->GetPosition().x + new_force.x,
		spt->GetPosition().y + new_force.y,
		spt->GetPosition().z));
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

		LineProjection(body2, norm_edge, body2_min, body2_max);
		LineProjection(body1, norm_edge, body1_min, body1_max);
		if (body2_min > body1_max || body1_min > body2_max)
			return false;
	}

	return true;
}

Vertices World::GetVertices(Sprite* spt)
{
	//  vert[1]     vert[2]
	//    |----------|
	//    |		     |
	//    |	  spt    |
	//    |		     |
	//    |----------|
	//	vert[0]     vert[3]

	//Get rectangle;s vertices' position
	Vertices result;

	//Todo: Change GetScale function that is form body, not sprite.
	result[0] = vec3(spt->GetPosition().x - spt->GetScale().x / 2, spt->GetPosition().y - spt->GetScale().y / 2, spt->GetPosition().z);
	result[1] = vec3(spt->GetPosition().x - spt->GetScale().x / 2, spt->GetPosition().y + spt->GetScale().y / 2, spt->GetPosition().z);
	result[2] = vec3(spt->GetPosition().x + spt->GetScale().x / 2, spt->GetPosition().y + spt->GetScale().y / 2, spt->GetPosition().z);
	result[3] = vec3(spt->GetPosition().x + spt->GetScale().x / 2, spt->GetPosition().y - spt->GetScale().y / 2, spt->GetPosition().z);

	//If sprite is rotated...
	if (spt->GetRotation())
	{
		result[0] = result[0].Rotation(spt->GetRotation(), spt->GetPosition());
		result[1] = result[1].Rotation(spt->GetRotation(), spt->GetPosition());
		result[2] = result[2].Rotation(spt->GetRotation(), spt->GetPosition());
		result[3] = result[3].Rotation(spt->GetRotation(), spt->GetPosition());
	}

	return result;
}

void World::LineProjection(Vertices& vert, vec3& point, float &min, float &max)
{
	//Implement 4 edges' projection
	min = max = point.DotProduct(vert[0]);
	for (int index = 1; index < 4; ++index)
	{
		float value = point.DotProduct(vert[index]);
		if (value < min) min = value;
		else if (value > max) max = value;
	}
}

void World::CollisionResponse(Sprite* spt1, Sprite* spt2)
{	
	//Set info that sprites are collided
	spt1->GetRigidBody()->CheckCollided(true);
	spt2->GetRigidBody()->CheckCollided(true);

	spt1->SetPosition(spt1->GetRigidBody()->GetLastPosition());

	//If 2nd sprite is movable, add half force of 1st sprite
	if (spt2->GetRigidBody()->GetMoveToggle())
	{
		spt2->GetRigidBody()->SetVelocity(spt1->GetRigidBody()->GetVelocity());
		spt2->GetRigidBody()->SetSpeed(spt1->GetRigidBody()->GetSpeed());
	}

	//Stick its position and body info
	else
	{
		//...
	}

	//Reflect 1st sprite
	GetNormalVelocity(spt1, spt2);
	GetNormalVelocity(spt2, spt1);
	//spt1->GetRigidBody()->SetVelocity(-spt1->GetRigidBody()->GetVelocity());
	spt1->GetRigidBody()->SetSpeed(spt1->GetRigidBody()->GetSpeed() / 2);
}

void World::CollisionPipeline()
{
	
}


void World::GetNormalVelocity(Sprite* spt1, Sprite* spt2)
{
	Vertices secondSpt = GetVertices(spt2);
	vec3 criteria;

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
			criteria = secondSpt[1] - secondSpt[0];

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
				criteria = secondSpt[2] - secondSpt[1];

			// 1-1-2nd case
			else
				criteria = secondSpt[0] - secondSpt[3];
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
			criteria = secondSpt[3] - secondSpt[2];

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
				criteria = secondSpt[0] - secondSpt[3];

			// 2-1-2nd case
			else
				criteria = secondSpt[2] - secondSpt[1];
		}
	}

	spt1->GetRigidBody()->SetVelocity(
		(spt1->GetRigidBody()->GetVelocity().Reflection(
		criteria)));
}