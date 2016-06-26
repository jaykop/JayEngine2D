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

SoundManager::SoundManager(void)
:m_channel(0), m_system(0)
{
	// Init all sound pointers
	for (int i = 0; i < SOUND_END; ++i)
		m_sound[i] = 0;
}

SoundManager::~SoundManager(void)
{
	m_system->release();
	m_system->close();
}

void SoundManager::Init(/*const int numOfchannel*/)
{
	FMOD::System_Create(&m_system);
	m_system->init(1, FMOD_INIT_NORMAL, 0);
	//m_system->init(numOfchannel, FMOD_INIT_NORMAL, 0);
}

void SoundManager::Load(const char* SoundDir, SoundData sound)
{
	m_system->createSound(SoundDir, FMOD_HARDWARE, 0, &m_sound[sound]);
}

void SoundManager::Play()
{
	m_system->playSound(FMOD_CHANNEL_FREE, m_sound[SE_1], false, &m_channel);
}

void SoundManager::Stop()
{}

void SoundManager::ErrorCheck()
{}

//void SoundManager::SetVolume()
//{}

FMOD::System* SoundManager::GetSystem(void)
{
	return m_system;
}

FMOD::Channel* SoundManager::GetChannel(void)
{
	return m_channel;
}

FMOD::Sound* SoundManager::GetSound(const SoundData s_data)
{
	return m_sound[s_data];
}
