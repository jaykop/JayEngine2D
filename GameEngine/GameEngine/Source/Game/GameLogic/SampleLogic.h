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

	virtual void Init(void);
	virtual void Update(void);
	virtual void Shutdown(void);

private:

	Object* m_pOwner;
	ObjectManager* m_OBM;
	GameStateManager* m_GSM;

};

#endif // _SAMPLELOGIC_H_