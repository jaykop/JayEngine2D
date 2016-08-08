#ifndef _LV1STAGE_H_
#define _LV1STAGE_H_

#include "../../Engine/StateManager/BaseStage.h"
#include "../../Engine/StateManager/StageBuilder.h"

class LV1Stage : public Stage
{
public:

	LV1Stage(GameStateManager* gsm = 0);

	virtual ~LV1Stage();
	virtual void Load(GameData& gd);
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown(GameData& gd);
	virtual void Unload(GameData& gd);

private:

	ObjectManager m_OBM;

};

class LV1Builder : public StageBuilder
{

public:
	virtual ~LV1Builder(){};

	Stage* BuildStage(GameStateManager* GSM)
	{
		return new LV1Stage(GSM);
	}

private:

};

#endif // _LV1STAGE_H_