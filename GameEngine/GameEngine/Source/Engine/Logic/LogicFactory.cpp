/******************************************************************************/
/*!
\file   LogicFactory.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/25(yy/mm/dd)

\description
Contains LogicFactory's class and member function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "LogicFactory.h"
#include "LogicBuilder.h"
#include "../Utilities/Debug/Debug.h"

/******************************************************************************/
/*!
\brief - Factory Destrutor
*/
/******************************************************************************/
LogicFactory::~LogicFactory(void)
{
	Clear();
}

/******************************************************************************/
/*!
\brief - Add Builder

\param stage - stage to make
\param pBuilder - pointer to the builder

*/
/******************************************************************************/
void LogicFactory::AddBuilder(GameLogic* logic, LogicBuilder* pBuilder)
{
	//Find if there is existing stage 
	auto found = m_builderMap.find(logic);

	//If there is, assert
	DEBUG_ASSERT(found == m_builderMap.end(), "Error: Stage Duplication!");

	//Unless, make new builder
	m_builderMap.insert(std::make_pair(logic, pBuilder));
}

/******************************************************************************/
/*!
\brief - Delete Builder

\param stage - stage to delete

*/
/******************************************************************************/
void LogicFactory::DeleteBuilder(GameLogic* logic)
{
	//I do not understand why we need this

	//Find if there is existing stage 
	auto found = m_builderMap.find(logic);

	//If there is not, assert
	DEBUG_ASSERT(found != m_builderMap.end(), "Error: Not Existing Stage!");

	//if there is, erase
	m_builderMap.erase(logic);
}

/******************************************************************************/
/*!
\brief - Clear the builder map
*/
/******************************************************************************/
void LogicFactory::Clear()
{
	for (auto it = m_builderMap.begin(); it != m_builderMap.end(); ++it)
		delete it->second;

	m_builderMap.clear();
}

/******************************************************************************/
/*!
\brief - Create stage

\param stage - stage to make
\param GSM - GSM to puint to the stage

*/
/******************************************************************************/
GameLogic* LogicFactory::CreateLogic(GameLogic* logic, GameStateManager* GSM)
{
	//Find if there is existing stage 
	auto found = m_builderMap.find(logic);

	//If there is not, assert
	DEBUG_ASSERT(found != m_builderMap.end(), "Error: Not Existing Stage!");

	//if there is, erase
	return found->second->BuildLogic(GSM);
}