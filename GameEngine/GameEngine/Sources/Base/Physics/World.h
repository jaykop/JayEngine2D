#ifndef _WORLD_H_
#define _WORLD_G_

#include "../Math/MathUtils.h"

enum CollisionType{ NO_COLLISION, VERTICAL, HORIZONAL };

class Vertices{
public:

	Vertices(){ vertice[0] = vertice[1] = vertice[2] = vertice[3] = vec3(); }
	~Vertices(){};
	vec3& operator[](const int index){ return vertice[index]; }

private:

	vec3 vertice[4];
};

class ObjectManager;
class RigidBody;
class Sprite;
class World
{

public:

	World();
	~World();
	
	void Init();
	void Update(ObjectManager& objM);
	void Shutdown();

private:

	//bool DetectCollide(RigidBody* Obj1, RigidBody* Obj2);
	Vertices GetVertices(Sprite* spt);
	void LineProjection(Vertices& vert, vec3& point, float &min, float &max);

	bool CollisionIntersect(Sprite* spt1, Sprite* spt2);
	void CollisionResponse(Sprite* spt1, Sprite* spt2);
	void CollisionPipeline();

	void BodyPipeline(Sprite* spt);
	
};

#endif // _WORLD_H_