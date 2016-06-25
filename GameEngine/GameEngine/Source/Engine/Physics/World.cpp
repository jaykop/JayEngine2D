/******************************************************************************/
/*!
\file   World.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains World's class member function
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "World.h"
#include <hash_map>
#include "../Graphic/Sprite.h"
#include "../Physics/RigidBody.h"
#include "../Utilities/Math/MathUtils.h"
#include "../ObjectManager/ObjectManager.h"

/******************************************************************************/
/*!
\brief - World's costructor
*/
/******************************************************************************/
World::World(void)
:tx_Toggle(true), ty_Toggle(true),
body1(Vertices()), body2(Vertices()),
tx_max(0), ty_max(0), tx_min(0), ty_min(0),
body1_min(0), body1_max(0), body2_min(0), body2_max(0)
{
	body1_1stIndex[0] = body1_2ndIndex[0] = 0;
	body2_1stIndex[0] = body2_2ndIndex[0] = 0;
	body1_1stIndex[1] = body1_2ndIndex[1] = 0;
	body2_1stIndex[1] = body2_2ndIndex[1] = 0;
	collided_edge[0] = collided_edge[1] = 0;
}

/******************************************************************************/
/*!
\brief - World's destructor
*/
/******************************************************************************/
World::~World(void)
{}

/******************************************************************************/
/*!
\brief - World's init function
*/
/******************************************************************************/
void World::Init(const ObjectList& objList)
{
	UNREFERENCED_PARAMETER(objList);
	body1 = body2 = Vertices();
	body1_min = body1_max = body2_min = body2_max = 0;
}

/******************************************************************************/
/*!
\brief - World's update function
*/
/******************************************************************************/
void World::Update(const ObjectList& objList)
{
	//Works each bodies' physics
	for (auto it1 = objList.begin(); it1 != objList.end(); ++it1)
	{
		// 1. If sprite has body and activated body to work.
		if (it1->second->HasRigidBody() && 
			it1->second->GetRigidBody()->GetMoveToggle())
		{
			//Save last position
			if (!it1->second->GetRigidBody()->IsCollided())
				it1->second->GetRigidBody()->SetLastPosition(it1->second->GetPosition());
			else
				it1->second->SetPosition(it1->second->GetPosition());

			//Work basic motion
			BodyPipeline(it1->second);
			
			// 2. if 2st sprite's colliders to be worked, check colliders
			if (it1->second->GetRigidBody()->GetColliderToggle())
			{
				auto next = it1;
				for (auto it2 = ++next; it2 != objList.end(); ++it2)
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
						{
							it1->second->SetColor(it1->second->GetColor());
							it2->second->SetColor(it2->second->GetColor());
							
							CollisionResponse(it1->second, it2->second);
						}// 4. Check the colliders
					}// 3. Has Rigid Body, 2 toggles to work
				}
			}// 2. Collider Toggle
		}// 1. Body Toggle
	}
}

/******************************************************************************/
/*!
\brief - World's shutdown function
*/
/******************************************************************************/
void World::Shutdown(const ObjectList& objList)
{
	UNREFERENCED_PARAMETER(objList);
}

/******************************************************************************/
/*!
\brief - World's Body Pipeline

\param spt - sprite to work
*/
/******************************************************************************/
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
	if (spt->GetRigidBody()->GetSpeed().x <= 0)
		spt->GetRigidBody()->SetSpeed(vec3(0.f, spt->GetRigidBody()->GetSpeed().y));
	if (spt->GetRigidBody()->GetSpeed().y <= 0)
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

