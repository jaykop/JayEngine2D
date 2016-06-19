/******************************************************************************/
/*!
\file   Factory.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Factory's class and members
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <map>
#include "../../../Game/BaseData/GameData.h"

class Stage;
class Builder;
class GameStateManager;

//! class Factory
class Factory
{

public:

	~Factory(void);

	//! Function manages factory
	void AddBuilder(StageType stage, Builder* pBuilder);
	void DeleteBuilder(StageType stage);
	void Clear();

	//! Create stage
	Stage* CreateStage(StageType stage, GameStateManager* GSM);

private:

	//! Builder list
	std::map<StageType, Builder*> m_builderMap;

};

#endif // FACTORY_H_