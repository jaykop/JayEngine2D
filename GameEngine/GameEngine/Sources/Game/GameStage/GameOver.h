#ifndef _GAMEOVERSTAGE_H_
#define _GAMEOVERSTAGE_H_

#include "../BaseData/BaseStage.h"

class GameOverStage : public Stage
{
public:

	GameOverStage(GameStateManager* gsm = 0);

	virtual ~GameOverStage();
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown();

private:

};

#endif // _GAMEOVERSTAGE_H_