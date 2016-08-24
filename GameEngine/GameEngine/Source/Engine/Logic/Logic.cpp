/******************************************************************************/
/*!
\file   Logic.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/25(yy/mm/dd)

\description
Contains Logic's class and member function

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

#include "Logic.h"
#include "GameLogic/GameLogic.h"

/******************************************************************************/
/*!
\brief - Logic Constructor
*/
/******************************************************************************/
Logic::Logic(void)
{}

/******************************************************************************/
/*!
\brief - Logic Destrutor
*/
/******************************************************************************/
Logic::~Logic(void)
{}

/******************************************************************************/
/*!
\brief - Logic Load function
*/
/******************************************************************************/
void Logic::Load(const ObjectList& objList, const Json::Value& data)
{
	// Load logics
	for (auto it = objList.begin(); it != objList.end(); ++it)
	{
		for (auto logic_it = (*it).second->GetLogicList().begin();
			logic_it != (*it).second->GetLogicList().end(); ++logic_it)
			(*logic_it).second->Load(data);
	}
}

/******************************************************************************/
/*!
\brief - Logic Init function
\param gd - Game data
*/
/******************************************************************************/
void Logic::Init(const ObjectList& objList, GameData& gd)
{
	// Init all object's logic data
	for (auto it = objList.begin(); it != objList.end(); ++it)
	{
		for (auto logic_it = (*it).second->GetLogicList().begin();
			logic_it != (*it).second->GetLogicList().end(); ++logic_it)
			(*logic_it).second->Init(gd);
	}
}

/******************************************************************************/
/*!
\brief - Logic Update function
\param gd - Game data
*/
/******************************************************************************/
void Logic::Update(const ObjectList& objList, GameData& gd)
{
	// Update all object's logic data
	for (auto it = objList.begin(); it != objList.end(); ++it)
	{
		for (auto logic_it = (*it).second->GetLogicList().begin();
			logic_it != (*it).second->GetLogicList().end(); ++logic_it)
				(*logic_it).second->Update(gd);
	}
}

/******************************************************************************/
/*!
\brief - Logic Shutdown function
\param gd - Game data
*/
/******************************************************************************/
void Logic::Shutdown(const ObjectList& objList, GameData& gd)
{
	// Shutdown all object's logic data
	for (auto it = objList.begin(); it != objList.end(); ++it)
	{
		for (auto logic_it = (*it).second->GetLogicList().begin();
			logic_it != (*it).second->GetLogicList().end(); ++logic_it)
			(*logic_it).second->Shutdown(gd);
	}
}

/******************************************************************************/
/*!
\brief - Logic Unload function
*/
/******************************************************************************/
void Logic::Unload(const ObjectList& objList)
{
	// Shutdown all object's logic data
	for (auto it = objList.begin(); it != objList.end(); ++it)
	{
		for (auto logic_it = (*it).second->GetLogicList().begin();
			logic_it != (*it).second->GetLogicList().end(); ++logic_it)
			(*logic_it).second->Unload();
	}
}
