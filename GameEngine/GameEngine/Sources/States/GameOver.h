#include "BaseStage/BaseStage.h"

class GameOverStage : public Stage
{
public:

	GameOverStage(GameStateManager* gsm = 0, InputManager* im = 0);

	virtual ~GameOverStage();
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown();

private:

};