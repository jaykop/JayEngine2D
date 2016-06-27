/******************************************************************************/
/*!
\file   InputManager.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains InputManager's class and member function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "InputManager.h"

/******************************************************************************/
/*!
\brief - InputManager Constructor

*/
/******************************************************************************/
InputManager::InputManager(void)
{
	//Initialize member info
	for (unsigned index = 0; index < KEY_LAST; ++index)
		m_key.insert(std::make_pair(index, false));

	m_pressedInput = 0;
	m_triggeredInput = 0;
	m_anykey = false;
	m_trigger = true;
	m_status = UP;
}

/******************************************************************************/
/*!
\brief - InputManager destructor

*/
/******************************************************************************/
InputManager::~InputManager(void)
{}

/******************************************************************************/
/*!
\brief - Translate input key 

\param user_input - raw input

\return KeyID
*/
/******************************************************************************/
INPUT_KEY InputManager::KeyTranslator(WPARAM user_input)
{
	//Translate key to enum
	INPUT_KEY KeyID;
	KeyID = static_cast<INPUT_KEY>(user_input);

	return KeyID;
}

/******************************************************************************/
/*!
\brief - Get triggered input key

\param input_tobe - raw input

\return bool
*/
/******************************************************************************/
bool InputManager::KeyTriggered(WPARAM input_tobe)
{
	if (m_key[input_tobe] && m_trigger)
	{
		m_key[input_tobe] = false;
		return true;
	}

	return false;
}

/******************************************************************************/
/*!
\brief - Get pressed input key

\param input_tobe - raw input

\return bool
*/
/******************************************************************************/
bool InputManager::KeyPressed(WPARAM input_tobe)
{
	//Compare input to be type to real user input
	if (m_key[input_tobe])
		return true;
	
	return false;
}

/******************************************************************************/
/*!
\brief - Set valid pressed input key

\param input_tobe - raw input

*/
/******************************************************************************/
void InputManager::PressActivate(INPUT_KEY user_input)
{
	m_key[user_input] = true;
	m_anykey = true;
}

/******************************************************************************/
/*!
\brief - Check invalid pressed input key

\param input_tobe - raw input

*/
/******************************************************************************/
void InputManager::PressInactivate(INPUT_KEY user_input)
{
	m_key[user_input] = false;
	m_anykey = false;
}

/******************************************************************************/
/*!
\brief - Set Trigger Toggle

\param toggle - set trigger toggle

*/
/******************************************************************************/
void InputManager::SetTriggerToggle(bool toggle)
{
	m_trigger = toggle;
}

/******************************************************************************/
/*!
\brief - Check any pressed input key

\return m_anykey

*/
/******************************************************************************/
bool InputManager::AnyKeyPressed(void)
{
	return m_anykey;
}

/******************************************************************************/
/*!
\brief - Check any tirggered input key

\return bool

*/
/******************************************************************************/
bool InputManager::AnyKeyTriggered(void)
{
	if (m_trigger && m_anykey)
	{
		m_trigger = false;
		return m_anykey;
	}

	return false;
}

/******************************************************************************/
/*!
\brief - Get Pressed Input Status

\return m_status

*/
/******************************************************************************/
PRESSED_STATUS InputManager::GetPressedStatus(void) const 
{
	return m_status;
}

/******************************************************************************/
/*!
\brief - Set Pressed Input Status

\param status

*/
/******************************************************************************/
void InputManager::SetPressedStatus(PRESSED_STATUS status)
{
	m_status = status;
}

/******************************************************************************/
/*!
\brief - Set Raw Mouse Position

\param xPos - mouse's x position
\param yPos - mouse's y position
*/
/******************************************************************************/
void InputManager::SetRawMousePosition(WORD xPos, WORD yPos)
{
	m_position.x = static_cast<float>(xPos);
	m_position.y = static_cast<float>(yPos);
}

/******************************************************************************/
/*!
\brief - Get Raw Mouse Position

\return m_position

*/
/******************************************************************************/
const vec3& InputManager::GetRawMousePosition(void) const
{
	return m_position;
}

/******************************************************************************/
/*!
\brief - Get Perspective Mouse Position

\return m_perspPos

*/
/******************************************************************************/
const vec3& InputManager::GetPerspPosition(void) const
{
	return m_perspPos;
}

/******************************************************************************/
/*!
\brief - Get Ortho Mouse Position

\return m_orthoPod

*/
/******************************************************************************/
const vec3& InputManager::GetOrthoPosition(void) const
{
	return m_orthoPos;
}

/******************************************************************************/
/*!
\brief - Set Perspective Mouse Position

\param pos -  Ortho Perspective Position
*/
/******************************************************************************/
void InputManager::SetPerspMouse(const vec3& pos)
{
	m_perspPos = pos;
}

/******************************************************************************/
/*!
\brief - Set Ortho Mouse Position

\param pos -  Ortho Mouse Position
*/
/******************************************************************************/
void InputManager::SetOrthoMouse(const vec3& pos)
{
	m_orthoPos = pos;
}