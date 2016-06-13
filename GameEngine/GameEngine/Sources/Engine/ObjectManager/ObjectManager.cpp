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

	//Make new sprite
	Sprite* new_sprite = new Sprite(id_settor);

	//Push it into the list
	m_ObjectList.insert(std::hash_map<int, Sprite*>::value_type(
		id_settor, new_sprite));
	
	//Change id number and the number of sprites;
	++id_settor;
	++number_of_Spt;
}

void ObjectManager::RemoveObject(const int id)
{
	//Check if it has a rigidbody or not.
	if (m_ObjectList.find(id)->second->HasRigidBody())
		m_ObjectList.find(id)->second->RemoveRigidBody();

	//If there is id that client to find,
	//Delete it
	delete (m_ObjectList.find(id)->second);

	m_ObjectList.erase(id);
	--number_of_Spt;
}

Sprite* ObjectManager::GetGameObject(const int id)
{
	//return the found one
	return m_ObjectList.find(id)->second;
}

bool ObjectManager::HasObject(const int id)
{
	//Get object
	auto it = m_ObjectList.find(id);
	
	//Compare the id from user input
	if (it->second->GetID() == id)
		return true;

	return false;
}

void ObjectManager::ClearObjectList(void)
{
	//Remove the all objects in the lsit
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
	//return the list
	return m_ObjectList;
}