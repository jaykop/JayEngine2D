#ifndef _LV3BUILDER_H_
#define _LV3BUILDER_H_

#include "LV3.h"
#include "../../Engine/StateManager/StageBuilder.h"

class LV3Builder : public StageBuilder
{

public:
	virtual ~LV3Builder(){};

	Stage* BuildStage(GameStateManager* GSM)
	{
		return new LV3Stage(GSM);
	}

private:

};

#endif // _LV3BUILDER_H_