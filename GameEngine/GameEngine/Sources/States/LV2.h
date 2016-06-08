#include "BaseStage/BaseStage.h"

class LV2Stage : public Stage
{
public:

	LV2Stage(GameStateManager* gsm = 0, InputManager* im = 0);

	virtual ~LV2Stage();
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown();

private:

};