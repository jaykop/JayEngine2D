#ifndef _LV3STAGE_H_
#define _LV3STAGE_H_

#include "../../Engine/StateManager/BaseStage.h"
#include "../../Engine/StateManager/StageBuilder.h"

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

	void SampleRender(void);

private:

	ObjectManager m_OBM;
	GLuint depthMapFBO;
	GLuint depthMap;

};

class LV3Builder : public StageBuilder
{

public:
	virtual ~LV3Builder(){};

	Stage* BuildStage(GameStateManager* GSM)
	{
		return new LV3Stage(GSM);
	}

private:

};

#endif // _LV3STAGE_H_