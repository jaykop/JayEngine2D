#include "InputManager.h"

InputManager::InputManager(void)
{
	for (unsigned index = 0; index < KEY_LAST; ++index)
		m_key.insert(std::make_pair(index, false));
	

	m_pressedInput = 0;
	m_triggeredInput = 0;
	m_anykey = false;
	m_trigger = true;
	m_status = UP;
}

InputManager::~InputManager(void)
{

}

INPUT_KEY InputManager::KeyTranslator(WPARAM user_input)
{
	//Translate key to enum
	INPUT_KEY KeyID;
	KeyID = static_cast<INPUT_KEY>(user_input);

	return KeyID;
}

bool InputManager::KeyTriggered(WPARAM input_tobe)
{
	if (m_key[input_tobe] && m_trigger)
		return true;

	return false;
}

bool InputManager::KeyPressed(WPARAM input_tobe)
{
	//Compare input to be type to real user input
	if (m_key[input_tobe])
		return true;
	
	return false;
}

void InputManager::PressActivate(INPUT_KEY user_input)
{
	m_key[user_input] = true;
	m_anykey = true;
}

void InputManager::PressInactivate(INPUT_KEY user_input)
{
	m_key[user_input] = false;
	m_anykey = false;
}

void InputManager::SetTriggerToggle(bool toggle)
{
	m_trigger = toggle;
}

bool InputManager::AnyKeyPressed(void)
{
	return m_anykey;
}

bool InputManager::AnyKeyTriggered(void)
{
	if (m_trigger && m_anykey)
	{
		m_trigger = false;
		return m_anykey;
	}

	return false;
}

PRESSED_STATUS InputManager::GetPressedStatus(void) const 
{
	return m_status;
}

void InputManager::SetPressedStatus(PRESSED_STATUS status)
{
	m_status = status;
}

void InputManager::GetRawMousePosition(WORD xPos, WORD yPos)
{
	m_position.x = static_cast<float>(xPos);
	m_position.y = static_cast<float>(yPos);
}

vec3 InputManager::GetMousePosition(void) const
{
	return m_position;
}