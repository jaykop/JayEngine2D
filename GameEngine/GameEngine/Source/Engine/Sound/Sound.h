/******************************************************************************/
/*!
\file   Sound.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/26(yy/mm/dd)

\description
Contains Sound class

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

#include <map>
#include "SoundManager/SoundManager.h"

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

	Audio* GetAudio(int key);
	void SetMasterMuteToggle(bool toggle);
	bool  GetMasterMuteToggle(void) const;
	
	void SetMasterVolume(float volume);
	float GetMasterVolume(void) const;
	
private:

	GameStateManager* m_GSM;
	SoundManager* m_SM;

	// Range of vulume is 0.f < v < 1.f
	float m_MasterVolume;
	bool m_MasterToggle;

	FMOD::System*	m_system;
	AudioMap*		m_audioMap;
};