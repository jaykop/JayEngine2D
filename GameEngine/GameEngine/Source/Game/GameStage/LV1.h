#ifndef _LV1STAGE_H_
#define _LV1STAGE_H_

#include "../../Engine/StateManager/BaseStage.h"

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

	virtual void LoadObjects(const wchar_t* fileName);

private:

	ObjectManager m_OBM;

};

#endif // _LV1STAGE_H_