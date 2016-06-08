#include "BaseStage/BaseStage.h"

class LV1Stage : public Stage
{
public:

	LV1Stage(GameStateManager* gsm = 0, InputManager* im = 0);

	virtual ~LV1Stage();
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown();

private:

};