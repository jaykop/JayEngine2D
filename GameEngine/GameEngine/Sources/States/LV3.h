class Stage;
class GameStateManager;
class InputManager;
class LV3Stage : public Stage
{
public:

	LV3Stage(GameStateManager* gsm = 0, InputManager* im = 0);

	virtual ~LV3Stage();
	virtual void Init();
	virtual void Update();
	virtual void Shutdown();

private:

};