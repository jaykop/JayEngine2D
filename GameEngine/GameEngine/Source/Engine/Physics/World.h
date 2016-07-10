/******************************************************************************/
/*!
\file   World.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains World's class member

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _WORLD_H_
#define _WORLD_G_

#include <hash_map>
#include "../Utilities/Math/MathUtils.h"

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

	//! New Fucntions
	bool new_FindCollidedPlane(vec3* axis, float* taxis, int index, vec3& nColl, float& tColl);
	void new_CalculateInterval(vec3& axis, RigidBody* body, float& min, float&max);
	bool new_intersect(RigidBody* body1, RigidBody* body2, vec3& mtd);
	bool new_AxisSeparatePolygons(vec3* axis, int& index, RigidBody* body1, RigidBody* body2);
	vec3 new_FindMTD(vec3* pushVector, int iNumVectors);
	bool World::new_IntervalIntersect(const Vertices* verts1, const Vertices* verts2,
		const vec3& axis, const vec3& diff_pos, const vec3& diff_vel, 
		float& taxis, float tmax);
	void GetInterval(const Vertices *axVertices, int iNumVertices,
		const vec3& xAxis, float& min, float& max);

	//! Collision helper functions
	void GetCollidedLine(Vertices body1, Vertices body2, int number);
	void LineProjection(Vertices vert, vec3& point, float &min, float &max);

	//! Collision intersection checking functions
	bool CollisionIntersect(Sprite* spt1, Sprite* spt2);
	bool IntersectBallToBall(Sprite* spt1, Sprite* spt2);
	bool IntersectBoxToBall(Sprite* spt1, Sprite* spt2, bool toggle);
	bool IntersectBoxToBox(Sprite* spt1, Sprite* spt2);

	//! Collision response functions
	void CollisionResponse(Sprite* spt1, Sprite* spt2);
	void ResponseBallToBall(Sprite* spt1, Sprite* spt2);
	void ResponseBoxToBall(Sprite* spt1, Sprite* spt2);
	void ResponseBoxToBox(Sprite* spt1, Sprite* spt2);

	//! Collision relation setting function 
	void CollisionRelation(Sprite* spt1, Sprite* spt2);

	//! Calculate bodies' motion
	void BodyPipeline(Sprite* spt);

	//! Helper variables
	bool loopToggle;			//! Toggle thatn control loop order
	vec3 collided_edge[2];		//! bodies edge storage
	vec3 temp_speed[2];			//! bodies' old speed storage
	vec3 temp_velocity[2];		//! bodies' old velocity
	vec3 mtd;

	float body1_min, body1_max;	//! projection constants
	float body2_min, body2_max;	//! projection constants
	
	float tColl;
	vec3 nColl;
};

#endif // _WORLD_H_