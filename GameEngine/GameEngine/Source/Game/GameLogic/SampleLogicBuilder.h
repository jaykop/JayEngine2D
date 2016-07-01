#ifndef _SAMPLELOGICBUILDER_H_
#define _SAMPLELOGICBUILDER_H_

#include "SampleLogic.h"
#include "../../Engine/Logic/LogicBuilder.h"

class Object;
class SampleLogicBuilder : public LogicBuilder
{

public:
	virtual ~SampleLogicBuilder(){};

	GameLogic* BuildLogic(Object* owner)
	{
		return new SampleLogic(owner);
	}

private:

};

#endif // _SAMPLELOGICBUILDER_H_