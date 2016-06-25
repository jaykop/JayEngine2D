#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_

class Object;
class GameLogic
{
public:

	GameLogic(Object* owner) {
		m_pOwner = owner;
	};
	virtual ~GameLogic(void) {};

	virtual void Init(void) = 0;
	virtual void Update(void) = 0;
	virtual void Shutdown(void) = 0;

private:

	Object* m_pOwner;

};

#endif // _GAMELOGIC_H_