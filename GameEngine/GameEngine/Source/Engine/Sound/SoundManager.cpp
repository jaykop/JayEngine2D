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
#include "../Utilities/Debug/Debug.h"

SoundManager::SoundManager(void)
:m_system(0)
{
	// Init all sound pointers
	for (int i = 0; i < SOUND_END; ++i) {
		m_sound[i] = 0;
	}
}

SoundManager::~SoundManager(void)
{
	m_system->release();
	m_system->close();
}

void SoundManager::Init()
{
	FMOD::System_Create(&m_system);
	m_system->init(SOUND_END, FMOD_INIT_NORMAL, 0);
}

void SoundManager::Load(const char* SoundDir, SoundData sound)
{
	m_system->createSound(SoundDir, FMOD_HARDWARE, 0, &m_sound[sound]);
}

void SoundManager::ErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
		MessageBox(NULL, L"Failed to init basic sound system.",
			L"FMOD Error", MB_OK);
}

FMOD::System* SoundManager::GetSystem(void)
{
	return m_system;
}

FMOD::Sound* SoundManager::GetSound(const SoundData soundData)
{
	return m_sound[soundData];
}