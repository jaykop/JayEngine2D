/******************************************************************************/
/*!
\file   World.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains World's class member

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

#ifndef _WORLD_H_
#define _WORLD_G_

#include <hash_map>
#include "../../Utilities/Math/MathUtils.h"

class Sprite;
class Vertices;
class RigidBody;
class ObjectManager;

//! Type definition for list
typedef std::hash_map<int, Sprite*> ObjectList;

//! class Physics World
class World
{

public:

	//! constructor and destructor
	World();
	~World();
	
	//! World's base function
	void Init(const ObjectList& objList);
	void Update(const ObjectList& objList);
	void Shutdown(const ObjectList& objList);

	//! Get 2 sprite's collision info
	bool GetCollisionRelation(Sprite* spt1, Sprite* spt2);

private:

	//! Calculate bodies' motion
	void BodyPipeline(Sprite* spt);

	//! Collision intersection checking functions
	bool CollisionIntersect(Sprite* spt1, Sprite* spt2);
	bool IntersectBallToBall(Sprite* spt1, Sprite* spt2);
	bool IntersectBoxToBall(Sprite* spt1, Sprite* spt2);
	bool IntersectBoxToBox(Sprite* spt1, Sprite* spt2);

	//! Collision response functions
	void CollisionResponse(Sprite* spt1, Sprite* spt2);
	void ResponseBallToBall(Sprite* spt1, Sprite* spt2);
	void ResponseBoxToBall(Sprite* spt1, Sprite* spt2);
	void ResponseBoxToBox(Sprite* spt1, Sprite* spt2);

	//! box2box helper functions
	void CalculateInterval(vec3& axis, RigidBody* body, float& min, float&max);
	bool AxisSeparatePolygons(vec3* axis, int& index, RigidBody* body1, RigidBody* body2);
	vec3 FindMTD(vec3* pushVector, int iNumVectors);
	vec3 GetClosestPoint(Sprite* box, Sprite* ball);

	//! Collision relation setting function 
	void CollisionRelation(Sprite* spt1, Sprite* spt2);

	//! Helper variables
	vec3 collided_edge;	//! bodies edge storage
	vec3 new_speed[2];	//! new speed for 2 sprites
	vec3 mtd;			//! minimum  transition distance
};

#endif // _WORLD_H_