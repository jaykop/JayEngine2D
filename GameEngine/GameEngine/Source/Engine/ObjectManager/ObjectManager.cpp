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
#include "../Logic/Logic.h"
#include "../Sound/Sound.h"
#include "../Graphic/Scene.h"
#include "../Physics/World.h"
#include "../StateManager/GameStateManager/GameStateManager.h"

/******************************************************************************/
/*!
\brief - ObjectManager Constructor
*/
/******************************************************************************/
ObjectManager::ObjectManager(void)
:number_of_Obj(0)
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
void ObjectManager::AddObject(const int SpriteID, Type type)
{

	//Make new sprite
	if (type == SPRITE)
	{
		Sprite* new_sprite = new Sprite(SpriteID, type, this);

		// Set basic texture
		new_sprite->SetTexture(new Texture);
		new_sprite->GetTexture()->LoadTexture("Resource/Texture/rect.png");

		//Push it into the list
		m_ObjectList.insert(std::hash_map<int, Sprite*>::value_type(
			SpriteID, new_sprite));

		scenePtr->AddSprite(new_sprite);
	}

	else if (type == TEXT)
	{
		Text* new_sprite = new Text(SpriteID, type, this);

		//Push it into the list
		m_ObjectList.insert(std::hash_map<int, Sprite*>::value_type(
			SpriteID, new_sprite));

		scenePtr->AddSprite(new_sprite);
	}
	//Change id number and the number of sprites;
	++number_of_Obj;
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

	--number_of_Obj;
}

/******************************************************************************/
/*!
\brief - Get Sprite 

\param SpriteID - sprite's id
*/
/******************************************************************************/
Sprite* ObjectManager::GetSprite(const int id)
{
	//return the found one
	auto it = m_ObjectList.find(id)->second;
	if (it->GetObjectType() == SPRITE)
		return it;
	else
		return 0;
}

/******************************************************************************/
/*!
\brief - Get Text

\param SpriteID - sprite's id
*/
/******************************************************************************/
Text* ObjectManager::GetText(const int id)
{
	// return the found one
	auto it = m_ObjectList.find(id)->second;
	if (it->GetObjectType() == TEXT)
		return static_cast<Text*>(it);
	else
		return 0;
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

	number_of_Obj = 0;
}

/******************************************************************************/
/*!
\brief - Get Sprite List

\return m_ObjectList
*/
/******************************************************************************/
const ObjectList& ObjectManager::GetObjectList(void) const
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
void ObjectManager::BindGameSystem(GameStateManager* gsm)
{
	soundPtr = new Sound(gsm);
	worldPtr = new World();
	scenePtr = new Scene(gsm);
	logicPtr = new Logic();
}

/******************************************************************************/
/*!
\brief - Initialize scene and world
*/
/******************************************************************************/
void ObjectManager::InitGameSystem()
{
	// Initialize game system
	soundPtr->Init();
	worldPtr->Init(m_ObjectList);
	scenePtr->Init(m_ObjectList);
	logicPtr->Init(m_ObjectList);
}

/******************************************************************************/
/*!
\brief - Update scene and world
*/
/******************************************************************************/
void ObjectManager::UpdateGameSystem(void)
{
	// Update game system
	logicPtr->Update(m_ObjectList);
	worldPtr->Update(m_ObjectList);
	scenePtr->Update(m_ObjectList);
	soundPtr->Update();
}

/******************************************************************************/
/*!
\brief - Shutdown scene and world
*/
/******************************************************************************/
void ObjectManager::ShutdownGameSystem()
{
	//Shutdown basic trunks
	scenePtr->Shutdown(m_ObjectList);
	worldPtr->Shutdown(m_ObjectList);
	logicPtr->Shutdown(m_ObjectList);
	soundPtr->Shutdown();

	//Delete dynamic scene, world, logic
	delete scenePtr;
	delete worldPtr;
	delete logicPtr;
	delete soundPtr;

	logicPtr = 0;
	scenePtr = 0;
	worldPtr = 0;
	soundPtr = 0;
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

/******************************************************************************/
/*!
\brief - Get pointer to the Sound

\return soundPtr
*/
/******************************************************************************/
Sound* ObjectManager::GetGameSound(void) const
{
	return soundPtr;
}

/******************************************************************************/
/*!
\brief - Get pointer to the Logic

\return logicPtr
*/
/******************************************************************************/
Logic* ObjectManager::GetGameLogic(void) const
{
	return logicPtr;
}