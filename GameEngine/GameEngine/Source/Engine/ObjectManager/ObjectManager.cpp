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
void ObjectManager::AddObject(const int SpriteID, Type type, const char* textureDir)
{
	if (type == NORMAL)
	{
		//Make new sprite
		Sprite* new_sprite = new Sprite(SpriteID, type);

		new_sprite->SetTexture(new Texture);
		new_sprite->GetTexture()->LoadTexture(textureDir);

		//Push it into the list
		m_SpriteList.insert(std::hash_map<int, Sprite*>::value_type(
			SpriteID, new_sprite));

		scenePtr->AddSprite(new_sprite);
	}

	else
	{
		//Make new text
		Text* new_text = new Text(SpriteID, type);

		//new_text->SetTexture(new Texture);
		//new_text->GetTexture()->LoadTexture(textureDir);

		//Push it into the list
		m_TextList.insert(std::hash_map<int, Text*>::value_type(
			SpriteID, new_text));

		scenePtr->AddSprite(new_text);
	}

	//Change id number and the number of sprites;
	++number_of_Spt;
}

/******************************************************************************/
/*!
\brief - Delete Object from the list

\param SpriteID - sprite's id
\param type - sprite's type
*/
/******************************************************************************/
void ObjectManager::RemoveObject(const int id, Type type)
{
	if (type == NORMAL)
	{	
		//If there is id that client to find,
		scenePtr->DeleteSprite(id);

		//Delete it
		delete m_SpriteList.find(id)->second;

		m_SpriteList.erase(id);
	}

	else
	{
		//If there is id that client to find,
		scenePtr->DeleteSprite(id);

		//Delete it
		delete m_TextList.find(id)->second;

		m_TextList.erase(id);
	}

	--number_of_Spt;
}

/******************************************************************************/
/*!
\brief - Get Object 

\param SpriteID - sprite's id
\param type - sprite's type
*/
/******************************************************************************/
Sprite* ObjectManager::GetGameObject(const int id, Type type)
{
	//return the found one
	if (type == NORMAL)
		return m_SpriteList.find(id)->second;

	else 
		return m_TextList.find(id)->second;
}

/******************************************************************************/
/*!
\brief - Check if list has the obhect or not

\param SpriteID - sprite's id
\param type - sprite's type
*/
/******************************************************************************/
bool ObjectManager::HasObject(const int id, Type type)
{
	//Get object
	if (type == NORMAL)
	{
		auto it = m_SpriteList.find(id);

		//Compare the id from user input
		if (it->second->GetID() == id)
			return true;
	}

	else
	{
		auto it = m_TextList.find(id);

		//Compare the id from user input
		if (it->second->GetID() == id)
			return true;
	}

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
	for (auto it = m_SpriteList.begin(); it != m_SpriteList.end(); ++it)
		delete (it->second);				//Delete all it

	//Remove the all objects in the lsit
	for (auto it = m_TextList.begin(); it != m_TextList.end(); ++it)
		delete (it->second);				//Delete all it

	m_SpriteList.clear();
	m_TextList.clear();

	number_of_Spt = 0;
}

/******************************************************************************/
/*!
\brief - Get Sprite List

\return m_SpriteList
*/
/******************************************************************************/
const SpriteList& ObjectManager::GetSpriteList(void) const
{
	//return the list
	return m_SpriteList;
}

/******************************************************************************/
/*!
\brief - Get Text List

\return m_TextList
*/
/******************************************************************************/
const TextList& ObjectManager::GetTextList(void) const
{
	//return the list
	return m_TextList;
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
	scenePtr->Draw(m_TextList);
	worldPtr->Update(m_SpriteList);
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