/******************************************************************************/
/*!
\file   Darkness.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/22(yy/mm/dd)

\description
Contains Darkness's class and member

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

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