#ifndef _WORLD_H_
#define _WORLD_G_

#include "../Math/MathUtils.h"

class ObjectManager;
class RigidBody;

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
	bool Intersect(RigidBody& body1, RigidBody& body2);
	void LineProjection(RigidBody& body, vec3& point, float &min, float &max);

};

#endif // _WORLD_H_