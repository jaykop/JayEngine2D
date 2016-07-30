#ifndef _LV2STAGE_H_
#define _LV2STAGE_H_

#include "../../Engine/StateManager/BaseStage.h"

//Todo: remove later
#include "../../Engine/Utilities/Json/JsonParser.h"
//
//class iniReader;
//class iniWritter;

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

	virtual void LoadObjects(const wchar_t* fileName);

private:

	//Obj Manager
	ObjectManager m_OBM;
	//iniReader* m_Loader;
	JsonParser m_testParser;
};

#endif // _LV2STAGE_H_