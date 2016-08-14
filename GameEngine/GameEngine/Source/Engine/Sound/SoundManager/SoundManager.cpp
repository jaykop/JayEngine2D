/******************************************************************************/
/*!
\file   SoundManager.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/26(yy/mm/dd)

\description
Contains SoundManager's class member functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "../Audio.h"
#include "SoundManager.h"
#include "../../App/Application.h"
#include "../../Utilities/Debug/Debug.h"

/******************************************************************************/
/*!
\brief - SoundManager Constructor
*/
/******************************************************************************/
SoundManager::SoundManager(void)
:m_system(0)
{}

/******************************************************************************/
/*!
\brief - SoundManager Destructor
*/
/******************************************************************************/
SoundManager::~SoundManager(void)
{
	ClearSoundMap();
	m_system->release();
	m_system->close();
}

/******************************************************************************/
/*!
\brief - Initialize SoundManager
\param pApp - pointer to application
\param size - The number of sound to load
*/
/******************************************************************************/
void SoundManager::InitFMOD(Application* pApp, int size)
{
	FMOD::System_Create(&m_system);
	FMOD_RESULT result = m_system->init(size, FMOD_INIT_NORMAL, 0);
	ErrorCheck(pApp, result);
}

/******************************************************************************/
/*!
\brief - Check sound's error
\param pApp - pointer to application
\param result - function's result
*/
/******************************************************************************/
void SoundManager::ErrorCheck(Application* pApp, FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		MessageBox(NULL, "Failed to init basic sound system.",
			"FMOD Error", MB_OK);
		pApp->Quit();
	}
}

/******************************************************************************/
/*!
\brief - Get fmod's m_system
\return m_system
*/
/******************************************************************************/
FMOD::System* SoundManager::GetSystem(void)
{
	return m_system;
}

/******************************************************************************/
/*!
\brief - Get pointer to sound
\param key - sound key
\return m_sound
*/
/******************************************************************************/
FMOD::Sound* SoundManager::GetSound(int key)
{
	auto found = m_audioMap.find(key)->second;

	if (found)
		return m_audioMap[key]->m_sound;

	return nullptr;
}

/******************************************************************************/
/*!
\brief - Get pointer to channel
\param key - sound key
\return m_channel
*/
/******************************************************************************/
FMOD::Channel*  SoundManager::GetChannel(int key)
{
	auto found = m_audioMap.find(key)->second;

	if (found)
		return m_audioMap[key]->m_channel;

	return nullptr;
}

/******************************************************************************/
/*!
\brief - Get pointer to sound
\param key - sound key
\param SoundDir - sound type
*/
/******************************************************************************/
void SoundManager::AddSound(int key, const char* SoundDir)
{
	//Find if there is existing stage 
	//If there is, assert
	DEBUG_ASSERT(m_audioMap.find(key) == m_audioMap.end(), "Error: Logic Duplication!");

	//Unless, make new builder
	m_audioMap[key] = new Audio(m_system);
	m_system->createSound(SoundDir, FMOD_HARDWARE, 0, &m_audioMap[key]->m_sound);
}

/******************************************************************************/
/*!
\brief - Clear sound map
*/
/******************************************************************************/
void SoundManager::ClearSoundMap(void)
{
	for (auto it = m_audioMap.begin(); it != m_audioMap.end(); ++it)
	{
		delete it->second;
		it->second = 0;
	}

	m_audioMap.clear();
}

/******************************************************************************/
/*!
\brief - Get Audio Map
\return m_audioMap
*/
/******************************************************************************/
AudioMap& SoundManager::GetAudioMap(void)
{
	return m_audioMap;
}