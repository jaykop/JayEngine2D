#ifndef _WORLD_H_
#define _WORLD_G_

#include <hash_map>
#include "../Utilities/Math/MathUtils.h"

class ObjectManager;
class RigidBody;
class Sprite;

//To check between 2 Sprites
struct CollisionInfo
{
	int Spt1_id;
	int Spt2_id;
	bool collision;
};

//For Rectangle sprites
class Vertices{

public:

	Vertices(){ vertice[0] = vertice[1] = vertice[2] = vertice[3] = vec3(); }
	~Vertices(){};
	vec3& operator[](const int index){ return vertice[index]; }

private:

	vec3 vertice[4];
};

//Physics world
class World
{

public:

	World();
	~World();
	
	void Init();
	void Update(ObjectManager& objM);
	void Shutdown();

	//Make line collider in the world form point1 to point2
	void SetLineCollision(vec3& point1, vec3& point2);
	bool GetCollisionResponse(Sprite* spt1, Sprite* spt2);

private:

	//Collision helper functions
	Vertices GetVertices(Sprite* spt);
	vec3 GetCollidedLine(const Sprite* spt1, const Sprite* spt2);
	Vertices GetOverlappedBox(const Sprite* spt1, const Sprite* spt2);
	void LineProjection(Vertices& vert, vec3& point, float &min, float &max);
	
	//Collision functions
	bool CollisionIntersect(Sprite* spt1, Sprite* spt2);
	void CollisionResponse(Sprite* spt1, Sprite* spt2);
	void CollisionRelation(Sprite* spt1, Sprite* spt2, bool coliided);
	void CollisionPipeline();

	//Calculate bodies' motion
	void BodyPipeline(Sprite* spt);

	// Helper variables
	bool tx_Toggle, ty_Toggle;
	CollisionInfo of2Spts;
	Vertices body1, body2;
	float body1_min, body1_max; 
	float body2_min, body2_max;
	float tx_max, ty_max, tx_min, ty_min;

	vec3 collided_edge[2];
	int body1_1stIndex[2];	// body1's 1st edge index
	int body1_2ndIndex[2];	// body1's 2nd edge index
	int body2_1stIndex[2];	// body2's 1st edge index
	int body2_2ndIndex[2];	// body2's 2nd edge index

	//Todo: Line collision (to be dynamic; list)
};

#endif // _WORLD_H_