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
class RigidBody;
class ObjectManager;

//! Type definition for list
typedef std::hash_map<int, Sprite*> ObjectList;

//! To check between 2 Sprites
struct CollisionInfo
{
	int Spt1_id;
	int Spt2_id;
	bool collision;
};

//! For Rectangle sprites
class Vertices{

public:

	//! Vertices constructor, destructor, operator
	Vertices(){ vertice[0] = vertice[1] = vertice[2] = vertice[3] = vec3(); }
	~Vertices(){};
	vec3& operator[](const int index){ return vertice[index]; }

private:

	// Four vectices (RECT)
	vec3 vertice[4];
};

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

	//! Make line collider in the world form point1 to point2
	void SetLineCollision(vec3& point1, vec3& point2);
	bool GetCollisionResponse(Sprite* spt1, Sprite* spt2);

private:

	//! Collision helper functions
	Vertices GetVertices(Sprite* spt);
	vec3 GetCollidedLine(const Sprite* spt1, const Sprite* spt2);
	Vertices GetOverlappedBox(const Sprite* spt1, const Sprite* spt2);
	void LineProjection(Vertices& vert, vec3& point, float &min, float &max);
	
	// Todo: RECT - RECT collision,
	// RECT - CIRCLE collision,
	// CIRCLE - CIRCLE collision.
	// Collision response to be polished

	//! Collision functions
	bool CollisionIntersect(Sprite* spt1, Sprite* spt2);
	void CollisionResponse(Sprite* spt1, Sprite* spt2);
	void CollisionRelation(Sprite* spt1, Sprite* spt2, bool coliided);
	void CollisionPipeline();

	//! Calculate bodies' motion
	void BodyPipeline(Sprite* spt);

	//! Helper variables
	bool tx_Toggle, ty_Toggle;
	CollisionInfo of2Spts;
	Vertices body1, body2;
	float body1_min, body1_max; 
	float body2_min, body2_max;
	float tx_max, ty_max, tx_min, ty_min;

	vec3 collided_edge[2];	//! body1's 2 edge storage
	int body1_1stIndex[2];	//! body1's 1st edge index storage
	int body1_2ndIndex[2];	//! body1's 2nd edge index storage
	int body2_1stIndex[2];	//! body2's 1st edge index storage
	int body2_2ndIndex[2];	//! body2's 2nd edge index storage

	// Todo: Line collision (to be dynamic; list)
	// Todo: record collision relation between 2 spts
};

#endif // _WORLD_H_