/******************************************************************************/
/*!
\file   Sound.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/26(yy/mm/dd)

\description
Contains Sound class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "SoundManager.h"

class GameStateManager;

class Sound{

public:

	Sound(GameStateManager* gsm);
	~Sound(void);

	void Init(void);
	void Update(void);
	void Shutdown(void);

	void Play(SoundData sound);
	void Stop(SoundData sound);

	void SetSoundToggle(SoundData sound, bool toggle);
	void SetMasterSoundToggle(bool toggle);
	void SetVolume(SoundData sound, float volume);
	void SetMasterVolume(float volume);

private:

	GameStateManager* m_GSM;
	SoundManager* m_SM;

	float			m_volume;
	bool			m_playToggle;

	FMOD::System*	m_system;				// pointer to system
	FMOD::Channel*	m_channel[SOUND_END];	// pointer to channel
	FMOD::Sound*	m_sound[SOUND_END];		// pointer to sound file
};