#include <algorithm>
#include "ObjectManager.h"
#include "../Graphic/Sprite.h"
#include "../Graphic/Scene.h"
#include "../Physics/World.h"
#include "../Physics/RigidBody.h"

ObjectManager::ObjectManager(void)
	:number_of_Spt(0)
{}

ObjectManager::~ObjectManager(void)
{}

void ObjectManager::AddObject(const int SpriteID, const std::string& textureDir)
{
	//Make new sprite
	Sprite* new_sprite = new Sprite(SpriteID);

	new_sprite->SetTexture(new Texture);
	new_sprite->GetTexture()->LoadTexture(textureDir.c_str());

	//Push it into the list
	m_ObjectList.insert(std::hash_map<int, Sprite*>::value_type(
		SpriteID, new_sprite));
	
	scenePtr->AddSprite(new_sprite);

	//Change id number and the number of sprites;
	++number_of_Spt;
}

void ObjectManager::RemoveObject(const int id)
{
	//If there is id that client to find,
	scenePtr->DeleteSprite(id);

	//Delete it
	delete m_ObjectList.find(id)->second;

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
		delete (it->second);				//Delete all it

	m_ObjectList.clear();
	number_of_Spt = 0;
}

const SpriteList& ObjectManager::GetList(void) const
{
	//return the list
	return m_ObjectList;
}

void ObjectManager::BindGameSystem(Application* pApp)
{
	scenePtr = new Scene(pApp);
	worldPtr = new World();
}

void ObjectManager::InitGameSystem()
{
	//Lambda expression
	//std::for_each(std::begin(m_ObjectList), std::end(m_ObjectList),
	//	[&](std::hash_map<int, Sprite*>::iterator it) 
	//{
	//	Don't use this anymore
	//	it->second->Init();
	//});

	scenePtr->Init();
	worldPtr->Init();
}

void ObjectManager::UpdateGameSystem(void)
{
	scenePtr->Draw();
	worldPtr->Update(m_ObjectList);
}

void ObjectManager::ShutdownGameSystem()
{
	//Shutdown basic trunks
	scenePtr->Shutdown();
	worldPtr->Shutdown();

	//Delete dynamic scene and world
	delete scenePtr;
	delete worldPtr;
	scenePtr = 0;
	worldPtr = 0;
}

Scene* ObjectManager::GetGameScene(void) const
{
	return scenePtr;
}

World* ObjectManager::GetGameWorld(void) const
{
	return worldPtr;
}