/******************************************************************************/
/*!
\file   Darkness.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/22(yy/mm/dd)

\description
Contains Darkness's class and member

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/
#ifndef _DARKNESS_H_
#define _DARKNESS_H_

#include "../Sprite/Sprite.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../StateManager/GameStateManager/GameStateManager.h"

//! Darkness class
class Darkness : public Sprite
{

public:

	//! Constructor and destructor
	Darkness(const int id = 0, ObjectManager* obm = 0)
		:Sprite(id, obm) {
		// Cover the whole screen
		SetType(DARKNESS);
		SetProjectionType(PERSPECTIVE);
		SetScale(vec3(
			static_cast<float>(obm->GetGSM()->GetResolution().width), 
			static_cast<float>(obm->GetGSM()->GetResolution().height),
			0.f));
		SetColor(vec4(0.f, 0.f, 0.f, 1.f));
	};
	virtual ~Darkness() {};

private:

};

#endif // _DARKNESS_H_