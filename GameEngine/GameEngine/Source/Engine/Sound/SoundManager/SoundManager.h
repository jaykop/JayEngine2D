/******************************************************************************/
/*!
\file   SoundManager.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/26(yy/mm/dd)

\description
Contains SoundManager class

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

#ifndef _SOUND_H_
#define _SOUND_H_

#pragma once
#include "FMOD/fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")
#include <map>

class Audio;
class Application;

//! type definition audio map
typedef std::map<int, Audio*> AudioMap;

//! Sound manager class
class SoundManager
{

public:

	//! Basic functions
	SoundManager(void);
	~SoundManager(void);

	//! Manage fmod system and loaded sounds
	void InitFMOD(Application* pApp, int size);
	void AddSound(int key, const char* SoundDir);
	void ClearSoundMap(void);
	void ErrorCheck(Application* pApp, FMOD_RESULT result);
	AudioMap& GetAudioMap(void);

	FMOD::System*	GetSystem(void);
	FMOD::Sound*	GetSound(int key);
	FMOD::Channel*  GetChannel(int key);

private:

	FMOD::System*	m_system;	// pointer to system
	AudioMap		m_audioMap;
};

#endif // _SOUND_H_