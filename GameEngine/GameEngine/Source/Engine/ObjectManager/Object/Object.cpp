/******************************************************************************/
/*!
\file   Object.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/25(yy/mm/dd)

\description
Contains Object's class functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Object.h"
#include "../ObjectManager.h"
#include "../../Logic/GameLogic.h"

/******************************************************************************/
/*!
\brief - Object's constructor
\param id - Object's id
\param type - Object's type
\param obm - Pointer to object manager
*/
/******************************************************************************/
Object::Object(const int id, Type type, ObjectManager* obm)
: m_id(id), m_type(type), m_OBM(obm)
{}

/******************************************************************************/
/*!
\brief - Object's Destructor
*/
/******************************************************************************/
Object::~Object()
{}

/******************************************************************************/
/*!
\brief - Get Object's id

\return m_id - Object's id
*/
/******************************************************************************/
const int Object::GetID(void) const
{
	return m_id;
}

/******************************************************************************/
/*!
\brief - Set Object's id

\param id - Object's id
*/
/******************************************************************************/
void Object::SetID(const int id)
{
	m_id = id;
}

/******************************************************************************/
/*!
\brief - Get Object's type

\return m_type - Object's shape
*/
/******************************************************************************/
Type Object::GetObjectType(void) const
{
	return m_type;
}

/******************************************************************************/
/*!
\brief - Set Object's type

\param type - Object's type
*/
/******************************************************************************/
void Object::SetObjectType(Type type)
{
	m_type = type;
}

/******************************************************************************/
/*!
\brief - Set Object manager

\param obm - Pointer to Object manager
*/
/******************************************************************************/
void Object::SetObjectManager(ObjectManager* obm)
{
	m_OBM = obm;
}

void Object::ClearLogicList(void)
{
	for (auto it = m_logicList.begin(); it != m_logicList.end(); ++it)
		delete it->second;

	m_logicList.clear();
}

void Object::AddLogic(GameLogic* logic)
{
	const char* name = typeid(logic).name();
	m_logicList[name] = logic;
}

const LogicList& Object::GetLogicList(void) const
{
	return m_logicList;
}