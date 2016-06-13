#ifndef _LV2BUILDER_H_
#define _LV2BUILDER_H_

#include "LV2.h"
#include "../../Engine/StateManager/Builder.h"

class LV2Builder : public Builder
{

public:
	virtual ~LV2Builder(){};

	Stage* BuildeStage(GameStateManager* GSM)
	{
		return new LV2Stage(GSM);
	}

private:

};

#endif // _LV2BUILDER_H_