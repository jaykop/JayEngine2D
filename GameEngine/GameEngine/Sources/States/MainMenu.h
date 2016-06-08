#include "BaseStage/BaseStage.h"

class MenuStage : public Stage
{
public:

	MenuStage(GameStateManager* gsm = 0, InputManager* im = 0);

	virtual ~MenuStage();
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown();

	void SampleAnimation(void);
	void BasicControl(void);

private:

	//Obj Manager
	ObjectManager m_ObjM;
	Scene* m_scene;
	World* m_world;

	float m_posx, m_posy, speed;
	
};