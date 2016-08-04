/******************************************************************************/
/*!
\file   GameLogic.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/01(yy/mm/dd)

\description
Contains GameLogic's member functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "GameLogic.h"

//! Init static logic's key
int GameLogic::m_key = 0;

/******************************************************************************/
/*!
\brief - Get logic's key
\return m_key - Logic's original id number
*/
/******************************************************************************/
int GameLogic::GetKey(void)
{ 
	return m_key; 
}