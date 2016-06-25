/******************************************************************************/
/*!
\file   Text.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/20(yy/mm/dd)

\description
Contains Text's class and member functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Text.h"
#include "../ObjectManager/ObjectManager.h"

Text::Text(const int id, Type type, ObjectManager* obm)
{
	SetScale(vec3(1.f, 1.f, 1.f));
	SetColor(vec4(0.f, 0.0f, 0.0f, 1.f));
	SetObjectType(type);
	SetObjectManager(obm); 
	SetProjectionType(ORTHOGONAL);
	SetID(id);
}

Text::~Text(void)
{}

void Text::SetText(const wchar_t* text)
{
	m_text = text;
}

const std::wstring& Text::GetText(void) const
{
	return m_text;
}
