#include "ObjectManager.h"
#include "../Physics/RigidBody.h"
#include "../Graphic/Sprite.h"

ObjectManager::ObjectManager(void)
	:number_of_Spt(0)
{}

ObjectManager::~ObjectManager(void)
{}

void ObjectManager::AddObject(const int SpriteID, const std::string& textureDir)
{
	UNREFERENCED_PARAMETER(textureDir);

	//Make new sprite
	Sprite* new_sprite = new Sprite(SpriteID);

	new_sprite->SetTexture(new Texture);
	new_sprite->GetTexture()->LoadTexture(textureDir.c_str());

	//Push it into the list
	m_ObjectList.insert(std::hash_map<int, Sprite*>::value_type(
		SpriteID, new_sprite));
	
	//Change id number and the number of sprites;
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
	for (auto it = m_ObjectList.begin(); it != m_ObjectList.end(); ++it)
	{
		//Check if it has a rigidbody or not.
		if (it->second->HasRigidBody())
			it->second->RemoveRigidBody();

		//If there is id that client to find,
		delete (it->second->GetTexture());	//Delete texture
		delete (it->second);				//Delete it
	}

	m_ObjectList.clear();
	number_of_Spt = 0;
}

const std::hash_map<int, Sprite*>& ObjectManager::GetList(void) const
{
	//return the list
	return m_ObjectList;
}