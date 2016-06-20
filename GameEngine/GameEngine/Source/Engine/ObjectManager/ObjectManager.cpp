/******************************************************************************/
/*!
\file   ObjectManager.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains ObjectManager's class and member functions
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include <algorithm>
#include "ObjectManager.h"
#include "../Graphic/Sprite.h"
#include "../Graphic/Scene.h"
#include "../Physics/World.h"
#include "../Physics/RigidBody.h"

/******************************************************************************/
/*!
\brief - ObjectManager Constructor
*/
/******************************************************************************/
ObjectManager::ObjectManager(void)
	:number_of_Spt(0)
{}

/******************************************************************************/
/*!
\brief - ObjectManager Destructor
*/
/******************************************************************************/
ObjectManager::~ObjectManager(void)
{}

/******************************************************************************/
/*!
\brief - Add Object to the list

\param SpriteID - sprite's id
\param textureDir - sprite's texture
*/
/******************************************************************************/
void ObjectManager::AddObject(const int SpriteID, const char* textureDir)
{
	//Make new sprite
	Sprite* new_sprite = new Sprite(SpriteID);

	new_sprite->SetTexture(new Texture);
	new_sprite->GetTexture()->LoadTexture(textureDir);

	//Push it into the list
	m_ObjectList.insert(std::hash_map<int, Sprite*>::value_type(
		SpriteID, new_sprite));
	
	scenePtr->AddSprite(new_sprite);

	//Change id number and the number of sprites;
	++number_of_Spt;
}

/******************************************************************************/
/*!
\brief - Delete Object from the list

\param SpriteID - sprite's id

*/
/******************************************************************************/
void ObjectManager::RemoveObject(const int id)
{
	//If there is id that client to find,
	scenePtr->DeleteSprite(id);

	//Delete it
	delete m_ObjectList.find(id)->second;

	m_ObjectList.erase(id);
	--number_of_Spt;
}

/******************************************************************************/
/*!
\brief - Get Object 

\param SpriteID - sprite's id

*/
/******************************************************************************/
Sprite* ObjectManager::GetGameObject(const int id)
{
	//return the found one
	return m_ObjectList.find(id)->second;
}

/******************************************************************************/
/*!
\brief - Check if list has the obhect or not

\param SpriteID - sprite's id

*/
/******************************************************************************/
bool ObjectManager::HasObject(const int id)
{
	//Get object
	auto it = m_ObjectList.find(id);
	
	//Compare the id from user input
	if (it->second->GetID() == id)
		return true;

	return false;
}

/******************************************************************************/
/*!
\brief - Clear Object List
*/
/******************************************************************************/
void ObjectManager::ClearObjectList(void)
{
	//Remove the all objects in the lsit
	for (auto it = m_ObjectList.begin(); it != m_ObjectList.end(); ++it)
		delete (it->second);				//Delete all it

	m_ObjectList.clear();
	number_of_Spt = 0;
}

/******************************************************************************/
/*!
\brief - Get Object List

\return m_ObjectList
*/
/******************************************************************************/
const SpriteList& ObjectManager::GetList(void) const
{
	//return the list
	return m_ObjectList;
}

/******************************************************************************/
/*!
\brief - Bind scene and world 

\param pApp - pointer to app to bind to scene
*/
/******************************************************************************/
void ObjectManager::BindGameSystem(Application* pApp)
{
	scenePtr = new Scene(pApp);
	worldPtr = new World();
}

/******************************************************************************/
/*!
\brief - Initialize scene and world
*/
/******************************************************************************/
void ObjectManager::InitGameSystem()
{
	scenePtr->Init();
	worldPtr->Init();
}

/******************************************************************************/
/*!
\brief - Update scene and world
*/
/******************************************************************************/
void ObjectManager::UpdateGameSystem(void)
{
	scenePtr->Draw();
	worldPtr->Update(m_ObjectList);
}

/******************************************************************************/
/*!
\brief - Shutdown scene and world
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief - Get pointer to the scene

\return scenePtr
*/
/******************************************************************************/
Scene* ObjectManager::GetGameScene(void) const
{
	return scenePtr;
}

/******************************************************************************/
/*!
\brief - Get pointer to the world

\return worldPtr
*/
/******************************************************************************/
World* ObjectManager::GetGameWorld(void) const
{
	return worldPtr;
}