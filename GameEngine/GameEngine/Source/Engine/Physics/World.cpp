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
:mtd(vec3()), collided_edge(vec3())
{
	new_speed[0] = new_speed[1] = vec3();
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
	// collided_edge = mtd = vec3();
	// new_speed[0] = new_speed[1] = vec3();
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
			// Work basic motion
			BodyPipeline(it1->second);
			
			// 2. if 2st sprite's colliders to be worked, check colliders
			if (it1->second->GetRigidBody()->GetColliderToggle())
			{
				// Refresh collision-with info
				it1->second->GetRigidBody()->CheckCollided(false);
				it1->second->GetRigidBody()->SetCollisionWith(nullptr);

				auto new_begin = std::next(it1,1);
				for (auto it2 = objList.begin(); it2 != objList.end(); ++it2)
				{
					// 3. If both objs are differenct and both bodies has own body, 
					// activated body and collider body,
					if (it1 != it2 && it2->second->HasRigidBody() &&
						it2->second->GetRigidBody()->GetColliderToggle())
					{					
						// 4. then check the colliders.
						// Check two sprites' collision status
						bool collisionIntersect = CollisionIntersect(it1->second, it2->second);
						if (collisionIntersect)
						{
							// Collision response
							CollisionResponse(it1->second, it2->second);

							// Refresh the collision with info
							CollisionRelation(it1->second, it2->second);

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
		new_speed.y * sinf(Math::DegToRad(spt->GetRigidBody()->GetDirectionAngle())), 0) 
		*  (2.f / spt->GetRigidBody()->GetMass());

	//Update position by velocity and direction
	spt->SetPosition(vec3(
		spt->GetPosition().x + new_force.x,
		spt->GetPosition().y + new_force.y,
		spt->GetPosition().z));
}

/******************************************************************************/
/*!
\brief - Do line projection and check if it is or not

\param axis - pointer to standard aixes
\param index - axis' index
\param body1 - 1st sprite's body
\param body2 - 2nd sprite's body

\return bool
*/
/******************************************************************************/
bool World::AxisSeparatePolygons(vec3* axis, int& index, RigidBody* body1, RigidBody* body2)
{
	float min_a, max_a;
	float min_b, max_b;

	// Get intervals
	CalculateInterval(axis[index], body1, min_a, max_a);
	CalculateInterval(axis[index], body2, min_b, max_b);

	if (min_a > max_b || min_b > max_a)
		return true;

	// find the interval overlap
	float d0 = max_a - min_b;
	float d1 = max_b - min_a;
	float depth = d0 < d1 ? d0 : d1;

	// conver the separation axis into a push vector (re-normaliz
	// the axis and multiply by interval overlap)
	float axis_length_sqaured = axis[index].DotProduct(axis[index]);

	axis[index] *= depth / axis_length_sqaured;

	// Increase the index
	index++;
	return false;
}

/******************************************************************************/
/*!
\brief - Get mtd and collided segment of body

\param pushVector - pointer to axis vectors
\param iNumVectors - the number of total indexes

\return temp_mtd
*/
/******************************************************************************/
vec3 World::FindMTD(vec3* pushVector, int iNumVectors)
{
	// Init temp mtd 
	// and index of collided side
	vec3 temp_mtd = pushVector[0];
	int min_i = -1;
	float min_d2 = pushVector[0].DotProduct(pushVector[0]);

	// Get collided line
	for (int i = 1; i < iNumVectors; ++i)
	{
		float d2 = pushVector[i].DotProduct(pushVector[i]);
		if (d2 < min_d2)
		{
			// Get mtd and collided line's index
			min_i = i;
			min_d2 = d2;
			temp_mtd = pushVector[i];
		}
	}

	// If index has been found,
	// set it collided edge
	if (min_i != -1)
		collided_edge = pushVector[min_i];

	return temp_mtd;
}


/******************************************************************************/
/*!
\brief - Get interval between the segment and axis

\param axis - standard axis
\param body - sprite's body
\param min - minimumn float
\param max - maximum float
*/
/******************************************************************************/
void World::CalculateInterval(vec3& axis, RigidBody* body, float& min, float&max)
{
	// Get body's vertices
	Vertices verts = body->GetVertices();

	// Init 1st min and max
	min = max = axis.DotProduct(verts[0]);

	// Get min and max
	for (int i = 1; i < 4; ++i)
	{
		float d = axis.DotProduct(verts[i]);
		if (d < min) min = d;
		else if (d > max) max = d;
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
			return IntersectBoxToBall(spt1, spt2);

		else  return IntersectBoxToBall(spt2, spt1);
	}
}

/******************************************************************************/
/*!
\brief - Do Collision Intersect between 2 boxes

\param box1 - get 1st body's verts
\param box2 - get 2nd body's verts

*/
/******************************************************************************/
bool World::IntersectBoxToBox(Sprite* spt1, Sprite* spt2)
{
	// Get bodies' edges
	Edges body1_edges = spt1->GetRigidBody()->GetEdges();
	Edges body2_edges = spt2->GetRigidBody()->GetEdges();

	// init helper variables
	vec3 vec_axis[8];
	int iNumAxis = 0;

	// Check overlapped for the 1st sprite
	for (int i = 0; i < 4; ++i)
	{
		vec_axis[iNumAxis] = vec3(-body1_edges[i].y, body1_edges[i].x);

		if (AxisSeparatePolygons(vec_axis, iNumAxis, spt1->GetRigidBody(), spt2->GetRigidBody()))
			return false;

	}

	// Check overlapped for the 2nd sprite
	for (int i = 0; i < 4; ++i)
	{
		vec_axis[iNumAxis] = vec3(-body2_edges[i].y, body2_edges[i].x);

		if (AxisSeparatePolygons(vec_axis, iNumAxis, spt1->GetRigidBody(), spt2->GetRigidBody()))
			return false;
	}

	//Find munumum transition distance
	mtd = FindMTD(vec_axis, iNumAxis);

	vec3 d = spt1->GetRigidBody()->GetOwnerSprite()->GetPosition()
		- spt2->GetRigidBody()->GetOwnerSprite()->GetPosition();

	// Reverse the mtd's sign
	if (d.DotProduct(mtd) < 0.f)
		mtd = -mtd;

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
	// Get the distance of 2 circles' position and radius
	float distance = Math::DistanceOf2Points(ball1->GetPosition(), ball2->GetPosition());
	float sum_radius = (ball1->GetRigidBody()->GetScale().x + ball2->GetRigidBody()->GetScale().x) / 2.f;

	// Check if they are overlapped or not
	if (distance < sum_radius)
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
bool World::IntersectBoxToBall(Sprite* box, Sprite* ball)
{
	// Init distance
	float distance = 0, min_distance = 0;
	int collided_index = -1;

	// Check collision for each edges and centre of ball + radius
	for (int index = 0; index < 4; ++index)
	{
		if (index == 3)
			distance = Math::DistanceOf2Points(
			ball->GetPosition(), 
			box->GetRigidBody()->GetVertices()[index]);

		else
			distance = Math::DistanceOfPointSegment(
			ball->GetPosition(), 
			box->GetRigidBody()->GetVertices()[index], 
			box->GetRigidBody()->GetVertices()[index + 1]);
	
		if (!index) min_distance = distance;

		// If it is, collided
		if (distance < ball->GetScale().x / 2 &&
			distance <= min_distance)
		{
			collided_index = index;
			// Get collided segment
			if (index == 3) collided_edge = 
				box->GetRigidBody()->GetVertices()[0] - box->GetRigidBody()->GetVertices()[3];
			else collided_edge = 
				box->GetRigidBody()->GetVertices()[index + 1] - box->GetRigidBody()->GetVertices()[index];
		}
	}

	if (collided_index != -1)
		return true;

	// If not, not collided
	else return false;
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
		ResponseBallToBall(spt1, spt2);

	// Collision between 2 boxes
	else if (spt1->GetRigidBody()->GetShape() == BOX &&
		spt2->GetRigidBody()->GetShape() == BOX)
		ResponseBoxToBox(spt1, spt2);

	// Collision between ball and box
	else
	{
		if (spt1->GetRigidBody()->GetShape() == BOX &&
			spt2->GetRigidBody()->GetShape() == BALL)
			ResponseBoxToBall(spt1, spt2);

		else ResponseBoxToBall(spt2, spt1);
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
	// Subtract to balls position
	vec3 dt = ball1->GetPosition() - ball2->GetPosition();
	float d = dt.Length();

	// Get reflection velocity
	float ball1_ci = ball1->GetRigidBody()->GetVelocity().DotProduct(dt);
	float ball2_ci = ball2->GetRigidBody()->GetVelocity().DotProduct(dt);

	// Get minumum transition distance
	mtd = dt * ((ball1->GetRigidBody()->GetScale().x / 2.f + ball2->GetRigidBody()->GetScale().x / 2.f)
		- d) / d;

	// If 2nd ball is movable, refresh the 2nd ball's body info too
	if (ball2->GetRigidBody()->GetMoveToggle())
	{
		// Move to the uncollided last position
		ball1->SetPosition(ball1->GetPosition() + .5f * mtd);
		ball2->SetPosition(ball2->GetPosition() - .5f * mtd);

		// Set new velocity
		ball1->GetRigidBody()->SetVelocity(ball1->GetRigidBody()->GetVelocity() +
			(ball2_ci - ball1_ci) * dt / d);

		ball2->GetRigidBody()->SetVelocity(ball2->GetRigidBody()->GetVelocity() +
			(ball1_ci - ball2_ci) * dt / d);

		// Save new speeds of two boxes
		new_speed[0] = ball1->GetRigidBody()->GetSpeed() *
			(ball1->GetRigidBody()->GetMass() /
			(ball2->GetRigidBody()->GetMass() + ball1->GetRigidBody()->GetMass()));

		new_speed[1] = ball2->GetRigidBody()->GetSpeed() *
			(ball2->GetRigidBody()->GetMass() /
			(ball2->GetRigidBody()->GetMass() + ball1->GetRigidBody()->GetMass()));

		// Todo: use this new speed or delete
		/*new_speed[0].x = (ball1->GetRigidBody()->GetSpeed().x * (ball1->GetRigidBody()->GetMass() - ball2->GetRigidBody()->GetMass()) + (2 * ball2->GetRigidBody()->GetMass() * ball2->GetRigidBody()->GetSpeed().x)) / (ball1->GetRigidBody()->GetMass() + ball2->GetRigidBody()->GetMass());
		new_speed[0].y = (ball1->GetRigidBody()->GetSpeed().y * (ball1->GetRigidBody()->GetMass() - ball2->GetRigidBody()->GetMass()) + (2 * ball2->GetRigidBody()->GetMass() * ball2->GetRigidBody()->GetSpeed().y)) / (ball1->GetRigidBody()->GetMass() + ball2->GetRigidBody()->GetMass());

		new_speed[1].x = (ball2->GetRigidBody()->GetSpeed().x * (ball2->GetRigidBody()->GetMass() - ball1->GetRigidBody()->GetMass()) + (2 * ball1->GetRigidBody()->GetMass() * ball1->GetRigidBody()->GetSpeed().x)) / (ball1->GetRigidBody()->GetMass() + ball2->GetRigidBody()->GetMass());
		new_speed[1].y = (ball2->GetRigidBody()->GetSpeed().y * (ball2->GetRigidBody()->GetMass() - ball1->GetRigidBody()->GetMass()) + (2 * ball1->GetRigidBody()->GetMass() * ball1->GetRigidBody()->GetSpeed().y)) / (ball1->GetRigidBody()->GetMass() + ball2->GetRigidBody()->GetMass());*/

		// Reset the speed
		ball1->GetRigidBody()->SetSpeed(new_speed[0]);
		ball2->GetRigidBody()->SetSpeed(new_speed[1]);
	}

	else
	{
		// Move to the uncollided last position
		ball1->SetPosition(ball1->GetPosition() + mtd);

		// Set new velocity
		ball1->GetRigidBody()->SetVelocity((ball1->GetRigidBody()->GetVelocity() +
			(ball2_ci - ball1_ci) * dt / d));

		// Save new speeds of two boxes
		new_speed[0] = ball1->GetRigidBody()->GetSpeed() *
			(ball1->GetRigidBody()->GetMass() /
			(ball2->GetRigidBody()->GetMass() + ball1->GetRigidBody()->GetMass()));

		// Todo: use this new speed or delete
		/*new_speed[0].x = (ball1->GetRigidBody()->GetSpeed().x * (ball1->GetRigidBody()->GetMass() - ball2->GetRigidBody()->GetMass()) + (2 * ball2->GetRigidBody()->GetMass() * ball2->GetRigidBody()->GetSpeed().x)) / (ball1->GetRigidBody()->GetMass() + ball2->GetRigidBody()->GetMass());
		new_speed[0].y = (ball1->GetRigidBody()->GetSpeed().y * (ball1->GetRigidBody()->GetMass() - ball2->GetRigidBody()->GetMass()) + (2 * ball2->GetRigidBody()->GetMass() * ball2->GetRigidBody()->GetSpeed().y)) / (ball1->GetRigidBody()->GetMass() + ball2->GetRigidBody()->GetMass());*/

		// Set new speed
		ball1->GetRigidBody()->SetSpeed(new_speed[0]);
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
	// If 2nd box is movable, refresh both 2 bodies info
	if (box2->GetRigidBody()->GetMoveToggle())
	{
		// Move both onjects to be proper position
		// after the colliding
		box2->SetPosition(box2->GetPosition() - .5f * mtd);
		box1->SetPosition(box1->GetPosition() + .5f * mtd);

		// Calculate new velocity
		box1->GetRigidBody()->SetVelocity(
			box1->GetRigidBody()->GetVelocity().Reflection(
			collided_edge));

		// if 1st body's force is stronger than 2nd.
		// 2nd sprite's velocity to be set same as the 1st

		// else if (the 2nd stronger, than set opposite velocity)
		// Set opposite velocity
		box2->GetRigidBody()->SetVelocity(-box1->GetRigidBody()->GetVelocity());

		// Reset the speed
		// Save new speeds of two boxes
		new_speed[0] = box1->GetRigidBody()->GetSpeed() *
			(box1->GetRigidBody()->GetMass() /
			(box2->GetRigidBody()->GetMass() + box1->GetRigidBody()->GetMass()));

		new_speed[1] = box2->GetRigidBody()->GetSpeed() *
			(box2->GetRigidBody()->GetMass() /
			(box2->GetRigidBody()->GetMass() + box1->GetRigidBody()->GetMass()));

		// Reset the speeds
		box1->GetRigidBody()->SetSpeed((new_speed[0] + new_speed[1]) / box2->GetRigidBody()->GetMass());
		box2->GetRigidBody()->SetSpeed((new_speed[0] + new_speed[1]) / box1->GetRigidBody()->GetMass());

	}

	// 2nd sprite is unmovable,
	else
	{
		// Here refresh only 1sr sprite
		box1->SetPosition(box1->GetPosition() + mtd);

		// Calculate new reflected velocity
		box1->GetRigidBody()->SetVelocity(
			box1->GetRigidBody()->GetVelocity().Reflection(
			collided_edge));

		// Reset the speed
		new_speed[0] = box1->GetRigidBody()->GetSpeed() *
			(box1->GetRigidBody()->GetMass() /
			(box2->GetRigidBody()->GetMass() + box1->GetRigidBody()->GetMass()));

		// Reset the speeds
		box1->GetRigidBody()->SetSpeed(new_speed[0] / box2->GetRigidBody()->GetMass());
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
	box->GetRigidBody()->SetVelocity(-ball->GetRigidBody()->GetVelocity());

	// Save new speed
	new_speed[0] = box->GetRigidBody()->GetSpeed() *
		(box->GetRigidBody()->GetMass() /
		(ball->GetRigidBody()->GetMass() + box->GetRigidBody()->GetMass()));

	// Move to the uncollided last position
	// box->SetPosition(box->GetRigidBody()->GetLastPosition());

	// If the ball is movable, refresh the ball's body info
	if (ball->GetRigidBody()->GetMoveToggle())
	{
		// Calculate new velocity
		ball->GetRigidBody()->SetVelocity(
			ball->GetRigidBody()->GetVelocity().Reflection(collided_edge));	

		// Save new speed
		new_speed[1] = ball->GetRigidBody()->GetSpeed() *
			(ball->GetRigidBody()->GetMass() /
			(ball->GetRigidBody()->GetMass() + box->GetRigidBody()->GetMass()));

		// Move to the uncollided last position
		// ball->SetPosition(ball->GetRigidBody()->GetLastPosition());

		// Reset the speed
		ball->GetRigidBody()->SetSpeed(new_speed[1] + new_speed[0] / box->GetRigidBody()->GetMass());
	}

	// Reset the speed
	box->GetRigidBody()->SetSpeed(new_speed[0] + new_speed[1] / ball->GetRigidBody()->GetMass());
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

	spt1->SetColor(spt2->GetColor());
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
