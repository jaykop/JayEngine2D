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
:body1_min(0), body1_max(0), body2_min(0), body2_max(0),
loopToggle(true)
{
	mtd = vec3();
	collided_edge[0] = collided_edge[1] = vec3();
	temp_speed[0] = temp_speed[1] = vec3();
	temp_velocity[0] = temp_velocity[1] = vec3();
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
			// Work basic motion
			BodyPipeline(it1->second);
			
			// 2. if 2st sprite's colliders to be worked, check colliders
			if (it1->second->GetRigidBody()->GetColliderToggle())
			{
				// Refresh collision-with info
				it1->second->GetRigidBody()->CheckCollided(false);
				it1->second->GetRigidBody()->SetCollisionWith(nullptr);

				auto new_begin = std::next(it1,1);
				for (auto it2 = new_begin; it2 != objList.end(); ++it2)
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
\brief - Do line projection

\param vert - sprite's 4 vertices
\param point - normalized edge
\param min - minimum projection range
\param max - maximum projection range

*/
/******************************************************************************/
void World::LineProjection(Vertices vert, vec3& point, float &min, float &max)
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
		return new_intersect(spt1->GetRigidBody(), spt2->GetRigidBody(), mtd);

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
	//Refresh the mins and maxs
	body1_min = 0, body1_max = 0;
	body2_min = 0, body2_max = 0;

	//Calculate 1st body's edges projection
	for (int index = 0; index < 4; ++index)
	{
		vec3 edge;
		edge = box1->GetRigidBody()->GetEdges()[index];
		edge = vec3(edge.y, -edge.x, edge.z);
		vec3 norm_edge = edge.Normalize();

		LineProjection(box1->GetRigidBody()->GetVertices(), norm_edge, body1_min, body1_max);
		LineProjection(box2->GetRigidBody()->GetVertices(), norm_edge, body2_min, body2_max);
		if (body1_min > body2_max || body2_min > body1_max)
			return false;
	}

	//Calculate 2nd body's edges projection
	for (int index = 0; index < 4; ++index)
	{
		vec3 edge;
		edge = box2->GetRigidBody()->GetEdges()[index];
		edge = vec3(edge.y, -edge.x, edge.z);
		vec3 norm_edge = edge.Normalize();

		LineProjection(box2->GetRigidBody()->GetVertices(), norm_edge, body2_min, body2_max);
		LineProjection(box1->GetRigidBody()->GetVertices(), norm_edge, body1_min, body1_max);
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

	// Here 2 loops to make balanced when there is two segments' projection happens
	// This is quite inefficient I guess, but this is the best for me.
	// Check collision for each edges and centre of ball + radius
	if (toggle)
	for (int index = 0; index < 4; ++index)
	{
		if (index == 3)
			distance = Math::DistanceOfPointSegment(
			ball->GetPosition(), 
			box->GetRigidBody()->GetVertices()[index], 
			box->GetRigidBody()->GetVertices()[0]);

		else
			distance = Math::DistanceOfPointSegment(
			ball->GetPosition(), 
			box->GetRigidBody()->GetVertices()[index], 
			box->GetRigidBody()->GetVertices()[index + 1]);
	
		// If it is, collided
		if (distance < ball->GetScale().x / 2)
		{
			// Get collided segment
			if (index == 3) collided_edge[0] = 
				box->GetRigidBody()->GetVertices()[0] - box->GetRigidBody()->GetVertices()[3];
			else collided_edge[0] = 
				box->GetRigidBody()->GetVertices()[index + 1] - box->GetRigidBody()->GetVertices()[index];

			return true;
		}
	}

	// Check collision for each edges and centre of ball + radius
	else
	for (int index = 3; index >= 0; --index)
	{
		if (index == 3)
			distance = Math::DistanceOfPointSegment(
			ball->GetPosition(), 
			box->GetRigidBody()->GetVertices()[index], 
			box->GetRigidBody()->GetVertices()[0]);

		else
			distance = Math::DistanceOfPointSegment(ball->GetPosition(), 
			box->GetRigidBody()->GetVertices()[index], 
			box->GetRigidBody()->GetVertices()[index + 1]);

		// If it is, collided
		if (distance < ball->GetScale().x / 2)
		{
			// Get collided segment
			if (index == 3)	collided_edge[0] = 
				box->GetRigidBody()->GetVertices()[0] - box->GetRigidBody()->GetVertices()[3];
			else collided_edge[0] = 
				box->GetRigidBody()->GetVertices()[index + 1] - box->GetRigidBody()->GetVertices()[index];

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
	// Refresh the 1st ball's body info
	// Calculate new velocity
	ball1->GetRigidBody()->SetVelocity(-ball1->GetRigidBody()->GetVelocity());	
	
	// Save new speed
	temp_speed[0] = ball1->GetRigidBody()->GetSpeed() *
		(ball1->GetRigidBody()->GetMass() / 
		(ball1->GetRigidBody()->GetMass() + ball2->GetRigidBody()->GetMass()));
	
	// Move to the uncollided last position
	// ball1->SetPosition(ball1->GetRigidBody()->GetLastPosition());

	// If 2nd ball is movable, refresh the 2nd ball's body info too
	if (ball2->GetRigidBody()->GetMoveToggle())
	{
		// Set new velocity
		ball2->GetRigidBody()->SetVelocity(-ball1->GetRigidBody()->GetVelocity());	

		// Save new speed
		temp_speed[1] = ball2->GetRigidBody()->GetSpeed() *
			(ball2->GetRigidBody()->GetMass() /
			(ball1->GetRigidBody()->GetMass() + ball2->GetRigidBody()->GetMass()));

		// Move to the uncollided last position
		// ball2->SetPosition(ball2->GetRigidBody()->GetLastPosition());
		
		// Reset the speed
		ball2->GetRigidBody()->SetSpeed(temp_speed[1] + temp_speed[0] / ball1->GetRigidBody()->GetMass());
	}

	// Reset the speed
	ball1->GetRigidBody()->SetSpeed(temp_speed[0] + temp_speed[1] / ball2->GetRigidBody()->GetMass());
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
	// Refresh the 1st box's body info
	// Get coliided lines of the 2 boxes
	
	//GetCollidedLine(box1->GetRigidBody()->GetVertices(),
		//box2->GetRigidBody()->GetVertices(), 0);

	box1->SetPosition(box1->GetPosition() + mtd);

	// Calculate new velocity
	//box1->GetRigidBody()->SetVelocity(
	//	box1->GetRigidBody()->GetVelocity().Reflection(
	//	collided_edge[0].Rotation(90)));	

	//// Save new speed
	//temp_speed[0] = box1->GetRigidBody()->GetSpeed() *
	//	(box1->GetRigidBody()->GetMass() /
	//	(box1->GetRigidBody()->GetMass() + box2->GetRigidBody()->GetMass()));

	// Move to the uncollided last position
	//box1->SetPosition(box1->GetRigidBody()->GetLastPosition());				
	

	// If 2nd box is movable, refresh the 2nd box's body info too
	if (box2->GetRigidBody()->GetMoveToggle())
	{
		//GetCollidedLine(box2->GetRigidBody()->GetVertices(),
			//box1->GetRigidBody()->GetVertices(), 1);

		// Calculate new velocity
		//box2->GetRigidBody()->SetVelocity(-box1->GetRigidBody()->GetVelocity());
		////box2->GetRigidBody()->SetVelocity(
		//	//box2->GetRigidBody()->GetVelocity().Reflection(
		//	//collided_edge[1].Rotation(90)).Normalize());

		//// Save new speed
		//temp_speed[1] = box2->GetRigidBody()->GetSpeed() *
		//	(box2->GetRigidBody()->GetMass() /
		//	(box1->GetRigidBody()->GetMass() + box2->GetRigidBody()->GetMass()));

		//// Move to the uncollided last position
		////box2->SetPosition(box2->GetRigidBody()->GetLastPosition());
		box2->SetPosition(box2->GetPosition() - mtd);

		//// Reset the speed
		//box2->GetRigidBody()->SetSpeed(temp_speed[1] + temp_speed[0] / box1->GetRigidBody()->GetMass());
		////BodyPipeline(box2);
	}

	// Reset the speed
	//box1->GetRigidBody()->SetSpeed(temp_speed[0] + temp_speed[1] / box2->GetRigidBody()->GetMass());
	//std::cout << temp_speed[0] << "\n";
	//BodyPipeline(box1);
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
	temp_speed[0] = box->GetRigidBody()->GetSpeed() *
		(box->GetRigidBody()->GetMass() /
		(ball->GetRigidBody()->GetMass() + box->GetRigidBody()->GetMass()));

	// Move to the uncollided last position
	// box->SetPosition(box->GetRigidBody()->GetLastPosition());

	// If the ball is movable, refresh the ball's body info
	if (ball->GetRigidBody()->GetMoveToggle())
	{
		// Calculate new velocity
		ball->GetRigidBody()->SetVelocity(
			ball->GetRigidBody()->GetVelocity().Reflection(
			collided_edge[0].Rotation(90)).Normalize());	

		// Save new speed
		temp_speed[1] = ball->GetRigidBody()->GetSpeed() *
			(ball->GetRigidBody()->GetMass() /
			(ball->GetRigidBody()->GetMass() + box->GetRigidBody()->GetMass()));

		// Move to the uncollided last position
		// ball->SetPosition(ball->GetRigidBody()->GetLastPosition());

		// Reset the speed
		ball->GetRigidBody()->SetSpeed(temp_speed[1] + temp_speed[0] / box->GetRigidBody()->GetMass());
	}

	// Reset the speed
	box->GetRigidBody()->SetSpeed(temp_speed[0] + temp_speed[1] / ball->GetRigidBody()->GetMass());
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
void World::GetCollidedLine(Vertices body1, Vertices body2, int number)
{
	// Line intersection check
	vec3 inter_point[2];
	int numOfedge = 0;

	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
	{
		// Line intersection check
		if (i == 3 && j == 3)
		{
			if (Math::LineIntersection(body1[i], body1[0], body2[j], body2[0]))
			{
				inter_point[numOfedge] = Math::IntersectPointOf2Lines(body1[3], body1[0], body2[3], body2[0]);
				numOfedge++;
			}
		}
		else if (i != 3 && j == 3)
		{
			if (Math::LineIntersection(body1[i], body1[i + 1], body2[j], body2[0]))
			{
				inter_point[numOfedge] = Math::IntersectPointOf2Lines(body1[i], body1[i + 1], body2[j], body2[0]);
				numOfedge++;
			}
		}

		else if (i == 3 && j != 3)
		{
			if (Math::LineIntersection(body1[i], body1[0], body2[j], body2[j + 1]))
			{
				inter_point[numOfedge] = Math::IntersectPointOf2Lines(body1[i], body1[0], body2[j], body2[j + 1]);
				numOfedge++;
			}
		}
		else
		{
			if (Math::LineIntersection(body1[i], body1[i + 1], body2[j], body2[j + 1]))
			{
				inter_point[numOfedge] = Math::IntersectPointOf2Lines(body1[i], body1[i + 1], body2[j], body2[j + 1]);
				numOfedge++;
			}
		}
	}
	
	if (numOfedge < 3)
	collided_edge[numOfedge] = (inter_point[1] - inter_point[0]);

	//else

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

bool World::new_intersect(RigidBody* body1, RigidBody* body2, vec3& mtd)
{
	// Get bodies' edges
	Edges body1_edges = body1->GetEdges();
	Edges body2_edges = body2->GetEdges();

	Vertices body1_verts = body1->GetVertices();
	Vertices body2_verts = body2->GetVertices();

	vec3 vec_axis[9];
	float taxis[9];
	int iNumAxis = 0;
	float t = 1.f;
	vec3 n;

	vec3 relPos = body1->GetOwnerSprite()->GetPosition() 
		- body2->GetOwnerSprite()->GetPosition();
	vec3 relDis = body1->GetVelocity() - body2->GetVelocity();

	vec_axis[iNumAxis] = vec3(-relDis.y, relDis.x);
	float fVel2 = relDis .DotProduct(relDis);

	if (fVel2 > 0.000001f)
	{
		if (!new_IntervalIntersect(&body1_verts, &body2_verts,
			vec_axis[iNumAxis], relPos, relDis, taxis[iNumAxis], t))
			return false;

		++iNumAxis;
	}

	for (int i = 0; i < 4; ++i)
	{
		vec_axis[iNumAxis] = vec3(-body1_edges[i].y, body1_edges[i].x);

		if (!new_IntervalIntersect(&body1_verts, &body2_verts,
			vec_axis[iNumAxis], relPos, relDis, taxis[iNumAxis], t))
			return false;
		++iNumAxis;

		//vec_axis[iNumAxis] = vec3(-body1_edges[i].y, body1_edges[i].x);

		//if (new_AxisSeparatePolygons(vec_axis, iNumAxis, body1, body2))
		//	return false;

	}

	for (int i = 0; i < 4; ++i)
	{
		vec_axis[iNumAxis] = vec3(-body2_edges[i].y, body2_edges[i].x);

		if (!new_IntervalIntersect(&body1_verts, &body2_verts,
			vec_axis[iNumAxis], relPos, relDis, taxis[iNumAxis], t))
			return false;
		++iNumAxis;

		//vec_axis[iNumAxis] = vec3(-body2_edges[i].y, body2_edges[i].x);

		//if (new_AxisSeparatePolygons(vec_axis, iNumAxis, body1, body2))
		//	return false;
	}

	//Find munumum transition distance
	//mtd = new_FindMTD(vec_axis, iNumAxis);

	//vec3 d = body1->GetOwnerSprite()->GetPosition() - body2->GetOwnerSprite()->GetPosition();
	//if (d.DotProduct(mtd) < 0.f)
	//	mtd = -mtd;

	if (!new_FindCollidedPlane(vec_axis, taxis, iNumAxis, n, t))
		return false;

	// make sure the polygons gets pushed away from each other.
	if (n.DotProduct(relPos) < 0.0f)
		n = -n;

	return true;
}

bool World::new_FindCollidedPlane(vec3* axis, float* taxis, int index, vec3& nColl, float& tColl)
{
	//nColl = axis[0];
	//float min_d2 = axis[0].DotProduct(axis[0]);
	//for (int i = 1; i < 8; ++i)
	//{
	//	float d2 = axis[i].DotProduct(axis[i]);
	//	if (d2 < min_d2)
	//	{
	//		min_d2 = d2;
	//		nColl = axis[i];
	//	}
	//}

	//// Find collision first
	//int min_i = -1;
	//tColl = 0.f;
	//for (int i = 0; i < 8; ++i)
	//{
	//	if (taxis[i] > 0.f && 
	//		taxis[i] > axis[i])
	//	{
	//		min_i = i;
	//		tColl = taxis[i];
	//		nColl = axis[i];
	//	}
	//}

	//std::cout << min_i << "\n";

	//// Found one
	//if (min_i != -1)
	//	return true;

	//// If not, find overlapped
	//min_i = -1;
	//for (int i = 0; i < 8; ++i)
	//{
	//	float n = axis[i].Length();
	//	taxis[i] /= n;

	//	if (min_i == -1)
	//	{
	//		min_i = i;
	//		tColl = taxis[i];
	//		nColl = axis[i];
	//	}
	//}
	//if (min_i == -1)
	//	printf("Error!\n");


	////std::cout << min_i << "\n";
	//return (min_i != -1);

	//// find collision first
	//int mini = -1;
	//t = 0.0f;
	//for (int i = 0; i < iNumAxes; i++)
	//{
	//	if (taxis[i] > 0)
	//	{
	//		if (taxis[i] > t)
	//		{
	//			mini = i;
	//			t = taxis[i];
	//			N = xAxis[i];
	//			N.Normalise();
	//		}
	//	}
	//}

	// find collision first
	int mini = -1;
	tColl = 0.0f;
	for (int i = 0; i < index; i++)
	{
		if (taxis[i] > 0)
		{
			if (taxis[i] > tColl)
			{
				mini = i;
				tColl = taxis[i];
				nColl = axis[i];
				nColl.Normalize();
			}
		}
	}

	// found one
	if (mini != -1)
		return true;

	// nope, find overlaps
	mini = -1;
	for (int i = 0; i < index; i++)
	{
		float n = axis[i].Length();
		taxis[i] /= n;

		if (taxis[i] > tColl || mini == -1)
		{
			mini = i;
			tColl = taxis[i];
			nColl = axis[i];
		}
	}

	if (mini == -1)
		printf("Error\n");

	return (mini != -1);
}

bool World::new_IntervalIntersect(const Vertices* verts1, const Vertices* verts2,
	const vec3& axis, const vec3& diff_pos, const vec3& diff_vel,
	float& taxis, float tmax)
{
	vec3 d_pos = diff_pos;
	vec3 d_vel = diff_vel;

	float min0, max0;
	float min1, max1;
	GetInterval(verts1, 4, taxis, min0, max0);
	GetInterval(verts2, 4, taxis, min1, max1);

	float h = d_pos.DotProduct(axis);
	min0 += h;
	max0 += h;

	float d0 = min0 - max1; // if overlapped, do < 0
	float d1 = min1 - max0; // if overlapped, d1 > 0

	// separated, test dynamic intervals
	if (d0 > 0.0f || d1 > 0.0f)
	{
		float v = d_vel.DotProduct(axis);

		// small velocity, so only the overlap test will be relevant. 
		if (fabs(v) < 0.0000001f)
			return false;

		float t0 = -d0 / v; // time of impact to d0 reaches 0
		float t1 = d1 / v; // time of impact to d0 reaches 1

		if (t0 > t1) { float temp = t0; t0 = t1; t1 = temp; }
		taxis = (t0 > 0.0f) ? t0 : t1;

		if (taxis < 0.0f || taxis > tmax)
			return false;

		return true;
	}
	else
	{
		// overlap. get the interval, as a the smallest of |d0| and |d1|
		// return negative number to mark it as an overlap
		taxis = (d0 > d1) ? d0 : d1;
		return true;
	}
}

void World::GetInterval(const Vertices *axVertices, int iNumVertices, const vec3& xAxis, float& min, float& max)
{
	Vertices gotVerts = *axVertices;
	vec3 gotAxis = xAxis;
	min = max = gotVerts[0].DotProduct(gotAxis);
	for (int i = 1; i < 4; ++i)
	{
		float d = gotVerts[i].DotProduct(gotAxis);
		if (d < min) min = d;
		else if (d > max) max = d;
	}
}

bool World::new_AxisSeparatePolygons(vec3* axis, int& index, RigidBody* body1, RigidBody* body2)
{
	float min_a, max_a;
	float min_b, max_b;

	new_CalculateInterval(axis[index], body1, min_a, max_a);
	new_CalculateInterval(axis[index], body2, min_b, max_b);

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
	index++;
	return false;
}

vec3 World::new_FindMTD(vec3* pushVector, int iNumVectors)
{
	vec3 mtd = pushVector[0];
	float min_d2 = pushVector[0].DotProduct(pushVector[0]);
	for (int i = 1; i < iNumVectors; ++i)
	{
		float d2 = pushVector[i].DotProduct(pushVector[i]);
		if (d2 < min_d2)
		{
			min_d2 = d2;
			mtd = pushVector[i];
		}
	}

	return mtd;
}

void World::new_CalculateInterval(vec3& axis, RigidBody* body, float& min, float&max)
{
	Vertices verts = body->GetVertices();

	min = max = axis.DotProduct(verts[0]);
	for (int i = 1; i < 4; ++i)
	{
		float d = axis.DotProduct(verts[i]);
		if (d < min) min = d;
		else if (d > max) max = d;
	}
}