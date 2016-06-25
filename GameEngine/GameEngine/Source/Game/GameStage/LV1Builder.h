#ifndef _LV1BUILDER_H_
#define _LV1BUILDER_H_

#include "LV1.h"
#include "../../Engine/StateManager/StageBuilder.h"

class LV1Builder : public StageBuilder
{

public:
	virtual ~LV1Builder(){};

	Stage* BuildStage(GameStateManager* GSM)
	{
		return new LV1Stage(GSM);
	}

private:

};

#endif // _LV1BUILDER_H_