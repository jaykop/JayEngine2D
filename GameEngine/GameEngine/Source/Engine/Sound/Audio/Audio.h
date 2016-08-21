/******************************************************************************/
/*!
\file   Audio.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/03(yy/mm/dd)

\description
Contains Audio class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "../SoundManager/SoundManager.h"

//! Audio class
class Audio
{
public:

	//! Constructor and destructor
	Audio(FMOD::System* system = 0);
	~Audio();

	void Play(void);
	void Stop(void);
	void Pause(bool boolean);

	//! Manage mute toggle
	bool GetMuteToggle(void) const;
	void SetMuteToggle(bool toggle);

	//! Manage volume
	float GetVolume(void) const;
	void SetVolume(float volume);

	FMOD::Channel* m_channel;	// Maybe not in need..
	FMOD::Sound* m_sound;		// Fmod sound

private:

	float m_volume;
	bool  m_pause;
	bool  m_play;
	FMOD::System*	m_system;

};

#endif // _AUDIO_H_