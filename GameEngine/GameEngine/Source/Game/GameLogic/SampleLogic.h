#ifndef _SAMPLELOGIC_H_
#define _SAMPLELOGIC_H_

#include "../../Engine/Logic/GameLogic.h"

class SampleLogic : public GameLogic
{
public:

	SampleLogic(Object* owner) 
		:m_pOwner(owner), m_OBM(owner->GetOBM()),
		m_GSM(owner->GetOBM()->GetGSM()) {};

	virtual ~SampleLogic(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(void);
	virtual void Update(void);
	virtual void Shutdown(void);
	virtual void Unload(void);

private:

	Object* m_pOwner;
	ObjectManager* m_OBM;
	GameStateManager* m_GSM;

	int* test;

	vec4 color;
	vec3 size;

};

#endif // _SAMPLELOGIC_H_