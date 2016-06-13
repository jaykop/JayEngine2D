#ifndef _BUILDER_H_
#define _BUILDER_H_

#include "../StateManager/GameStateManager/GameStateManager.h"

class Builder
{
public:
	virtual ~Builder(void) {};
	virtual Stage* BuildeStage(GameStateManager* m_GSM) = 0;

private:

};

#endif //_BUILDER_H_