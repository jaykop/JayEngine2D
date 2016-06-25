/******************************************************************************/
/*!
\file   Factory.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Factory's class and member function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "StageFactory.h"
#include "../StageBuilder.h"
#include "../../Utilities/Debug/Debug.h"

/******************************************************************************/
/*!
\brief - Factory Destrutor
*/
/******************************************************************************/
StageFactory::~StageFactory(void)
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
void StageFactory::AddBuilder(StageType stage, StageBuilder* pBuilder)
{
	//Find if there is existing stage 
	auto found = m_builderMap.find(stage);
	
	//If there is, assert
	DEBUG_ASSERT(found == m_builderMap.end(), "Error: Stage Duplication!");

	//Unless, make new builder
	m_builderMap.insert(std::make_pair(stage, pBuilder));
}

/******************************************************************************/
/*!
\brief - Delete Builder

\param stage - stage to delete

*/
/******************************************************************************/
void StageFactory::DeleteBuilder(StageType stage)
{
	//I do not understand why we need this

	//Find if there is existing stage 
	auto found = m_builderMap.find(stage);
	
	//If there is not, assert
	DEBUG_ASSERT(found != m_builderMap.end(), "Error: Not Existing Stage!");
	
	//if there is, erase
	m_builderMap.erase(stage);
}

/******************************************************************************/
/*!
\brief - Clear the builder map
*/
/******************************************************************************/
void StageFactory::Clear()
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
Stage* StageFactory::CreateStage(StageType stage, GameStateManager* GSM)
{
	//Find if there is existing stage 
	auto found = m_builderMap.find(stage);

	//If there is not, assert
	DEBUG_ASSERT(found != m_builderMap.end(), "Error: Not Existing Stage!");

	//if there is, erase
	return found->second->BuildStage(GSM);
}