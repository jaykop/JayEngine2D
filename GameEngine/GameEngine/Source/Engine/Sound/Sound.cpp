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
m_BGMToggle(true), m_SEToggle(true), m_MasterToggle(true),
m_BGMVolume(.5f), m_SEVolume(.5f), m_MasterVolume(.5f)
{
	// Init all channels
	for (int i = 0; i < TYPE_END; ++i) {
		m_channel[i] = 0;
	}
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
\brief - Play background Sound
\param sound - sound type
*/
/******************************************************************************/
void Sound::PlayBGM(int key)
{
	auto found = m_SM->GetSound(key);

	if (m_BGMToggle)
		m_system->playSound(FMOD_CHANNEL_FREE, found, false, &m_channel[BGM]);
}

/******************************************************************************/
/*!
\brief - Stop background Sound
*/
/******************************************************************************/
void Sound::StopBGM(void)
{
	m_channel[BGM]->stop();
}

/******************************************************************************/
/*!
\brief - Pause background Sound
\param sound - sound type
*/
/******************************************************************************/
void Sound::PauseBGM(bool boolean)
{
	m_channel[BGM]->setPaused(boolean);
}

/******************************************************************************/
/*!
\brief - Play Sound effect
\param sound - sound type
*/
/******************************************************************************/
void Sound::PlaySE(int key)
{
	auto found = m_SM->GetSound(key);

	if (m_SEToggle)
		m_system->playSound(FMOD_CHANNEL_FREE, found, false, &m_channel[SE]);
}

/******************************************************************************/
/*!
\brief - Stop Sound effect
*/
/******************************************************************************/
void Sound::StopSE(void)
{
	m_channel[SE]->stop();
}

/******************************************************************************/
/*!
\brief - Pause Sound effect
\param sound - sound type
*/
/******************************************************************************/
void Sound::PauseSE(bool boolean)
{
	m_channel[SE]->setPaused(boolean);
}

/******************************************************************************/
/*!
\brief - Get sound effect Mute Toggle
\return m_SEToggle
*/
/******************************************************************************/
bool Sound::GetSEMuteToggle(void) const
{
	return m_SEToggle;
}

/******************************************************************************/
/*!
\brief - Get BGM Mute Toggle
\return m_BGMToggle
*/
/******************************************************************************/
bool Sound::GetBGMMuteToggle(void) const
{
	return m_BGMToggle;
}

/******************************************************************************/
/*!
\brief - Get Master Mute Toggle
\return m_MasterToggle
*/
/******************************************************************************/
bool Sound::GetMasterMuteToggle(void) const
{
	return m_MasterToggle;
}

/******************************************************************************/
/*!
\brief - Set sound effect Mute Toggle
\param toggle - sound toggle
*/
/******************************************************************************/
void Sound::SetSEMuteToggle(bool toggle)
{
	// Set mute toggle
	m_SEToggle = toggle;
	m_channel[SE]->setMute(m_SEToggle);

	//If toggle is false, Stop current sound
	m_channel[SE]->setPaused(!m_SEToggle);

	// Set Master toggle
	if (toggle)
		m_MasterToggle = toggle;
}

/******************************************************************************/
/*!
\brief - Set background music Mute Toggle
\param toggle - sound toggle
*/
/******************************************************************************/
void Sound::SetBGMMuteToggle(bool toggle)
{
	// Set mute toggle
	m_BGMToggle = toggle;
	m_channel[BGM]->setMute(m_BGMToggle);

	//If toggle is false, Stop current sound
	m_channel[BGM]->setPaused(!m_BGMToggle);

	// Set Master toggle
	if (toggle)
		m_MasterToggle = toggle;
}

/******************************************************************************/
/*!
\brief - Set Master Mute Toggle
\param toggle - sound toggle
*/
/******************************************************************************/
void Sound::SetMasterMuteToggle(bool toggle)
{
	// Set all toggles
	m_SEToggle = m_BGMToggle = m_MasterToggle = toggle;
	m_channel[BGM]->setMute(m_BGMToggle);
	m_channel[SE]->setMute(m_SEToggle);

	//Stop current sounds
	m_channel[BGM]->setPaused(!m_BGMToggle);
	m_channel[SE]->setPaused(!m_SEToggle);
}

/******************************************************************************/
/*!
\brief - Get sound effect Volume
\return m_SEVolume
*/
/******************************************************************************/
float Sound::GetSEVolume(void) const
{
	return m_SEVolume;
}

/******************************************************************************/
/*!
\brief - Get background music Volume
\return m_BGMVolume
*/
/******************************************************************************/
float Sound::GetBGMVolume(void) const
{
	return m_BGMVolume;
}

/******************************************************************************/
/*!
\brief - Get Master Volume 
\return m_MasterVolume 
*/
/******************************************************************************/
float Sound::GetMasterVolume(void) const
{
	return m_MasterVolume;
}

/******************************************************************************/
/*!
\brief - Set sound effect Volume
\param volume - sound volume
*/
/******************************************************************************/
void Sound::SetSEVolume(float volume)
{
	// Control the range of volume
	if (volume < 0) volume = 0;
	else if (volume > 1) volume = 1;
	m_SEVolume = volume;

	// Set master volume 
	m_MasterVolume = m_SEVolume > m_BGMVolume ? m_SEVolume : m_BGMVolume;

	//Set channel
	m_channel[SE]->setVolume(m_SEVolume);
	m_channel[SE]->setPaused(false);
}

/******************************************************************************/
/*!
\brief - Set background music Volume
\param volume - sound volume
*/
/******************************************************************************/
void Sound::SetBGMVolume(float volume)
{
	// Control the range of volume
	if (volume < 0) volume = 0;
	else if (volume > 1) volume = 1;
	m_BGMVolume = volume;

	// Set master volume 
	m_MasterVolume = m_SEVolume > m_BGMVolume ? m_SEVolume : m_BGMVolume;
	
	//Set channel
	m_channel[BGM]->setVolume(m_BGMToggle);
	m_channel[BGM]->setPaused(false);
}

/******************************************************************************/
/*!
\brief - Set Master Volume
\param volume - sound volume
*/
/******************************************************************************/
void Sound::SetMasterVolume(float volume)
{
	// Control the range of volume
	if (volume < 0) volume = 0;
	else if (volume > 1) volume = 1;
	m_SEVolume = m_BGMVolume = m_MasterVolume = volume;

	//Set channels
	m_channel[SE]->setVolume(m_SEVolume);
	m_channel[SE]->setPaused(false);

	m_channel[BGM]->setVolume(m_BGMToggle);
	m_channel[BGM]->setPaused(false);
}