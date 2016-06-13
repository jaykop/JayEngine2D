#ifndef _BASESTAGE_H_
#define _BASESTAGE_H_

#include "../../Engine/Utilities/Time.h"
#include "../../Engine/Utilities/Random.h"
#include "../../Engine/Utilities/Math/MathUtils.h"
#include "../../Engine/ObjectManager/ObjectManager.h"

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