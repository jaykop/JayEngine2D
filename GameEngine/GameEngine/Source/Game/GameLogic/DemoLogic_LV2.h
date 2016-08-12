#ifndef _DemoLogic_LV2_H_
#define _DemoLogic_LV2_H_

#include "../../Engine/Logic/GameLogic/GameLogic.h"
#include "../../Engine/Logic/LogicBuilder.h"

class DemoLogic_LV2Builder : public LogicBuilder
{

public:
	DemoLogic_LV2Builder() {};
	virtual ~DemoLogic_LV2Builder() {};
	virtual GameLogic* BuildLogic(Object* Owner) const;

};

class DemoLogic_LV2 : public GameLogic
{
public:

	DemoLogic_LV2(Object* owner);
	virtual ~DemoLogic_LV2(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown(GameData& gd);
	virtual void Unload(void);

	void BasicControl(void);
	void SountTest(void);
	void ToggleAnimation(void);
	void UnprojectSample(void);

private:

	Object* m_Owner;
	ObjectManager* m_OBM;
	GameStateManager* m_GSM;

	bool bgm_toggle, se_toggle;
	float volume;
};

#endif // _DemoLogic_LV2_H_