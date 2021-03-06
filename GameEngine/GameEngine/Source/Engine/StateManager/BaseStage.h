/******************************************************************************/
/*!
\file   BaseStage.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains base stage, base utils' header files consists of stage(state)

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

#ifndef _BASESTAGE_H_
#define _BASESTAGE_H_

#include "../ObjectManager/ObjectManager.h"

struct GameData;

class Scene;
class World;
class Sprite;
class InputManager;
class GameStateManager;

//! Virtual stage class
class Stage
{
public:

	Stage(GameStateManager* gsm = 0)
	{
		m_GSM = gsm;
	};

	virtual ~Stage() {};
	virtual void Load(GameData& gd) = 0;
	virtual void Init(GameData& gd) = 0;
	virtual void Update(GameData& gd) = 0;
	virtual void Shutdown(GameData& gd) = 0;
	virtual void Unload(GameData& gd) = 0;

	GameStateManager* m_GSM;
};

#endif //_BASESTAGE_H_