#ifndef _PUASEBUILDER_H_
#define _PUASEUBUILDER_H_

#include "Pause.h"
#include "../../Engine/StateManager/StageBuilder.h"

class PauseBuilder : public StageBuilder
{

public:

	virtual ~PauseBuilder(){};

	Stage* BuildStage(GameStateManager* GSM)
	{
		return new PauseStage(GSM);
	}

private:

};

#endif // _MAINMENUBUILDER_H_