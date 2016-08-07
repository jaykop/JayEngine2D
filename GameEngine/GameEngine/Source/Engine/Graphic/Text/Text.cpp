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
#include "../GLManager/GLManager.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../StateManager/GameStateManager/GameStateManager.h"

/******************************************************************************/
/*!
\brief - Sprite's Constructor
*/
/******************************************************************************/
Text::Text(const int id, ObjectManager* obm)
:Sprite(id, obm)
{
	//SetID(id);
	SetType(TEXT);
	//SetObjectManager(obm); 
	SetProjectionType(ORTHOGONAL);
	SetScale(vec3(1.f, 1.f, 1.f));
	SetColor(vec4(0.f, 0.0f, 0.0f, 1.f));
}
/******************************************************************************/
/*!
\brief - Text's Copy Constructor
*/
/******************************************************************************/
Text::Text(Text& text)
:Sprite(text)
{
	//m_fontSize = text.m_fontSize;
	m_text.assign(text.m_text);
}

/******************************************************************************/
/*!
\brief - Text's Destructor
*/
/******************************************************************************/
Text::~Text(void)
{
	ClearLogicList();
}

/******************************************************************************/
/*!
\brief - Set text
\param text
*/
/******************************************************************************/
void Text::SetText(const char* text)
{
	m_text = text;
}

/******************************************************************************/
/*!
\brief - Get text
\return m_text
*/
/******************************************************************************/
const std::string& Text::GetText(void) const
{
	return m_text;
}

///******************************************************************************/
///*!
//\brief - Set text font size
//\param size
//*/
///******************************************************************************/
//void Text::SetFontSize(float size)
//{
//	m_fontSize = size;
//}
//
///******************************************************************************/
///*!
//\brief - Get text font size
//\return fontSize
//*/
///******************************************************************************/
//float Text::GetFontSize(void)
//{
//	return m_fontSize;
//}