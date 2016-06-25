/******************************************************************************/
/*!
\file   LogicFactory.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/25(yy/mm/dd)

\description
Contains LogicFactory class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _LOGICFACTORY_H_
#define _LOGICFACTORY_H_

#include <map>

class GameLogic;
class LogicBuilder;
class GameStateManager;

class LogicFactory
{

public:

	~LogicFactory(void);
	void AddBuilder(GameLogic* logic, LogicBuilder* pBuilder);
	void DeleteBuilder(GameLogic* logic);
	void Clear(void);

	GameLogic* CreateLogic(GameLogic* logic, GameStateManager* GSM);

private:

	std::map <GameLogic*, LogicBuilder*> m_builderMap;

};

#endif // _LOGICFACTORY_H_