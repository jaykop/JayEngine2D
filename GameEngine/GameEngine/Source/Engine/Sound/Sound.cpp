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
m_system(gsm->GetSoundManager()->GetSystem())
{
	// Init all sound pointers
	for (int i = 0; i < SOUND_END; ++i) {
		m_sound[i] = m_SM->GetSound(static_cast<SoundData>(i));
		m_channel[i] = m_SM->GetChannel(static_cast<SoundData>(i));
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

void Sound::Play(SoundData sound)
{
	m_system->playSound(FMOD_CHANNEL_FREE, m_sound[sound], false, &m_channel[sound]);
}

void Sound::Stop(SoundData sound)
{
	m_channel[sound]->stop();
}

void Sound::SetSoundToggle(SoundData sound, bool toggle)
{
	
}

void Sound::SetMasterSoundToggle(bool toggle)
{

}

void Sound::SetVolume(SoundData sound, float volume)
{
	m_channel[sound]->setVolume(volume);
}

void Sound::SetMasterVolume(float volume)
{
	for (int i = 0; i < SOUND_END; ++i)
		m_channel[i]->setVolume(volume);
}