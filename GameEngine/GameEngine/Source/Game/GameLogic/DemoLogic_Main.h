#ifndef _DemoLogic_Main_H_
#define _DemoLogic_Main_H_

#include "../../Engine/Logic/GameLogic/GameLogic.h"
#include "../../Engine/Logic/LogicBuilder.h"

class DemoLogic_MainBuilder : public LogicBuilder
{

public:
	DemoLogic_MainBuilder() {};
	virtual ~DemoLogic_MainBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner) const;

};

class DemoLogic_Main : public GameLogic
{
public:

	DemoLogic_Main(Object* owner);
	virtual ~DemoLogic_Main(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown(GameData& gd);
	virtual void Unload(void);

	void BasicControl(void);
	void MovingSprite(void);
	void ColoredTexts(float dt);
	void MousePosition(void);

private:

	Object* m_Owner;
	ObjectManager* m_OBM;
	GameStateManager* m_GSM;

	vec4  color;
	int   color_offset;
	float rotation, m_dt;
	vec3  position, scale;
	bool  pos_toggle, scale_toggle;
};

#endif // _DemoLogic_Main_H_