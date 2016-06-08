#include "ObjectManager.h"
#include "../Graphic/Sprite.h"

ObjectManager::ObjectManager(void)
	: id_settor(0), number_of_Spt(0)
{}

ObjectManager::~ObjectManager(void)
{}

void ObjectManager::AddObject(const std::string& textureDir)
{
	UNREFERENCED_PARAMETER(textureDir);
	Sprite* new_sprite = new Sprite;

	m_ObjectList.insert(std::hash_map<int, Sprite*>::value_type(
		id_settor, new_sprite));
	
	++id_settor;
	++number_of_Spt;
}

void ObjectManager::RemoveObject(const int id)
{
	for (auto it = m_ObjectList.begin(); it != m_ObjectList.end(); ++it)
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
	for (auto it = m_ObjectList.begin(); it != m_ObjectList.end(); ++it)
	 delete	it->second;

	m_ObjectList.clear();
	number_of_Spt = 0;
}

const std::hash_map<int, Sprite*>& ObjectManager::GetList(void) const
{
	return m_ObjectList;
}