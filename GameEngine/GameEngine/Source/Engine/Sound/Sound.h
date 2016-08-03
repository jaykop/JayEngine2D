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

#include <map>

#include "SoundManager.h"

enum ChannleType{BGM, SE, TYPE_END};

class Audio;
class GameStateManager;

//! Sound system class
class Sound{

public:

	//! Basic functions
	Sound(GameStateManager* gsm);
	~Sound(void);

	//! Loop functions
	void Init(void);
	void Update(void);
	void Shutdown(void);

	//! play, pause, stop functions
	void PlayBGM(int key);
	void StopBGM(void);
	void PauseBGM(bool boolean);

	void PlaySE(int key);
	void StopSE(void);
	void PauseSE(bool boolean);

	//! Manage mute toggle
	bool GetSEMuteToggle(void) const;
	bool GetBGMMuteToggle(void) const;
	bool GetMasterMuteToggle(void) const;

	void SetSEMuteToggle(bool toggle);
	void SetBGMMuteToggle(bool toggle);
	void SetMasterMuteToggle(bool toggle);
	
	//! Manager volume
	float GetSEVolume(void) const;
	float GetBGMVolume(void) const;
	float GetMasterVolume(void) const;
	
	void SetSEVolume(float volume);
	void SetBGMVolume(float volume);
	void SetMasterVolume(float volume);

private:

	GameStateManager* m_GSM;
	SoundManager* m_SM;

	// Range of vulume is 0.f < v < 1.f
	float m_SEVolume;
	float m_BGMVolume;
	float m_MasterVolume;

	bool m_SEToggle;
	bool m_BGMToggle;
	bool m_MasterToggle;

	FMOD::System*	m_system;			 // pointer to system
	FMOD::Channel*	m_channel[TYPE_END]; // pointer to channel
};