#ifndef _DemoLogic_Pause_H_
#define _DemoLogic_Pause_H_

#include "../../Engine/Logic/GameLogic/GameLogic.h"
#include "../../Engine/Logic/LogicBuilder.h"

class DemoLogic_PauseBuilder : public LogicBuilder
{

public:
	DemoLogic_PauseBuilder() {};
	virtual ~DemoLogic_PauseBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner) const;

};

class DemoLogic_Pause : public GameLogic
{
public:

	DemoLogic_Pause(Object* owner);
	virtual ~DemoLogic_Pause(void) {};

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

#endif // _DemoLogic_Pause_H_