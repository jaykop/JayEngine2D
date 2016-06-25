/******************************************************************************/
/*!
\file   Object.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Object's class functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Object.h"

Object::Object(const int id, Type type)
: m_id(id), m_type(type)
{}

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
\brief - Get Object;s type

\return m_type - Object's shape
*/
/******************************************************************************/
Type Object::GetObjectType(void) const
{
	return m_type;
}

/******************************************************************************/
/*!
\brief - Set Object;s type

\param type - Object's type
*/
/******************************************************************************/
void Object::SetObjectType(Type type)
{
	m_type = type;
}
