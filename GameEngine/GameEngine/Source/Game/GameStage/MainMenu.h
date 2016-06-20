#ifndef _MAINMENUSTAGE_H_
#define _MAINMENUSTAGE_H_

#include "../BaseData/BaseStage.h"

class MenuStage : public Stage
{
public:

	MenuStage(GameStateManager* gsm = 0);

	virtual ~MenuStage();
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown();

	void SampleAnimation(void);
	void BasicControl(void);

private:

	//Obj Manager
	ObjectManager m_ObjM;
};

#endif // _MAINMENUSTAGE_H_