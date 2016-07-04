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
#include "../ObjectManager/ObjectManager.h"

/******************************************************************************/
/*!
\brief - World's costructor
*/
/******************************************************************************/
World::World(void)
:body1(Vertices()), body2(Vertices()),
body1_min(0), body1_max(0), body2_min(0), body2_max(0),
loopToggle(true)
{
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
}

/******************************************************************************/
/*!
\brief - World's update function
*/
/******************************************************************************/
void World::Update(const ObjectList& objList)
{
	// Works each bodies' physics
	for (auto it1 = objList.begin(); it1 != objList.end(); ++it1)
	{
		// 1. If sprite has body and activated body to work.
		if (it1->second->HasRigidBody() && 
			it1->second->GetRigidBody()->GetMoveToggle())
		{
			// Save last position
			if (!it1->second->GetRigidBody()->IsCollided())
				it1->second->GetRigidBody()->SetLastPosition(it1->second->GetPosition());

			else
				it1->second->SetPosition(it1->second->GetPosition());

			// Work basic motion
			BodyPipeline(it1->second);
			
			// 2. if 2st sprite's colliders to be worked, check colliders
			if (it1->second->GetRigidBody()->GetColliderToggle())
			{
				// Init collision with info
				it1->second->GetRigidBody()->CheckCollided(false);
				it1->second->GetRigidBody()->SetCollisionWith(nullptr);

				// Todo: delete this or not
				auto new_bigin = std::next(it1, 1);
				for (auto it2 = objList.begin(); it2 != objList.end(); ++it2)
				{
					// 3. If both objs are differenct and both bodies has own body, 
					// activated body and collider body,
					if (it1 != it2 && it2->second->HasRigidBody() &&
						it2->second->GetRigidBody()->GetColliderToggle())
					{					
						// Save last position
						if (!it2->second->GetRigidBody()->IsCollided())
							it2->second->GetRigidBody()->SetLastPosition(it2->second->GetPosition());

						// 4. then check the colliders.
						// Check two sprites' collision status
						bool collisionIntersect = CollisionIntersect(it1->second, it2->second);
						if (collisionIntersect)
						{
							// Collision response
							CollisionResponse(it1->second, it2->second);

							// Refresh the collision with info
							CollisionRelation(it1->second, it2->second);

							// Switch toggle
							loopToggle = !loopToggle;
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
	// Collision between 2 balls
	if (spt1->GetRigidBody()->GetShape() == BALL &&
		spt2->GetRigidBody()->GetShape() == BALL)
		return IntersectBallToBall(spt1, spt2);

	// Collision between 2 boxes
	else if (spt1->GetRigidBody()->GetShape() == BOX && 
		spt2->GetRigidBody()->GetShape() == BOX)
		return IntersectBoxToBox(spt1, spt2);

	// Collision between ball and box
	else
	{
		if (spt1->GetRigidBody()->GetShape() == BOX &&
			spt2->GetRigidBody()->GetShape() == BALL)
			return IntersectBoxToBall(spt1, spt2, loopToggle);

		else  return IntersectBoxToBall(spt2, spt1, loopToggle);
	}
}

/******************************************************************************/
/*!
\brief - Do Collision Intersect between 2 boxes

\param box1 - get 1st body's verts
\param box2 - get 2nd body's verts

*/
/******************************************************************************/
bool World::IntersectBoxToBox(Sprite* box1, Sprite* box2)
{
	//Get rectangle;s vertices
	body1 = GetVertices(box1);
	body2 = GetVertices(box2);

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
\brief - Do Collision Intersect between 2 balls

\param ball1 - get 1st body's position and radius
\param ball2 - get 2nd body's position and radius

*/
/******************************************************************************/
bool World::IntersectBallToBall(Sprite* ball1, Sprite* ball2)
{
	// Get the distance of 2 circles' position
	float distance = 2 * Math::DistanceOf2Points(ball1->GetPosition(), ball2->GetPosition());

	// Check if they are overlapped or not
	if (distance < ball1->GetRigidBody()->GetScale().x + ball2->GetRigidBody()->GetScale().x)
		return true;

	return false;
}

/******************************************************************************/
/*!
\brief - Do Collision Intersect between box and ball

\param box - get 1st body's verts
\param ball - get 2nd body's position and radius

*/
/******************************************************************************/
bool World::IntersectBoxToBall(Sprite* box, Sprite* ball, bool toggle)
{
	// Init distance
	float distance = 0;

	//Get rectangle;s vertices
	body1 = GetVertices(box);

	// Here 2 loops to make balanced when there is two segments' projection happens
	// This is quite inefficient I guess, but this is the best for me.
	// Check collision for each edges and centre of ball + radius
	if (toggle)
	for (int index = 0; index < 4; ++index)
	{
		if (index == 3)
			distance = Math::DistanceOfPointSegment(ball->GetPosition(), body1[index], body1[0]);

		else
			distance = Math::DistanceOfPointSegment(ball->GetPosition(), body1[index], body1[index + 1]);
	
		// If it is, collided
		if (distance < ball->GetScale().x / 2)
		{
			// Get collided segment
			if (index == 3) collided_edge[0] = body1[0] - body1[3];
			else collided_edge[0] = body1[index + 1] - body1[index];

			return true;
		}
	}

	// Check collision for each edges and centre of ball + radius
	else
	for (int index = 3; index >= 0; --index)
	{
		if (index == 3)
			distance = Math::DistanceOfPointSegment(ball->GetPosition(), body1[0], body1[index]);

		else
			distance = Math::DistanceOfPointSegment(ball->GetPosition(), body1[index + 1], body1[index]);

		// If it is, collided
		if (distance < ball->GetScale().x / 2)
		{
			// Get collided segment
			if (index == 0)	collided_edge[0] = body1[0] - body1[3];
			else collided_edge[0] = body1[index] - body1[index + 1];

			return true;
		}
	}

	// If not, not collided
	return false;
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
	// Collision between 2 balls
	if (spt1->GetRigidBody()->GetShape() == BALL &&
		spt2->GetRigidBody()->GetShape() == BALL)
		return ResponseBallToBall(spt1, spt2);

	// Collision between 2 boxes
	else if (spt1->GetRigidBody()->GetShape() == BOX &&
		spt2->GetRigidBody()->GetShape() == BOX)
		return ResponseBoxToBox(spt1, spt2);

	// Collision between ball and box
	else
	{
		if (spt1->GetRigidBody()->GetShape() == BOX &&
			spt2->GetRigidBody()->GetShape() == BALL)
			return ResponseBoxToBall(spt1, spt2);

		else  return ResponseBoxToBall(spt2, spt1);
	}
}

/******************************************************************************/
/*!
\brief - Do Collision Response between two balls

\param ball1 - set new body info
\param ball2 - set new body info

*/
/******************************************************************************/
void World::ResponseBallToBall(Sprite* ball1, Sprite* ball2)
{			
	// Calculate new velocity
	ball1->GetRigidBody()->SetVelocity(-ball1->GetRigidBody()->GetVelocity());	
	
	// Reduce the speed(force)
	ball1->GetRigidBody()->SetSpeed(ball1->GetRigidBody()->GetSpeed() / 2);	
	
	// Move to the uncollided last position
	ball1->SetPosition(ball1->GetRigidBody()->GetLastPosition());

	// If 2nd sprite is movable, add half force of 1st sprite
	if (ball2->GetRigidBody()->GetMoveToggle())
	{
		// Set new velocity
		ball2->GetRigidBody()->SetVelocity(-ball1->GetRigidBody()->GetVelocity());	

		// Reduce the speed(force)
		ball2->GetRigidBody()->SetSpeed((ball2->GetRigidBody()->GetSpeed()	
				+ ball1->GetRigidBody()->GetSpeed()) / 2);

		// Move to the uncollided last position
		ball2->SetPosition(ball2->GetRigidBody()->GetLastPosition());
	}
}

/******************************************************************************/
/*!
\brief - Do Collision Response between two boxes

\param box1 - set new body info
\param box2 - set new body info

*/
/******************************************************************************/
void World::ResponseBoxToBox(Sprite* box1, Sprite* box2)
{
	// Get coliided lines
	GetCollidedLine(loopToggle);

	// Calculate new velocity
	box1->GetRigidBody()->SetVelocity(
		box1->GetRigidBody()->GetVelocity().Reflection(
		collided_edge[1].Rotation(90)).Normalize());	

	// Reduce the speed(force)
	box1->GetRigidBody()->SetSpeed(box1->GetRigidBody()->GetSpeed() / 2);	

	// Move to the uncollided last position
	box1->SetPosition(box1->GetRigidBody()->GetLastPosition());				

	// If 2nd sprite is movable, add half force of 1st sprite
	if (box2->GetRigidBody()->GetMoveToggle())
	{
		// Calculate new velocity
		box2->GetRigidBody()->SetVelocity(box1->GetRigidBody()->GetVelocity() +
			box2->GetRigidBody()->GetVelocity());

		// Reduce the speed(force)
		box2->GetRigidBody()->SetSpeed((box2->GetRigidBody()->GetSpeed()
				+ box1->GetRigidBody()->GetSpeed()) / 2);

		// Move to the uncollided last position
		box2->SetPosition(box2->GetRigidBody()->GetLastPosition());
	}
}

/******************************************************************************/
/*!
\brief - Do Collision Response between ball and box

\param box - set new body info
\param ball - set new body info

*/
/******************************************************************************/
void World::ResponseBoxToBall(Sprite* box, Sprite* ball)
{
	// Refresh the box's body info
	
	// Calculate new velocity
	box->GetRigidBody()->SetVelocity(-box->GetRigidBody()->GetVelocity());

	// Reduce the speed(force)
	box->GetRigidBody()->SetSpeed(box->GetRigidBody()->GetSpeed() / 2);	
	
	// Move to the uncollided last position
	box->SetPosition(box->GetRigidBody()->GetLastPosition());

	// If the ball is movable, add half force of 1st sprite
	if (ball->GetRigidBody()->GetMoveToggle())
	{
		// Calculate new velocity
		ball->GetRigidBody()->SetVelocity(
			ball->GetRigidBody()->GetVelocity().Reflection(
			collided_edge[0].Rotation(90)).Normalize());	

		// Reduce the speed(force)
		ball->GetRigidBody()->SetSpeed((ball->GetRigidBody()->GetSpeed()
			+ box->GetRigidBody()->GetSpeed()) / 2);

		// Move to the uncollided last position
		ball->SetPosition(ball->GetRigidBody()->GetLastPosition());
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
void World::CollisionRelation(Sprite* spt1, Sprite* spt2)
{
	//Set each sprite's collision status
	spt1->GetRigidBody()->CheckCollided(true);
	spt2->GetRigidBody()->CheckCollided(true);
	
	spt1->GetRigidBody()->SetCollisionWith(spt2);
	spt2->GetRigidBody()->SetCollisionWith(spt1);
}

/******************************************************************************/
/*!
\brief - Get collided line segment

\param toggle - loop toggle
*/
/******************************************************************************/
void World::GetCollidedLine(bool toggle)
{
	// Line intersection check
	bool checker = false;

	if (toggle)
	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
	{
		// Line intersection check
		if (i == 3 && j == 3)
			checker = Math::LineIntersection(body1[i], body1[0], body2[j], body2[0]);
		
		else if (i != 3 && j == 3)
			checker = Math::LineIntersection(body1[i], body1[i + 1], body2[j], body2[0]);

		else if (i == 3 && j != 3)
			checker = Math::LineIntersection(body1[i], body1[0], body2[j], body2[j + 1]);

		else
			checker = Math::LineIntersection(body1[i], body1[i + 1], body2[j], body2[j + 1]);

		// If checker is true,
		if (checker)
		{
			// Get collided segment
			if (i == 3 && j == 3)
			{
				collided_edge[0] = body1[0] - body1[3];
				collided_edge[1] = body2[0] - body2[3];
			}
			else if (i != 3 && j == 3)
			{
				collided_edge[0] = body1[i + 1] - body1[i];
				collided_edge[1] = body2[0] - body2[3];
			}
			else if (i == 3 && j != 3)
			{
				collided_edge[0] = body1[0] - body1[3];
				collided_edge[1] = body2[j + 1] - body2[j];
			}
			else
			{
				collided_edge[0] = body1[i + 1] - body1[i];
				collided_edge[1] = body2[j + 1] - body2[j];
			}
		}
	}

	else
	for (int i = 3; i >= 0; --i)
	for (int j = 3; j >= 0; --j)
	{
		// Line intersection check
		if (i == 3 && j == 3)
			checker = Math::LineIntersection(body1[i], body1[0], body2[j], body2[0]);
		
		else if (i != 3 && j == 3)
			checker = Math::LineIntersection(body1[i + 1], body1[i], body2[j], body2[0]);
		
		else if (i == 3 && j != 3)
			checker = Math::LineIntersection(body1[i], body1[0], body2[j + 1], body2[j]);

		else
			checker = Math::LineIntersection(body1[i + 1], body1[i], body2[j + 1], body2[j]);

		// If checker is true,
		if (checker)
		{
			// Get collided segment
			if (i == 3 && j == 3)
			{
				collided_edge[0] = body1[0] - body1[3];
				collided_edge[1] = body2[0] - body2[3];
			}
			else if (i != 3 && j == 3)
			{
				collided_edge[0] = body1[i] - body1[i + 1];
				collided_edge[1] = body2[0] - body2[3];
			}
			else if (i == 3 && j != 3)
			{
				collided_edge[0] = body1[0] - body1[3];
				collided_edge[1] = body2[j] - body2[j + 1];
			}
			else
			{
				collided_edge[0] = body1[i] - body1[i + 1];
				collided_edge[1] = body2[j] - body2[j + 1];
			}
		}
	}
}

/******************************************************************************/
/*!
\brief - Get 2 sprites' collision relation

\param spt1 - 1st sprite
\param spt2 - 2nd sprite
*/
/******************************************************************************/
bool World::GetCollisionRelation(Sprite* spt1, Sprite* spt2)
{
	if (spt1->GetRigidBody()->GetCollisionWith() == spt2
		&& spt2->GetRigidBody()->GetCollisionWith() == spt1)
		return true;

	return false;
}