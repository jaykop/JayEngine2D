#ifndef _MAINMENUSTAGE_H_
#define _MAINMENUSTAGE_H_

#include "../../Engine/StateManager/BaseStage.h"

class MenuStage : public Stage
{
public:

	MenuStage(GameStateManager* gsm = 0);

	virtual ~MenuStage();
	virtual void Load(GameData& gd);
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown(GameData& gd);
	virtual void Unload(GameData& gd);

	void PhysicsTest(void);
	void BasicControl(void);
	void SetWallSprites(void);
	void SetSamllSprites(void);

private:

	//Obj Manager
	ObjectManager m_OBM;

	// num of sprites
	int offset;
};

#endif // _MAINMENUSTAGE_H_