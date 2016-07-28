/******************************************************************************/
/*!
\file   BaseStage.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains base stage, base utils' header files consists of stage(state)

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _BASESTAGE_H_
#define _BASESTAGE_H_

#include "../Utilities/Time.h"
#include "../Utilities/Random.h"
#include "../ObjectManager/ObjectManager.h"

struct GameData;

class Scene;
class World;
class Sprite;
class InputManager;
class GameStateManager;

class Stage
{
public:

	Stage(GameStateManager* gsm = 0)
	{
		m_GSM = gsm;
	};

	virtual ~Stage() {};
	virtual void Init(GameData& gd) = 0;
	virtual void Update(GameData& gd) = 0;
	virtual void Shutdown() = 0;

	GameStateManager* m_GSM;
};

#endif //_BASESTAGE_H_