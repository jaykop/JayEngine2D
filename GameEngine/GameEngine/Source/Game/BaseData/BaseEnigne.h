/******************************************************************************/
/*!
\file   BaseEngine.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains header files(BaseEngine) to provide users base engine

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _STAGE_BASE_HEADER_
#define _STAGE_BASE_HEADER_

#include "../../Engine/App/Application.h"

// Graphic Header
#include "../../Engine/Graphic/Scene/Scene.h"
#include "../../Engine/Graphic/Light/Light.h"
#include "../../Engine/Graphic/Sprite/Sprite.h"
#include "../../Engine/Graphic/Particle/Particle.h"


// Physics Header
#include "../../Engine/Physics/World/World.h"
#include "../../Engine/Physics/RigidBody/RigidBody.h"

// Sound Header
#include "../../Engine/Sound/Sound.h"
#include "../../Engine/Sound/Audio/Audio.h"

// Logic Header
#include "../../Engine/Logic/Logic.h"
#include "../../Engine/InputManager/InputManager.h"

// Until Header
#include "../../Engine/Utilities/Time.h"
#include "../../Engine/Utilities/Random.h"
#include "../../Engine/Utilities/Debug/Debug.h"
#include "../../Engine/Utilities/INI/iniReader.h"
#include "../../Engine/Utilities/INI/iniWritter.h"


#endif //_STAGE_BASE_HEADER_