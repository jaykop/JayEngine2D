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

#ifndef _SOUND_H_
#define _SOUND_H_

#pragma once
#include <fmod.hpp>
#pragma comment(lib, "fmodex_vc.lib")

using namespace FMOD;
typedef FMOD::System SoundManager;

class Sound
{

public:

	Sound(const SoundManager* sm = 0);
	~Sound(void);

	void Init();
	void Load();
	void Play();
	void Stop();
	void ErrorCheck();
	void SetVolume();

private:

	SoundManager* m_SM;		// pointer to sound manager
	Channel m_channel;		// channel
	FMOD::Sound* m_sound;	// pointer to sound file
};

#endif // _SOUND_H_