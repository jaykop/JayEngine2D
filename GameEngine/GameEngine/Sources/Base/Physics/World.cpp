#include "World.h"
#include <hash_map>
#include "../ObjectManager/ObjectManager.h"
#include "../Graphic/Sprite.h"
#include "../Physics/RigidBody.h"
#include "../Math/MathUtils.h"

World::World()
{

}

World::~World()
{

}

void World::Init()
{

}

void World::Update(ObjectManager objM)
{
	auto list = objM.GetList();

	for (auto it1 = list.begin(); it1 != list.end(); ++it1)
	{
		auto next = it1;
		for (auto it2 = ++next; it2 != list.end(); ++it2)
		{
			//If both objs are same, or one of body has no body, 
			//then skip to check.
			if (it1 == it2 || !it1->second->HasRigidBody() ||
				!it2->second->HasRigidBody())
				continue;

			else
			{
				//else, check collision
				std::cout << "Object ID:" << it1->second->GetID() << " & " << it2->second->GetID();
				std::cout << " | Collision Info: " << DetectCollide(it1->second->GetRigidBody(),
					it2->second->GetRigidBody()) << "\n";
			}
		}
	}
}

void World::Shutdown()
{

}

bool World::DetectCollide(RigidBody* Obj1, RigidBody* Obj2)
{
	vec3 Obj1_pos = Obj1->m_position;
	vec3 Obj2_pos = Obj2->m_position;
	vec3 Obj1_scl = Obj1->m_scale / 2;
	vec3 Obj2_scl = Obj2->m_scale / 2;

	if (Obj1_pos.x + Obj1_scl.x < Obj2_pos.x - Obj2_scl.x ||
		Obj1_pos.x - Obj1_scl.x > Obj2_pos.x + Obj2_scl.x ||
		Obj1_pos.y + Obj1_scl.y < Obj2_pos.y - Obj2_scl.y ||
		Obj1_pos.y - Obj1_scl.y > Obj2_pos.y + Obj2_scl.y)
		return false;

	return true;
}