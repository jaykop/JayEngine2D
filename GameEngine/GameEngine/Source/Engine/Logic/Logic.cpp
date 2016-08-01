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

void Logic::Init(/*const ObjectList& objList*/)
{
	//for (auto it_1 = objList.begin(); it_1 != objList.end(); ++it_1)
	//{
	//	// Get sprite's logic list
	//	auto new_list = it_1->second->GetLogicList();

	//	// Update sprite's logic
	//	for (auto it_2 = new_list.begin(); it_2 != new_list.end(); ++it_2)
	//		it_2->second->Init();
	//}

	for (auto it = m_logicList.begin(); it != m_logicList.end(); ++it)
		(*it)->Init();
}

void Logic::Update(/*const ObjectList& objList*/)
{
	//// Load sprite list
	//for (auto it_1 = objList.begin(); it_1 != objList.end(); ++it_1)
	//{
	//	// Get sprite's logic list
	//	auto new_list = it_1->second->GetLogicList();

	//	// Update sprite's logic
	//	for (auto it_2 = new_list.begin(); it_2 != new_list.end(); ++it_2)
	//		it_2->second->Update();
	//}

	for (auto it = m_logicList.begin(); it != m_logicList.end(); ++it)
		(*it)->Update();
}

void Logic::Shutdown(/*const ObjectList& objList*/)
{
	//for (auto it_1 = objList.begin(); it_1 != objList.end(); ++it_1)
	//{
	//	// Get sprite's logic list
	//	auto new_list = it_1->second->GetLogicList();

	//	// Update sprite's logic
	//	for (auto it_2 = new_list.begin(); it_2 != new_list.end(); ++it_2)
	//		it_2->second->Shutdown();
	//}

	for (auto it = m_logicList.begin(); it != m_logicList.end(); ++it)
		(*it)->Shutdown();
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