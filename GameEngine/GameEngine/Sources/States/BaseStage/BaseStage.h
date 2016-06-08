#ifndef _BASESTAGE_H_
#define _BASESTAGE_H_

class GameStateManager;
class InputManager;
//Stage class definition
class Stage
{
public:

	Stage(GameStateManager* gsm = 0,
		InputManager* im = 0)
	{
		m_GSM = gsm;
		m_IM = im;
	};

	virtual ~Stage() {};
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;

	GameStateManager* m_GSM;
	InputManager* m_IM;
};

#endif //_BASESTAGE_H_