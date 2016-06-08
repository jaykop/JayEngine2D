class Stage;
class GameStateManager;
class InputManager;
class GameOverStage : public Stage
{
public:

	GameOverStage(GameStateManager* gsm = 0, InputManager* = 0);

	virtual ~GameOverStage();
	virtual void Init();
	virtual void Update();
	virtual void Shutdown();

private:

};