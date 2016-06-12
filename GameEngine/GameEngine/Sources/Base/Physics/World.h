#ifndef _WORLD_H_
#define _WORLD_G_

#include "../Math/MathUtils.h"

class ObjectManager;
class RigidBody;
class Sprite;

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
	void LineCollision(vec3& point1, vec3& point2);

private:

	//Collision helper functions
	Vertices GetVertices(Sprite* spt);
	void LineProjection(Vertices& vert, vec3& point, float &min, float &max);

	//Collision functions
	bool CollisionIntersect(Sprite* spt1, Sprite* spt2);
	void CollisionResponse(Sprite* spt1, Sprite* spt2);
	void CollisionPipeline();

	//Calculate bodies' motion
	void BodyPipeline(Sprite* spt);

};

#endif // _WORLD_H_