#ifndef _LV1STAGE_H_
#define _LV1STAGE_H_

#include "../BaseData/BaseStage.h"

class LV1Stage : public Stage
{
public:

	LV1Stage(GameStateManager* gsm = 0);

	virtual ~LV1Stage();
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown();

private:

	ObjectManager m_OBM;

};

#endif // _LV1STAGE_H_