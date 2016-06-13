#ifndef _LV1BUILDER_H_
#define _LV1BUILDER_H_

#include "LV1.h"
#include "../../Engine/StateManager/Builder.h"

class LV1Builder : public Builder
{

public:
	virtual ~LV1Builder(){};

	Stage* BuildeStage(GameStateManager* GSM)
	{
		return new LV1Stage(GSM);
	}

private:

};

#endif // _LV1BUILDER_H_