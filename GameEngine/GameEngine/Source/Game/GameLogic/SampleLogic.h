#ifndef _SAMPLELOGIC_H_
#define _SAMPLELOGIC_H_

#include "../../Engine/Logic/GameLogic.h"
#include "../../Engine/Logic/LogicBuilder.h"

class SampleLogicBuilder : public LogicBuilder
{

public:
	SampleLogicBuilder() {};
	virtual ~SampleLogicBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner) const;

};

class SampleLogic : public GameLogic
{
public:

	SampleLogic(Object* owner);
	virtual ~SampleLogic(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown(GameData& gd);
	virtual void Unload(void);

private:

	Object* m_Owner;
	ObjectManager* m_OBM;
	GameStateManager* m_GSM;

	int* test;

	vec4 color;
	vec3 size;

};

#endif // _SAMPLELOGIC_H_