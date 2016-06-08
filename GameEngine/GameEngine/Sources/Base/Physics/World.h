#ifndef _WORLD_H_
#define _WORLD_G_

class ObjectManager;
class RigidBody;

class World
{

public:
	World();
	//World(ObjectManager* objM);
	~World();
	
	void Init();
	void Update(ObjectManager objM);
	void Shutdown();

	bool DetectCollide(RigidBody* Obj1, RigidBody* Obj2);

private:

};

#endif // _WORLD_H_