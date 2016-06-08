class Stage;
class GameStateManager;
class InputManager;
class LV2Stage : public Stage
{
public:

	LV2Stage(GameStateManager* gsm = 0, InputManager* im = 0);

	virtual ~LV2Stage();
	virtual void Init();
	virtual void Update();
	virtual void Shutdown();

private:

};