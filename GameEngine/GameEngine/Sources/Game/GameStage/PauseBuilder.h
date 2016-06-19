#ifndef _PUASEBUILDER_H_
#define _PUASEUBUILDER_H_

#include "Pause.h"
#include "../../Engine/StateManager/Builder.h"

class PauseBuilder : public Builder
{

public:

	virtual ~PauseBuilder(){};

	Stage* BuildeStage(GameStateManager* GSM)
	{
		return new PauseStage(GSM);
	}

private:

};

#endif // _MAINMENUBUILDER_H_