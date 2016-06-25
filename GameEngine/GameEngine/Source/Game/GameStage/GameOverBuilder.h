#ifndef _GAMEOVERBUILDER_H_
#define _GAMEOVERBUILDER_H_

#include "GameOver.h"
#include "../../Engine/StateManager/StageBuilder.h"

class GameOverBuilder : public StageBuilder
{
	
public:
	virtual ~GameOverBuilder(){};

	Stage* BuildStage(GameStateManager* GSM)
	{
		return new GameOverStage(GSM);
	}

private:

};

#endif // _GAMEOVERBUILDER_H_