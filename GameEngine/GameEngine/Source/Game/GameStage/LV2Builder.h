#ifndef _LV2BUILDER_H_
#define _LV2BUILDER_H_

#include "LV2.h"
#include "../../Engine/StateManager/StageBuilder.h"

class LV2Builder : public StageBuilder
{

public:
	virtual ~LV2Builder(){};

	Stage* BuildStage(GameStateManager* GSM)
	{
		return new LV2Stage(GSM);
	}

private:

};

#endif // _LV2BUILDER_H_