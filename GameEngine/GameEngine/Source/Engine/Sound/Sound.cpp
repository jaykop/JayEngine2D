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

Sound::Sound(GameStateManager* gsm)
: m_GSM(gsm), m_SM(gsm->GetSoundManager()),
m_system(gsm->GetSoundManager()->GetSystem()),
m_BGMToggle(true), m_SEToggle(true), m_MasterToggle(true),
m_BGMVolume(.5f), m_SEVolume(.5f), m_MasterVolume(.5f)
{
	// Init all sound pointers
	for (int i = 0; i < SOUND_END; ++i) {
		m_sound[i] = m_SM->GetSound(static_cast<SoundData>(i));
	}

	// Init all channels
	for (int i = 0; i < TYPE_END; ++i) {
		m_channel[i] = 0;
	}
}

Sound::~Sound(void)
{}

void Sound::Init(void)
{

}

void Sound::Update(void)
{
	m_GSM->GetSoundManager()->GetSystem()->update();
}

void Sound::Shutdown(void)
{

}

void Sound::PlayBGM(SoundData sound)
{
	if (m_BGMToggle)
		m_system->playSound(FMOD_CHANNEL_FREE, m_sound[sound], false, &m_channel[BGM]);
}

void Sound::StopBGM(void)
{
	m_channel[BGM]->stop();
}

void Sound::PauseBGM(bool boolean)
{
	m_channel[BGM]->setPaused(boolean);
}

void Sound::PlaySE(SoundData sound)
{
	if (m_SEToggle)
		m_system->playSound(FMOD_CHANNEL_FREE, m_sound[sound], false, &m_channel[SE]);
}

void Sound::StopSE(void)
{
	m_channel[SE]->stop();
}

void Sound::PauseSE(bool boolean)
{
	m_channel[SE]->setPaused(boolean);
}

bool Sound::GSetSEMuteToggle(void) const
{
	return m_SEToggle;
}

bool Sound::GetBGMMuteToggle(void) const
{
	return m_BGMToggle;
}

bool Sound::GetMasterMuteToggle(void) const
{
	return m_MasterToggle;
}

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

float Sound::GetSEVolume(void) const
{
	return m_SEVolume;
}

float Sound::GetBGMVolume(void) const
{
	return m_BGMVolume;
}

float Sound::GetMasterVolume(void) const
{
	return m_MasterVolume;
}

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