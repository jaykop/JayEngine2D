/******************************************************************************/
/*!
\file   SoundManager.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/26(yy/mm/dd)

\description
Contains SoundManager class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _SOUND_H_
#define _SOUND_H_

#pragma once
#include "FMOD/fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")

//using namespace FMOD;

enum SoundData{BG, END, SE_1, SE_2, SOUND_END};

class SoundManager
{

public:

	SoundManager(void);
	~SoundManager(void);

	void Init(void/*const int numOfchannel*/);
	void Load(const char* SoundDir, SoundData sound);

	void ErrorCheck(FMOD_RESULT result);

	FMOD::System*	GetSystem(void);
	FMOD::Channel*	GetChannel(const SoundData soundData);
	FMOD::Sound*	GetSound(const SoundData soundData);

private:

	FMOD::System*	m_system;				// pointer to system
	FMOD::Channel*	m_channel[SOUND_END];	// pointer to channel
	FMOD::Sound*	m_sound[SOUND_END];		// pointer to sound file
};

#endif // _SOUND_H_