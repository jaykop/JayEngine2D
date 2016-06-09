//#include "World.h"
//#include <hash_map>
//#include "../ObjectManager/ObjectManager.h"
//#include "../Graphic/Sprite.h"
//#include "../Physics/RigidBody.h"
//#include "../Math/MathUtils.h"
//
//World::World()
//{
//
//}
//
//World::~World()
//{
//
//}
//
//void World::Init()
//{
//
//}
//
//void World::Update(ObjectManager objM)
//{
//	auto list = objM.GetList();
//
//	for (auto it1 = list.begin(); it1 != list.end(); ++it1)
//	{
//		auto next = it1;
//		for (auto it2 = ++next; it2 != list.end(); ++it2)
//		{
//			//If both objs are same, or one of body has no body, 
//			//then skip to check.
//			if (it1 == it2 || !it1->second->HasRigidBody() ||
//				!it2->second->HasRigidBody())
//				continue;
//
//			else
//			{
//				m_checker = DetectCollide(it1->second->GetRigidBody(),
//					it2->second->GetRigidBody());
//
//				switch (m_checker)
//				{
//
//				case NO_COLLISION:
//					break;
//
//				case RIGHT_HORIZON:
//
//					if (!it1->second->GetRigidBody()->GetStatus())
//					{
//						it1->second->SetPosition(vec3(
//							(it2->second->GetPosition().x - it2->second->GetScale().x - it1->second->GetScale().x),
//							it1->second->GetPosition().y, it1->second->GetPosition().z));
//					}
//
//					if (!it2->second->GetRigidBody()->GetStatus())
//					{
//						it2->second->SetPosition(vec3(
//							(it1->second->GetPosition().x + it1->second->GetScale().x + it2->second->GetScale().x),
//							it2->second->GetPosition().y, it2->second->GetPosition().z));
//					}
//					break;
//
//				case LEFT_HORIZON:
//
//					if (!it1->second->GetRigidBody()->GetStatus())
//					{
//						it1->second->SetPosition(vec3(
//							(it2->second->GetPosition().x + it2->second->GetScale().x + it1->second->GetScale().x),
//							it1->second->GetPosition().y, it1->second->GetPosition().z));
//					}
//
//					if (!it2->second->GetRigidBody()->GetStatus())
//					{
//						it2->second->SetPosition(vec3(
//							(it1->second->GetPosition().x - it1->second->GetScale().x - it2->second->GetScale().x),
//							it2->second->GetPosition().y, it2->second->GetPosition().z));
//					}
//					break;
//
//				case UP_VERTICAL:
//
//					if (!it1->second->GetRigidBody()->GetStatus())
//					{
//						//it1->second->SetPosition();
//					}
//
//					if (!it2->second->GetRigidBody()->GetStatus())
//					{
//						//it2->second->SetPosition();
//					}
//					break;
//
//				case DOWN_VERTICAL:
//
//					if (!it1->second->GetRigidBody()->GetStatus())
//					{
//						//it1->second->SetPosition();
//					}
//
//					if (!it2->second->GetRigidBody()->GetStatus())
//					{
//						//it2->second->SetPosition();
//					}
//					break;
//				}
//				//else, check collision
//				/*std::cout << "Object ID:" << it1->second->GetID() << " & " << it2->second->GetID();
//				std::cout << " | Collision Info: " <<  << "\n";*/
//			}
//		}
//	}
//}
//
//void World::Shutdown()
//{
//
//}
//
//CollisionChecker World::DetectCollide(RigidBody* Obj1, RigidBody* Obj2)
//{
//	vec3 Obj1_pos = Obj1->m_position;
//	vec3 Obj2_pos = Obj2->m_position;
//	vec3 Obj1_scl = Obj1->m_scale / 2;
//	vec3 Obj2_scl = Obj2->m_scale / 2;
//
//	Obj1->SetStatus(false);
//	Obj2->SetStatus(false);
//
//	//CollisionPriority priority = ;
//
//	CollisionChecker vert_checker = VerticalCollider(Obj1_pos, Obj2_pos, Obj1_scl, Obj2_scl);
//	CollisionChecker horz_checker = HorizonalCollider(Obj1_pos, Obj2_pos, Obj1_scl, Obj2_scl);
//
//	if (vert_checker && horz_checker)
//	{
//		Obj1->SetStatus(true);
//		Obj2->SetStatus(true);
//
//		return horz_checker;
//
//	}
//
//	//if (Obj1_pos.x + Obj1_scl.x >= Obj2_pos.x - Obj2_scl.x)
//	//{
//	//	Obj1->SetStatus(true);
//	//	Obj2->SetStatus(true);
//	//	return RIGHT_HORIZON;
//	//}
//	//
//	//else if (Obj1_pos.x - Obj1_scl.x <= Obj2_pos.x + Obj2_scl.x)
//	//{
//	//	Obj1->SetStatus(true);
//	//	Obj2->SetStatus(true);
//	//	return LEFT_HORIZON;
//	//}
//	//
//	//else if (Obj1_pos.y + Obj1_scl.y >= Obj2_pos.y - Obj2_scl.y)
//	//{
//	//	Obj1->SetStatus(true);
//	//	Obj2->SetStatus(true);
//	//	return UP_VERTICAL;
//	//}
//	//
//	//else if (Obj1_pos.y - Obj1_scl.y <= Obj2_pos.y + Obj2_scl.y)
//	//{
//	//	Obj1->SetStatus(true);
//	//	Obj2->SetStatus(true);
//	//	return DOWN_VERTICAL;
//	//}
//
//	return NO_COLLISION;
//}
//
//CollisionChecker World::VerticalCollider(vec3& Obj1_pos, vec3& Obj2_pos, vec3& Obj1_scl, vec3& Obj2_scl)
//{
//	if (Obj1_pos.y + Obj1_scl.y >= Obj2_pos.y - Obj2_scl.y)
//		return UP_VERTICAL;
//
//	else if (Obj1_pos.y - Obj1_scl.y <= Obj2_pos.y + Obj2_scl.y)
//		return DOWN_VERTICAL;
//
//	return NO_COLLISION;
//}
//
//CollisionChecker World::HorizonalCollider(vec3& Obj1_pos, vec3& Obj2_pos, vec3& Obj1_scl, vec3& Obj2_scl)
//{
//	if (Obj1_pos.x + Obj1_scl.x >= Obj2_pos.x - Obj2_scl.x)
//		return RIGHT_HORIZON;
//
//	else if (Obj1_pos.x - Obj1_scl.x <= Obj2_pos.x + Obj2_scl.x)
//		return LEFT_HORIZON;
//
//	return NO_COLLISION;
//}
//
//#ifndef _WORLD_H_
//#define _WORLD_G_
//
//#include "../Math/MathUtils.h"
//
//enum CollisionChecker{
//	NO_COLLISION, RIGHT_HORIZON, LEFT_HORIZON,
//	UP_VERTICAL, DOWN_VERTICAL
//};
//
//enum CollisionPriority{ NONE, VERT, HORZ, DIAG };
//
//class ObjectManager;
//class RigidBody;
//
//class World
//{
//
//public:
//	World();
//	~World();
//
//	void Init();
//	void Update(ObjectManager objM);
//	void Shutdown();
//
//	CollisionChecker VerticalCollider(vec3& Obj1_pos, vec3& Obj2_pos,
//		vec3& Obj1_scl, vec3& Obj2_scl);
//	CollisionChecker HorizonalCollider(vec3& Obj1_pos, vec3& Obj2_pos,
//		vec3& Obj1_scl, vec3& Obj2_scl);
//	CollisionChecker DetectCollide(RigidBody* Obj1, RigidBody* Obj2);
//
//private:
//
//	CollisionChecker m_checker;
//
//};
//
//#endif // _WORLD_H_