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
#include "../Graphic/Particle.h"
#include "../Graphic/Scene.h"
#include "../Physics/World.h"
#include "../StateManager/GameStateManager/GameStateManager.h"

/******************************************************************************/
/*!
\brief - ObjectManager Constructor
*/
/******************************************************************************/
ObjectManager::ObjectManager(void)
:number_of_Obj(0), m_GSM(0),
scenePtr(0), worldPtr(0), logicPtr(0), soundPtr(0)
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
\brief - Delete Object from the list

\param SpriteID - sprite's id
*/
/******************************************************************************/
void ObjectManager::RemoveObject(const int id)
{
	//If there is id that client to find,
	if (scenePtr)
		scenePtr->DeleteSprite(id);

	//Delete it
	
	auto fount = m_ObjectList.find(id)->second;
	
	if (strcmp(typeid((fount)).name(), "class Sprite"))
		delete m_ObjectList.find(id)->second;

	else if (strcmp(typeid((fount)).name(), "class Text"))
		delete static_cast<Text*>(fount);

	else if (strcmp(typeid((fount)).name(), "class Emitter"))
		delete static_cast<Emitter*>(fount);

	m_ObjectList.erase(id);

	--number_of_Obj;
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
	for (auto it = m_ObjectList.begin(); it != m_ObjectList.end(); )
		RemoveObject((it++)->second->GetID());
	
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
	m_GSM = gsm;

	soundPtr = new Sound(m_GSM);
	worldPtr = new World();
	scenePtr = new Scene(m_GSM);
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

/******************************************************************************/
/*!
\brief - Get pointer to m_GSM

\return m_GSM
*/
/******************************************************************************/
GameStateManager* ObjectManager::GetGSM(void)
{
	return m_GSM;
}
