#ifndef _GAMEOVERBUILDER_H_
#define _GAMEOVERBUILDER_H_

#include "GameOver.h"
#include "../../Engine/StateManager/Builder.h"

class GameOverBuilder : public Builder
{
	
public:
	virtual ~GameOverBuilder(){};

	Stage* BuildeStage(GameStateManager* GSM)
	{
		return new GameOverStage(GSM);
	}

private:

};

#endif // _GAMEOVERBUILDER_H_