/******************************************************************************/
/*!
\brief - Get sprite's 4 vertices

\param spt - sprite to get 4 verts
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief - Do line projection

\param vert - sprite's 4 vertices
\param point - normalized edge
\param min - minimum projection range
\param max - maximum projection range

*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief - Do Collision Intersect

\param spt1 - get 1st body's verts
\param spt2 - get 2nd body's verts

*/
/******************************************************************************/
bool World::CollisionIntersect(Sprite* spt1, Sprite* spt2)
{
	//Get rectangle;s vertices
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

/******************************************************************************/
/*!
\brief - Do Collision Response

\param spt1 - get 1st body's verts
\param spt2 - get 2nd body's verts

*/
/******************************************************************************/
void World::CollisionResponse(Sprite* spt1, Sprite* spt2)
{	
	// Todo: Temporary function!
	// Need to be fixed!!!

	//vec3 new_vel = spt1->GetRigidBody()->GetVelocity().Reflection(
	//GetCollidedLine(spt1, spt2).Rotation(90).Normalize());				// Calculate new velocity
	vec3 new_vel = -spt1->GetRigidBody()->GetVelocity();
	spt1->GetRigidBody()->SetVelocity(new_vel);								// Set new velocity
	spt1->GetRigidBody()->SetSpeed(spt1->GetRigidBody()->GetSpeed() / 2);	// Reduce the speed(force)
	spt1->SetPosition(spt1->GetRigidBody()->GetLastPosition());				// Move to the uncollided last position
	//BodyPipeline(spt1);

	// If 2nd sprite is movable, add half force of 1st sprite
	if (spt2->GetRigidBody()->GetMoveToggle())
	{
	//	//vec3 new_vel2 = spt2->GetRigidBody()->GetVelocity().Reflection(
	//		//GetCollidedLine(spt2, spt1).Rotation(90).Normalize());			// Calculate new velocity
	//	spt2->GetRigidBody()->SetVelocity(-new_vel);							// Set new velocity
	//	spt2->GetRigidBody()->SetSpeed(spt2->GetRigidBody()->GetSpeed() 
	//		+ spt1->GetRigidBody()->GetSpeed() / 2);							// Reduce the speed(force)
		spt2->SetPosition(spt2->GetRigidBody()->GetLastPosition());				// Move to the uncollided last position
	//	//BodyPipeline(spt2);
	}	
}

/******************************************************************************/
/*!
\brief - Do Collision Relation

\param spt1 - get 1st sprite
\param spt2 - get 2nd sprite
\param coliided - Set 2 bodies collision status

*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief - Get collided line segment

\param spt1 - get 1st sprite
\param spt2 - get 2nd sprite

*/
/******************************************************************************/
vec3 World::GetCollidedLine(const Sprite* spt1, const  Sprite* spt2)
{
	spt1; spt2;

	bool hooker = false;
	int numOfedge = 0;	// index of edge
	body1_1stIndex[2];	// body1's 1st edge index
	body1_2ndIndex[2];	// body1's 2nd edge index
	body2_1stIndex[2];	// body2's 1st edge index
	body2_2ndIndex[2];	// body2's 2nd edge index

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (j == 3 && i == 3)
			{
				hooker = Math::LineIntersection(body1[i], body1[0],
					body2[j], body2[0]);
				if (hooker)
				{
					body1_1stIndex[numOfedge] = 0, body1_2ndIndex[numOfedge] = i;
					collided_edge[numOfedge] = body2[0] - body2[j];
					body2_1stIndex[numOfedge] = 0, body2_2ndIndex[numOfedge] = j;
					++numOfedge;
				}
			}
			else if (j != 3 && i == 3)
			{
				hooker = Math::LineIntersection(body1[i], body1[0],
					body2[j], body2[j + 1]);
				if (hooker)
				{
					body1_1stIndex[numOfedge] = 0, body1_2ndIndex[numOfedge] = i;
					collided_edge[numOfedge] = body2[j + 1] - body2[j];
					body2_1stIndex[numOfedge] = j + 1, body2_2ndIndex[numOfedge] = j;
					++numOfedge;
				}
			}
			else if (j == 3 && i != 3)
			{
				hooker = Math::LineIntersection(body1[i], body1[i + 1],
					body2[j], body2[0]);
				if (hooker)
				{
					body1_1stIndex[numOfedge] = i + 1, body1_2ndIndex[numOfedge] = i;
					collided_edge[numOfedge] = body2[0] - body2[j];
					body2_1stIndex[numOfedge] = 0, body2_2ndIndex[numOfedge] = j;
					++numOfedge;
				}
			}
			else
			{
				hooker = Math::LineIntersection(body1[i], body1[i + 1],
					body2[j], body2[j + 1]);

				if (hooker)
				{
					body1_1stIndex[numOfedge] = i + 1, body1_2ndIndex[numOfedge] = i;
					collided_edge[numOfedge] = body2[j + 1] - body2[j];
					body2_1stIndex[numOfedge] = j + 1, body2_2ndIndex[numOfedge] = j;
					++numOfedge;
				}
			}
		}
	}

	// 	1st case		
	//			*-----------*	
	//			|			|	
	//		*---+-----------+---*
	//		|	|			|	|
	//		|	*-----------*	|
	//		|					|
	//		*-------------------*
	if (collided_edge[0] == collided_edge[1])
	{
		//return spt2->GetPosition() - spt1->GetPosition();

		return collided_edge[0];
	}

	//	2nd case	
	//			*---------------*
	//			|				|
	//			|				|
	//		*---+-------*		|
	//		|	|		| dy	|
	//		|	|	dx	|		|
	//		|	*-------+-------*
	//		|			| 
	//		*-----------*
	else
	{
		Vertices new_box = GetOverlappedBox(spt1, spt2);
		vec3 diff = (new_box[0] - new_box[2]).Absolute();
		if (diff.x > diff.y)
		{
			if (collided_edge[0].Absolute().x > collided_edge[1].Absolute().x)
				return collided_edge[0];
			else if (collided_edge[0].Absolute().x < collided_edge[1].Absolute().x)
				return collided_edge[1];
			else
				return spt1->GetPosition() - spt2->GetPosition();
		}

		else
		{
			if (collided_edge[0].Absolute().y > collided_edge[1].Absolute().y)
				return collided_edge[0];
			else if (collided_edge[0].Absolute().y < collided_edge[1].Absolute().y)
				return collided_edge[1];
			else
				return spt1->GetPosition() - spt2->GetPosition();
		}
	}
}

