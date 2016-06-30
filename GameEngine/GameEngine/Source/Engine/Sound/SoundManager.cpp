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

#include "SoundManager.h"
#include "../App/Application.h"
#include "../Utilities/Debug/Debug.h"

/******************************************************************************/
/*!
\brief - SoundManager Constructor
*/
/******************************************************************************/
SoundManager::SoundManager(void)
:m_system(0)
{
	// Init all sound pointers
	for (int i = 0; i < SOUND_END; ++i) {
		m_sound[i] = 0;
	}
}

/******************************************************************************/
/*!
\brief - SoundManager Destructor
*/
/******************************************************************************/
SoundManager::~SoundManager(void)
{
	m_system->release();
	m_system->close();
}

/******************************************************************************/
/*!
\brief - Initialize SoundManager
\param pApp - pointer to application
*/
/******************************************************************************/
void SoundManager::InitFMOD(Application* pApp)
{
	FMOD::System_Create(&m_system);
	FMOD_RESULT result = m_system->init(SOUND_END, FMOD_INIT_NORMAL, 0);
	ErrorCheck(pApp, result);
}

/******************************************************************************/
/*!
\brief - Load sounds 
\param SoundDir - sound's directory
\param sound - sound type
*/
/******************************************************************************/
void SoundManager::Load(const char* SoundDir, SoundData sound)
{
	m_system->createSound(SoundDir, FMOD_HARDWARE, 0, &m_sound[sound]);
}

/******************************************************************************/
/*!
\brief - Check sound's error
\param result - function's result
\param pApp - pointer to application
*/
/******************************************************************************/
void SoundManager::ErrorCheck(Application* pApp, FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		MessageBox(NULL, L"Failed to init basic sound system.",
			L"FMOD Error", MB_OK);
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
\param soundData - sound type
\return m_sound
*/
/******************************************************************************/
FMOD::Sound* SoundManager::GetSound(const SoundData soundData)
{
	return m_sound[soundData];
}