#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_

#include "../ObjectManager/Object/Object.h"
#include "../ObjectManager/ObjectManager.h"

class GameStateManager;
class GameLogic
{
public:

	GameLogic(Object* owner = 0)
		:m_pOwner(owner), m_OBM(0), 
		m_GSM(0) {};

	virtual ~GameLogic(void) {};

	virtual void Init(void) = 0;
	virtual void Update(void) = 0;
	virtual void Shutdown(void) = 0;

private:

	Object* m_pOwner;
	ObjectManager* m_OBM;
	GameStateManager* m_GSM;
};

#endif // _GAMELOGIC_H_