/******************************************************************************/
/*!
\brief - Get Overlapped Box

\param spt1 - get 1st sprite
\param spt2 - get 2nd sprite

*/
/******************************************************************************/
Vertices World::GetOverlappedBox(const Sprite* spt1, const Sprite* spt2)
{
	spt1, spt2;

	//		
	//			*---------------*
	//			|				|
	//			|				|
	//		*---+-------*		|
	//		|	|///////|		|
	//		|	|///////|		|
	//		|	*-------+-------*
	//		|			| 
	//		*-----------*

	int new_index = 0;
	Vertices new_box;
	for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2; ++j)
	{
		new_box[new_index] = Math::IntersectPointOf2Lines(body1[body1_2ndIndex[i]], body1[body1_1stIndex[i]],
			body2[body2_2ndIndex[j]], body2[body2_1stIndex[j]]).vector;
		++new_index;
	}

	for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2; ++j)
	{
		if (body1_2ndIndex[i] == body1_1stIndex[j])
			new_box[1] = body1[body1_2ndIndex[i]];
		if (body2_2ndIndex[i] == body2_1stIndex[j])
			new_box[2] = body2[body2_2ndIndex[i]];
	}

	float smallx = new_box[0].x, largex = new_box[0].x, smally = new_box[0].y, largey = new_box[0].y;
	for (int i = 0; i < 4; ++i)
	{
		if (new_box[i].x < smallx) smallx = new_box[i].x;
		if (new_box[i].x > largex) largex = new_box[i].x;
		if (new_box[i].y < smally) smally = new_box[i].y;
		if (new_box[i].y > largey) largey = new_box[i].y;
	}

	new_box[0] = vec3(smallx, smally, 0);
	new_box[1] = vec3(smallx, largey, 0);
	new_box[2] = vec3(largex, largey, 0);
	new_box[3] = vec3(largex, smally, 0);

	return new_box;
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