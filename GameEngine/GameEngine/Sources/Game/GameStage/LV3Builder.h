#ifndef _LV3BUILDER_H_
#define _LV3BUILDER_H_

#include "LV3.h"
#include "../../Engine/StateManager/Builder.h"

class LV3Builder : public Builder
{

public:
	virtual ~LV3Builder(){};

	Stage* BuildeStage(GameStateManager* GSM)
	{
		return new LV3Stage(GSM);
	}

private:

};

#endif // _LV3BUILDER_H_