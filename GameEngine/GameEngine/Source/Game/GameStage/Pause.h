#include "../../Engine/StateManager/BaseStage.h"
#include "../../Engine/StateManager/StageBuilder.h"

class PauseStage : public Stage
{
public:

	PauseStage(GameStateManager* gsm = 0);

	virtual ~PauseStage();
	virtual void Load(GameData& gd);
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown(GameData& gd);
	virtual void Unload(GameData& gd);

private:

	//Obj Manager
	ObjectManager m_OBM;

};

class PauseBuilder : public StageBuilder
{

public:

	virtual ~PauseBuilder(){};

	Stage* BuildStage(GameStateManager* GSM)
	{
		return new PauseStage(GSM);
	}

private:

};
