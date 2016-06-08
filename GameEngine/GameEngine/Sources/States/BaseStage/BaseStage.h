#ifndef _BASESTAGE_H_
#define _BASESTAGE_H_

#include "../../Base/Math/MathUtils.h"
#include "../../Base/ObjectManager/ObjectManager.h"

struct GameData;

class Scene;
class World;
class Sprite;
class InputManager;
class GameStateManager;

class Stage
{
public:

	Stage(GameStateManager* gsm = 0,
		InputManager* im = 0)
	{
		m_GSM = gsm;
		m_IM = im;
	};

	virtual ~Stage() {};
	virtual void Init(GameData& gd) = 0;
	virtual void Update(GameData& gd) = 0;
	virtual void Shutdown() = 0;

	GameStateManager* m_GSM;
	InputManager* m_IM;
};

#endif //_BASESTAGE_H_