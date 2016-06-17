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
			//Save last position
			if (!it1->second->GetRigidBody()->IsCollided())
				it1->second->GetRigidBody()->SetLastPosition(it1->second->GetPosition());

			//Work basic motion
			BodyPipeline(it1->second);
			
			// 2. if 2st sprite's colliders to be worked, check colliders
			if (it1->second->GetRigidBody()->GetColliderToggle())
			{
				auto next = it1;
				for (auto it2 = ++next; it2 != objM.GetList().end(); ++it2)
				{
					// 3. If both objs are differenct and both bodies has own body, 
					// activated body and collider body,
					if (it1 != it2 && it2->second->HasRigidBody() &&
						it2->second->GetRigidBody()->GetColliderToggle())
					{					
						//Save last position
						if (!it2->second->GetRigidBody()->IsCollided())
							it2->second->GetRigidBody()->SetLastPosition(it2->second->GetPosition());

						// 4. then check the colliders.
						//Check two sprites' collision status
						bool collisionIntersect = CollisionIntersect(it1->second, it2->second);
						CollisionRelation(it1->second, it2->second, collisionIntersect);

						if (collisionIntersect)
							CollisionResponse(it1->second, it2->second);
						// 4. Check the colliders
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
	if (spt->GetRigidBody()->GetSpeed().x < 0)
		spt->GetRigidBody()->SetSpeed(vec3(0.f, spt->GetRigidBody()->GetSpeed().y));
	if (spt->GetRigidBody()->GetSpeed().y < 0)
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

Vertices World::GetVertices(Sprite* spt)
{
	//  vert[1]     vert[2]
	//    *----------*
	//    |		     |
	//    |	  spt    |
	//    |		     |
	//    *----------*
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

void World::CollisionResponse(Sprite* spt1, Sprite* spt2)
{	
	// Todo: Temporary function!
	// Need to be fixed!!!

	//vec3 new_vel = -spt1->GetRigidBody()->GetVelocity();
	vec3 new_vel = spt1->GetRigidBody()->GetVelocity().Reflection(
		GetCollidedLine(spt1, spt2).Rotation(90).Normalize());			// Calculate new velocity
	spt1->GetRigidBody()->SetVelocity(new_vel);								// Set new velocity
	spt1->GetRigidBody()->SetSpeed(spt1->GetRigidBody()->GetSpeed() / 2);	// Reduce the speed(force)
	spt1->SetPosition(spt1->GetRigidBody()->GetLastPosition());				// Move to the uncollided last position

	//BodyPipeline(spt1);

	// If 2nd sprite is movable, add half force of 1st sprite
	if (spt2->GetRigidBody()->GetMoveToggle())
	{
		//spt2->SetPosition(spt2->GetRigidBody()->GetLastPosition());			// Move to the uncollided last position
		//vec3 new_vel2 = spt2->GetRigidBody()->GetVelocity().Reflection(
			//GetCollidedLine(spt2, spt1).Rotation(90).Normalize());		// Calculate new velocity
		spt2->GetRigidBody()->SetVelocity(-spt1->GetRigidBody()->GetVelocity());// Set new velocity
		spt2->GetRigidBody()->SetSpeed(spt2->GetRigidBody()->GetSpeed() 
			+ spt1->GetRigidBody()->GetSpeed() / 2);	// Reduce the speed(force)
		//BodyPipeline(spt2);
	}

}

void World::CollisionRelation(Sprite* spt1, Sprite* spt2, bool coliided)
{
	//Set each sprite's collision status
	spt1->GetRigidBody()->CheckCollided(coliided);
	spt2->GetRigidBody()->CheckCollided(coliided);
	
	// Todo: Get 2 bodies' collision info
	// write the code here

	//of2Spts.Spt1_id = spt1->GetID();
	//of2Spts.Spt2_id = spt2->GetID();
	//of2Spts.collision = coliided;

	//Temporary visual collision checker
	if (coliided)
	{
		spt1->SetColor(spt2->GetColor());
		spt2->SetColor(spt1->GetColor());
	}
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

vec3 World::GetCollidedLine(const Sprite* spt1, const  Sprite* spt2)
{
	// Get spt2's collded line(edge) to set reflected velocity

	int numOfedge = 0;
	int  edgeIndex[2];
	vec3 edge[2];
	vec3 result;
	// Get the vertice got 2nd sprite's inside 
	for (int index = 0; index < 4; ++index)
	if (VerticeProjection(body1[index], spt2))
	{
		edgeIndex[numOfedge] = index;
		edge[numOfedge] = body1[index];
		++numOfedge;
	}

	//		intersect 1 point
	//			*---------------*
	//			|				|
	//			|		edge[0] |
	//		*---+-------*		|
	//		|	|		| dy	|
	//		|	|	dx	|		|
	//		|	*-------+-------*
	//		| shortest	|
	//		*-----------*
	if (numOfedge == 1)
	{
		float distance[4] = { 0 };
		float shortest = distance[0] = Math::DistanceOf2Points(body1[0], edge[0]);;
		int	shortest_index = 0;

		// Calculate which is the closest to the 1st sprite's middle point(position)
		for (int index = 1; index < 4; ++index)
		{
			distance[index] = Math::DistanceOf2Points(body1[index], edge[0]);
			if (shortest > distance[index])
			{
				shortest = distance[index];
				shortest_index = index;
			}
		}

		// Decide where to reflex
		if (abs(body1[shortest_index].x - edge[0].x) > abs(body1[shortest_index].y - edge[0].y))
		{
			if (shortest_index == 0 && edgeIndex[0] == 3)
				result = edge[0] - edge[1];
			else
				result = edge[1] - edge[0];
		}

		else
		{
			if (shortest_index == 0 && edgeIndex[0] == 3)
				result = edge[0] - edge[1];
			else
				result = edge[1] - edge[0];
		}
	}

	//		intersect 2 points
	//			*-----------*	
	//			|			|	
	//		*---+-----------+---*
	//		|	|			|	|
	//		|	*-----------*	|
	//		| edge[0]	edge[1]	|
	//		*-------------------*
	else if (numOfedge == 2)
	{
		if (edgeIndex[0] == 0 && edgeIndex[1] == 3)
			result = edge[0] - edge[1];
		else
			result = edge[1] - edge[0];;
	}

	return result;
}

bool World::VerticeProjection(vec3& vert, const Sprite* spt)
{
	vec3 new_vert = vert;

	// If 2nd sprite is rotated, then vertice also should be rotated
	// but not real rotation, just for checking
	if (spt->GetRotation())
		new_vert = vert.Rotation(spt->GetRotation(), spt->GetPosition());
	
	if ((new_vert.y > spt->GetPosition().y - spt->GetRigidBody()->GetScale().y / 2) &&
		(new_vert.y < spt->GetPosition().y + spt->GetRigidBody()->GetScale().y / 2) &&
		(new_vert.x > spt->GetPosition().x - spt->GetRigidBody()->GetScale().x / 2) &&
		(new_vert.x < spt->GetPosition().x + spt->GetRigidBody()->GetScale().x / 2))
		return true;

	return false;
}
