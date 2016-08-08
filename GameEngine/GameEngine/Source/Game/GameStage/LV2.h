#ifndef _LV2STAGE_H_
#define _LV2STAGE_H_

#include "../../Engine/StateManager/BaseStage.h"
#include "../../Engine/StateManager/StageBuilder.h"

class LV2Stage : public Stage
{
public:

	LV2Stage(GameStateManager* gsm = 0);

	virtual ~LV2Stage();
	virtual void Load(GameData& gd);
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown(GameData& gd);
	virtual void Unload(GameData& gd);

private:

	//Obj Manager
	ObjectManager m_OBM;
};

class LV2Builder : public StageBuilder
{

public:
	virtual ~LV2Builder(){};

	Stage* BuildStage(GameStateManager* GSM)
	{
		return new LV2Stage(GSM);
	}

private:

};

#endif // _LV2STAGE_H_