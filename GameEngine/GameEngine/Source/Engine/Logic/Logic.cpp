/******************************************************************************/
/*!
\file   Logic.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/25(yy/mm/dd)

\description
Contains Logic's class and member function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Logic.h"
#include "GameLogic.h"

Logic::Logic(void)
{}

Logic::~Logic(void)
{}

void Logic::Init(GameData& gd)
{
	for (auto it = m_logicList.begin(); it != m_logicList.end(); ++it)
		(*it)->Init(gd);
}

void Logic::Update(GameData& gd)
{
	for (auto it = m_logicList.begin(); it != m_logicList.end(); ++it)
		(*it)->Update(gd);
}

void Logic::Shutdown(GameData& gd)
{
	for (auto it = m_logicList.begin(); it != m_logicList.end(); ++it)
		(*it)->Shutdown(gd);
}

void Logic::AddLogic(GameLogic* logic)
{
	m_logicList.push_back(logic);
}

void Logic::RemoveLogic(GameLogic* logic)
{
	for (auto it = m_logicList.begin(); it != m_logicList.end(); ++it)
	{
		if (*it == logic)
		{
			m_logicList.erase(it++);
			break;
		}
	}
}

void Logic::ClearLogicList(void)
{
	m_logicList.clear();
}

const LogicList& Logic::GetLogicList(void) const
{
	return m_logicList;
}