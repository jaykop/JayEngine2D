#ifndef _LV2STAGE_H_
#define _LV2STAGE_H_

#include "../BaseData/BaseStage.h"

class LV2Stage : public Stage
{
public:

	LV2Stage(GameStateManager* gsm = 0);

	virtual ~LV2Stage();
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown();

private:

};

#endif // _LV2STAGE_H_