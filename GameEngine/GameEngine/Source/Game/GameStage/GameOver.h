#ifndef _GAMEOVERSTAGE_H_
#define _GAMEOVERSTAGE_H_

#include "../../Engine/StateManager/BaseStage.h"
#include "../../Engine/StateManager/StageBuilder.h"

class GameOverStage : public Stage
{
public:

	GameOverStage(GameStateManager* gsm = 0);

	virtual ~GameOverStage();
	virtual void Load(GameData& gd);
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown(GameData& gd);
	virtual void Unload(GameData& gd);

private:

	ObjectManager m_OBM;

};

class GameOverBuilder : public StageBuilder
{

public:
	virtual ~GameOverBuilder(){};

	Stage* BuildStage(GameStateManager* GSM)
	{
		return new GameOverStage(GSM);
	}

private:

};

#endif // _GAMEOVERSTAGE_H_