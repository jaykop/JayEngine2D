/******************************************************************************/
/*!
\file   Sound.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/26(yy/mm/dd)

\description
Contains Sound class member and functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Sound.h"
#include "Audio/Audio.h"
#include "../StateManager/GameStateManager/GameStateManager.h"

/******************************************************************************/
/*!
\brief - Sound Constructor
\param gsm - pointer to gamestate manager
*/
/******************************************************************************/
Sound::Sound(GameStateManager* gsm)
: m_GSM(gsm), m_SM(gsm->GetSoundManager()),
m_system(gsm->GetSoundManager()->GetSystem()),
m_MasterToggle(true), m_MasterVolume(.5f)
{
	// Get audiomap form manager
	m_audioMap = &m_SM->GetAudioMap();
}

/******************************************************************************/
/*!
\brief - Sound Destructor
*/
/******************************************************************************/
Sound::~Sound(void)
{}

/******************************************************************************/
/*!
\brief - Initialize Sound 
*/
/******************************************************************************/
void Sound::Init(void)
{

}

/******************************************************************************/
/*!
\brief - Update Sound
*/
/******************************************************************************/
void Sound::Update(void)
{
	//Update all audios' volume
	for (auto it = m_audioMap->begin();
		it != m_audioMap->end(); ++it)
		it->second->m_channel->setVolume(it->second->GetVolume());

	m_GSM->GetSoundManager()->GetSystem()->update();
}

/******************************************************************************/
/*!
\brief - Shutdown Sound
*/
/******************************************************************************/
void Sound::Shutdown(void)
{

}

/******************************************************************************/
/*!
\brief - Get audio
*/
/******************************************************************************/
Audio* Sound::GetAudio(int key)
{
	auto found = m_audioMap->find(key)->second;
	return found;
}

/******************************************************************************/
/*!
\brief - Set all audios' play toggle
\param toggle
*/
/******************************************************************************/
void Sound::SetMasterMuteToggle(bool toggle)
{
	m_MasterToggle = toggle;
	for (auto it = m_audioMap->begin();
		it != m_audioMap->end(); ++it)
		it->second->SetMuteToggle(m_MasterToggle);
}

/******************************************************************************/
/*!
\brief - Get master play toggle
\return m_MasterToggle
*/
/******************************************************************************/
bool  Sound::GetMasterMuteToggle(void) const
{
	return m_MasterToggle;
}

/******************************************************************************/
/*!
\brief - Set all audios' volume
\param volume
*/
/******************************************************************************/
void Sound::SetMasterVolume(float volume)
{
	m_MasterVolume = volume;
	for (auto it = m_audioMap->begin();
		it != m_audioMap->end(); ++it)
		it->second->m_channel->setVolume(m_MasterVolume);
}

/******************************************************************************/
/*!
\brief - Get master volume
\return m_MasterVolume
*/
/******************************************************************************/
float Sound::GetMasterVolume(void) const
{
	return m_MasterVolume;
}