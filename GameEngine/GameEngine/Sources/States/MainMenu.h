#include "../Base/Math/MathUtils.h"
#include "../Base/ObjectManager/ObjectManager.h"

class Scene;
class Sprite;
class Stage;
class GameStateManager;
class InputManager;
class MenuStage : public Stage
{
public:

	MenuStage(GameStateManager* gsm = 0, InputManager* im = 0);

	virtual ~MenuStage();
	virtual void Init();
	virtual void Update();
	virtual void Shutdown();

	void SampleAnimation(void);
	void BasicControl(void);

private:

	//Obj Manager
	ObjectManager m_ObjM;
	Scene* m_scene;
	//Variable for animation
	bool  scale;
	float offset;
	float m_posx, m_posy, m_scl, degree, speed;
	
};