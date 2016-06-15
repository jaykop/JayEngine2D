#include "World.h"
#include <hash_map>
#include "../Graphic/Sprite.h"
#include "../Physics/RigidBody.h"
#include "../Utilities/Math/MathUtils.h"
#include "../ObjectManager/ObjectManager.h"

World::World(void)
:tx_Toggle(true), ty_Toggle(true),
body1(Vertices()), body2(Vertices()),
tx_max(0), ty_max(0), tx_min(0), ty_min(0),
body1_min(0), body1_max(0), body2_min(0), body2_max(0)
{}

World::~World(void)
{}

void World::Init(void)
{
	body1 = body2 = Vertices();
	body1_min = body1_max = body2_min = body2_max = 0;
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
						bool collisionIntersect = CollisionIntersect(it1->second, it2->second);
						if (collisionIntersect)
						{	
							CollisionResponse(it1->second, it2->second);
							
						} // 4. Check the colliders

						//No collision, then set info diffrently
						else
						{
							
						}

						//Check two sprites' collision status
						CollisionRelation(it1->second, it2->second, collisionIntersect);

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

	//Save last position
	if (!spt->GetRigidBody()->IsCollided())
		spt->GetRigidBody()->SetLastPosition(spt->GetPosition());

	//Update position by velocity and direction
	spt->SetPosition(vec3(
		spt->GetPosition().x + new_force.x,
		spt->GetPosition().y + new_force.y,
		spt->GetPosition().z));
}

bool World::CollisionIntersect(Sprite* spt1, Sprite* spt2)
{
	//Get rectangle;s vertices

	//Refresh the vetices
	body1 = GetVertices(spt1);
	body2 = GetVertices(spt2);

	//Refresh the mins and maxs
	body1_min = 0, body1_max = 0;
	body2_min = 0, body2_max = 0;

	//Calculate 1st body's edges projection
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

	//Calculate 2nd body's edges projection
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
	result[0] = vec3(spt->GetPosition().x - spt->GetRigidBody()->GetScale().x / 2, spt->GetPosition().y - spt->GetRigidBody()->GetScale().y / 2, spt->GetPosition().z);
	result[1] = vec3(spt->GetPosition().x - spt->GetRigidBody()->GetScale().x / 2, spt->GetPosition().y + spt->GetRigidBody()->GetScale().y / 2, spt->GetPosition().z);
	result[2] = vec3(spt->GetPosition().x + spt->GetRigidBody()->GetScale().x / 2, spt->GetPosition().y + spt->GetRigidBody()->GetScale().y / 2, spt->GetPosition().z);
	result[3] = vec3(spt->GetPosition().x + spt->GetRigidBody()->GetScale().x / 2, spt->GetPosition().y - spt->GetRigidBody()->GetScale().y / 2, spt->GetPosition().z);

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
	// Todo: Temporary function!
	// Need to be fixed!!!
	// Set info that sprites are collided
	CollisionRelation(spt1, spt2, true);

	spt1->SetPosition(spt1->GetRigidBody()->GetLastPosition());

	// If 2nd sprite is movable, add half force of 1st sprite
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
	
	spt1->GetRigidBody()->SetVelocity(-spt1->GetRigidBody()->GetVelocity());
	spt1->GetRigidBody()->SetSpeed(spt1->GetRigidBody()->GetSpeed() / 2);
}

bool World::Get2ndBoxEdge(const vec3& body2edge_start, const vec3& body2edge_end, 
	Sprite* sprite1)
{
	UNREFERENCED_PARAMETER(sprite1);
	UNREFERENCED_PARAMETER(body2edge_start);
	UNREFERENCED_PARAMETER(body2edge_end);
	return false;
}

void World::CollisionRelation(Sprite* spt1, Sprite* spt2, bool coliided)
{
	//Set each sprite's status
	spt1->GetRigidBody()->CheckCollided(coliided);
	spt2->GetRigidBody()->CheckCollided(coliided);
	
	//Refresh info
	of2Spts.Spt1_id = spt1->GetID();
	of2Spts.Spt2_id = spt2->GetID();
	of2Spts.collision = coliided;

	//Temporary visual collision checker
	if (coliided)
	{
		if (spt1->GetID() == 0)
			spt1->SetColor(spt2->GetColor());

		else if (spt2->GetID() == 0)
			spt2->SetColor(spt1->GetColor());
	}

	//else
	//{
	//	if (spt1->GetID() == 0)
	//		spt1->SetColor(vec4(1, 1, 1, 1));

	//	else if (spt2->GetID() == 0)
	//		spt2->SetColor(vec4(1, 1, 1, 1));
	//}
}

bool World::GetCollisionResponse(Sprite* spt1, Sprite* spt2)
{
	if (spt1->GetID() == of2Spts.Spt1_id &&
		spt2->GetID() == of2Spts.Spt2_id)
		return true;

	return false;
}

void World::CollisionPipeline()
{}
