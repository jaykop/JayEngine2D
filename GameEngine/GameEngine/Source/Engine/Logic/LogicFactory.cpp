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

std::map <std::string, LogicBuilder*> LogicFactory::m_builderMap;

/******************************************************************************/
/*!
\brief - Factory Destrutor
*/
/******************************************************************************/
LogicFactory::~LogicFactory(void)
{
	DeleteAllBuilders();
}

/******************************************************************************/
/*!
\brief - Add Builder

\param stage - stage to make
\param pBuilder - pointer to the builder

*/
/******************************************************************************/
void LogicFactory::AddBuilder(const std::string& name, LogicBuilder* pBuilder)
{
	//Find if there is existing stage 
	//If there is, assert
	DEBUG_ASSERT(m_builderMap.find(name) == m_builderMap.end(), "Error: Logic Duplication!");

	//Unless, make new builder
	if (pBuilder)
		m_builderMap[name] = pBuilder;
}

/******************************************************************************/
/*!
\brief - Clear the builder map
*/
/******************************************************************************/
void LogicFactory::DeleteAllBuilders(void)
{
	for (auto it = m_builderMap.begin(); it != m_builderMap.end(); ++it)
	{
		delete it->second;
		it->second = 0;
	}

	m_builderMap.clear();
}

/******************************************************************************/
/*!
\brief - Create stage

\param stage - stage to make
\param GSM - GSM to puint to the stage

*/
/******************************************************************************/
GameLogic* LogicFactory::CreateLogic(const std::string& name, Object* owner)
{
	auto bulider = m_builderMap.find(name)->second;
	
	//if there is, return new logic
	if (bulider)
		return bulider->BuildLogic(owner);

	return nullptr;
}