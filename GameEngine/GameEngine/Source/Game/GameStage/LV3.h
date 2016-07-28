#ifndef _LV3STAGE_H_
#define _LV3STAGE_H_

#include "../../Engine/StateManager/BaseStage.h"

class LV3Stage : public Stage
{
public:

	LV3Stage(GameStateManager* gsm = 0);

	virtual ~LV3Stage();
	virtual void Load(GameData& gd);
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown(GameData& gd);
	virtual void Unload(GameData& gd);

private:

};

#endif // _LV3STAGE_H_