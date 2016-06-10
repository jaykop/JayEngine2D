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

void World::Update(ObjectManager& objM)
{
	auto list = objM.GetList();

	//Works each bodies' physics
	for (auto it1 = list.begin(); it1 != list.end(); ++it1)
	{
		if (it1->second->HasRigidBody())
			it1->second->GetRigidBody()->WorkVelocity();

		//Colision Checker
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
				std::cout << Intersect(*it1->second->GetRigidBody(), *it2->second->GetRigidBody()) << "\n";
			}
		}
	}

	std::cout << "========================" << "\n";
}

void World::Shutdown()
{

}

bool World::Intersect(RigidBody& body1, RigidBody& body2)
{
	body1.SetVertices();
	body2.SetVertices();

	float body1_min = 0, body1_max = 0;
	float body2_min = 0, body2_max = 0;

	for (int index = 0; index < 4; ++index)
	{	
		vec3 edge;
		if (index == 3)
			edge = body1.GetVertice(0) - body1.GetVertice(index);
		else
			edge = body1.GetVertice(index+1) - body1.GetVertice(index);

		edge = vec3(edge.y, -edge.x, edge.z);
		vec3 norm_edge = edge.Normalize();

		LineProjection(body1, norm_edge, body1_min, body1_max);
		LineProjection(body2, norm_edge, body2_min, body2_max);
		if (body1_min > body2_max || body2_min > body1_max)
			return false;
	}

	for (int index = 0; index < 4; ++index)
	{
		vec3 edge;
		if (index == 3)
			edge = body2.GetVertice(0) - body2.GetVertice(index);
		else
			edge = body2.GetVertice(index + 1) - body2.GetVertice(index);

		edge = vec3(edge.y, -edge.x, edge.z);
		vec3 norm_edge = edge.Normalize();

		LineProjection(body1, norm_edge, body1_min, body1_max);
		LineProjection(body2, norm_edge, body2_min, body2_max);
		if (body1_min > body2_max || body2_min > body1_max)
			return false;
	}

	return true;
}

void World::LineProjection(RigidBody& body, vec3& point, float &min, float &max)
{
	min = max = point.DotProduct(body.GetVertice(0));
	for (int index = 1; index < 4; ++index)
	{
		float value = point.DotProduct(body.GetVertice(index));
		if (value < min) min = value;
		else if (value > max) max = value;
	}
}

//bool World::DetectCollide(RigidBody* Obj1, RigidBody* Obj2)
//{
//	We dont use this now.
//	vec3 Obj1_pos = Obj1->m_position;
//	vec3 Obj2_pos = Obj2->m_position;
//	vec3 Obj1_scl = Obj1->m_scale / 2;
//	vec3 Obj2_scl = Obj2->m_scale / 2;
//
//	if (Obj1_pos.x + Obj1_scl.x < Obj2_pos.x - Obj2_scl.x ||
//		Obj1_pos.x - Obj1_scl.x > Obj2_pos.x + Obj2_scl.x ||
//		Obj1_pos.y + Obj1_scl.y < Obj2_pos.y - Obj2_scl.y ||
//		Obj1_pos.y - Obj1_scl.y > Obj2_pos.y + Obj2_scl.y)
//		return false;
//
//	return true;
//}
