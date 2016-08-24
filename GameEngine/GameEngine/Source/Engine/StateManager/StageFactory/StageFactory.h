/******************************************************************************/
/*!
\file   Factory.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Factory's class and members

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <map>
#include "../../../Game/BaseData/GameData.h"

class Stage;
class StageBuilder;
class GameStateManager;

//! class Factory
class StageFactory
{

public:

	~StageFactory(void);

	//! Function manages factory
	void AddBuilder(StageType stage, StageBuilder* pBuilder);
	void DeleteBuilder(StageType stage);
	void Clear(void);

	//! Create stage
	Stage* CreateStage(StageType stage, GameStateManager* GSM);

private:

	//! Builder list
	std::map<StageType, StageBuilder*> m_builderMap;

};

#endif // FACTORY_H_