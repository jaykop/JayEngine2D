#include "BaseStage/BaseStage.h"

class LV3Stage : public Stage
{
public:

	LV3Stage(GameStateManager* gsm = 0);

	virtual ~LV3Stage();
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown();

private:

};