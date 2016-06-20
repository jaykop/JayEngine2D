#ifndef _MAINMENUBUILDER_H_
#define _MAINMENUBUILDER_H_

#include "MainMenu.h"
#include "../../Engine/StateManager/Builder.h"

class MainMenuBuilder : public Builder
{

public:

	virtual ~MainMenuBuilder(){};

	Stage* BuildeStage(GameStateManager* GSM)
	{
		return new MenuStage(GSM);
	}

private:

};

#endif // _MAINMENUBUILDER_H_