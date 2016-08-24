/******************************************************************************/
/*!
\file   LogicFactory.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/25(yy/mm/dd)

\description
Contains LogicFactory's class and member function

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

#include "LogicFactory.h"
#include "../LogicBuilder.h"
#include "../../Utilities/Debug/Debug.h"

//! Init static builder map
std::map <int, LogicBuilder*> LogicFactory::m_builderMap;

/******************************************************************************/
/*!
\brief - Factory Destrutor
*/
/******************************************************************************/
LogicFactory::~LogicFactory(void)
{
	ClearBuilderMap();
}

/******************************************************************************/
/*!
\brief - Add Builder
\param key - Logic builder key
\param pBuilder - pointer to the builder
*/
/******************************************************************************/
void LogicFactory::AddBuilder(int key, LogicBuilder* pBuilder)
{
	//Find if there is existing stage 
	//If there is, assert
	DEBUG_ASSERT(m_builderMap.find(key) == m_builderMap.end(), "Error: Logic Duplication!");

	//Unless, make new builder
	if (pBuilder)
		m_builderMap[key] = pBuilder;
}

/******************************************************************************/
/*!
\brief - Clear the builder map
*/
/******************************************************************************/
void LogicFactory::ClearBuilderMap(void)
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
\param key - Logic builder key
\param owner - Logic of owner object
*/
/******************************************************************************/
GameLogic* LogicFactory::CreateLogic(int key, Object* owner)
{
	auto bulider = m_builderMap.find(key)->second;
	
	//if there is, return new logic
	if (bulider)
		return bulider->BuildLogic(owner);

	return nullptr;
}