#include "../../Engine/StateManager/BaseStage.h"

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

	virtual void LoadObjects(const wchar_t* fileName);

private:

	//Obj Manager
	ObjectManager m_OBM;

};