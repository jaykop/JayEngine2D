#ifndef _MAINMENUBUILDER_H_
#define _MAINMENUBUILDER_H_

#include "MainMenu.h"
#include "../../Engine/StateManager/StageBuilder.h"

class MainMenuBuilder : public StageBuilder
{

public:

	virtual ~MainMenuBuilder(){};

	Stage* BuildStage(GameStateManager* GSM)
	{
		return new MenuStage(GSM);
	}

private:

};

#endif // _MAINMENUBUILDER_H_