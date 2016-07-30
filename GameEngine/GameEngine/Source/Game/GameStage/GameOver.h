#ifndef _GAMEOVERSTAGE_H_
#define _GAMEOVERSTAGE_H_

#include "../../Engine/StateManager/BaseStage.h"

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

	virtual void LoadObjects(const wchar_t* fileName);

private:

};

#endif // _GAMEOVERSTAGE_H_