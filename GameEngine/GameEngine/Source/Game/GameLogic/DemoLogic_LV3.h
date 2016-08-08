#ifndef _DemoLogic_LV3_H_
#define _DemoLogic_LV3_H_

#include "../../Engine/Logic/GameLogic/GameLogic.h"
#include "../../Engine/Logic/LogicBuilder.h"

class DemoLogic_LV3Builder : public LogicBuilder
{

public:
	DemoLogic_LV3Builder() {};
	virtual ~DemoLogic_LV3Builder() {};
	virtual GameLogic* BuildLogic(Object* Owner) const;

};

class DemoLogic_LV3 : public GameLogic
{
public:

	DemoLogic_LV3(Object* owner);
	virtual ~DemoLogic_LV3(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown(GameData& gd);
	virtual void Unload(void);

private:

	Object* m_Owner;
	ObjectManager* m_OBM;
	GameStateManager* m_GSM;

	vec4 color;
	vec3 size;

};

#endif // _DemoLogic_LV3_H_