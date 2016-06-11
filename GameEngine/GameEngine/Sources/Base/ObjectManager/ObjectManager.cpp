#include "ObjectManager.h"
#include "../Physics/RigidBody.h"
#include "../Graphic/Sprite.h"

ObjectManager::ObjectManager(void)
	: id_settor(0), number_of_Spt(0)
{}

ObjectManager::~ObjectManager(void)
{}

void ObjectManager::AddObject(const std::string& textureDir)
{
	UNREFERENCED_PARAMETER(textureDir);
	Sprite* new_sprite = new Sprite(id_settor);

	m_ObjectList.insert(std::hash_map<int, Sprite*>::value_type(
		id_settor, new_sprite));
	
	++id_settor;
	++number_of_Spt;
}

void ObjectManager::RemoveObject(const int id)
{
	if (m_ObjectList.find(id)->second->HasRigidBody())
		m_ObjectList.find(id)->second->RemoveRigidBody();

	delete (m_ObjectList.find(id)->second);

	m_ObjectList.erase(id);
	--number_of_Spt;
}

Sprite* ObjectManager::GetGameObject(const int id)
{
	return m_ObjectList.find(id)->second;
}

bool ObjectManager::HasObject(const int id)
{
	for (auto it = m_ObjectList.begin(); it != m_ObjectList.end(); ++it)
		if (it->second->GetID() == id)
			return true;

	return false;
}

void ObjectManager::ClearObjectList(void)
{
	for (int index = 0; index < id_settor; ++index)
	{
		if (HasObject(index))
			RemoveObject(index);
	}

	m_ObjectList.clear();
	id_settor = 0;
	number_of_Spt = 0;
}

const std::hash_map<int, Sprite*>& ObjectManager::GetList(void) const
{
	return m_ObjectList;
}