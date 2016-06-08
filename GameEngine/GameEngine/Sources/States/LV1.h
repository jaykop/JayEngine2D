#include "../Base/ObserverSample/Observer.h"

class InputList;
class InputManager;
class Stage;
class GameStateManager;
class LV1Stage : public Stage
{
public:

	LV1Stage(GameStateManager* gsm = 0, InputManager* im = 0);
	virtual ~LV1Stage();
	virtual void Init();
	virtual void Update();
	virtual void Shutdown();

private:
	InputList* a;
	InputManager* m_InputM;
	ConcreteSubject *CS;
	Observer *o1;
	Observer *o2;

};