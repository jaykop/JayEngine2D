#ifndef _DemoLogic_LV1_H_
#define _DemoLogic_LV1_H_

#include "../../Engine/Logic/GameLogic/GameLogic.h"
#include "../../Engine/Logic/LogicBuilder.h"

class DemoLogic_LV1Builder : public LogicBuilder
{

public:
	DemoLogic_LV1Builder() {};
	virtual ~DemoLogic_LV1Builder() {};
	virtual GameLogic* BuildLogic(Object* Owner) const;

};

class DemoLogic_LV1 : public GameLogic
{
public:

	DemoLogic_LV1(Object* owner);
	virtual ~DemoLogic_LV1(void) {};

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

#endif // _DemoLogic_LV1_H_