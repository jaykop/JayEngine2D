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

#include "SoundManager.h"

//! Audio class
class Audio
{
public:

	//! Constructor and destructor
	Audio() :m_channel(0), m_sound(0) {};
	~Audio() {};

	FMOD::Channel* m_channel;	// Maybe not in need..
	FMOD::Sound* m_sound;		// Fmod sound

private:

};

#endif // _AUDIO_H_