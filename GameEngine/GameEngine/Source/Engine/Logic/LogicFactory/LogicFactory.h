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

class Object;
class GameLogic;
class LogicBuilder;

//! Logic Factoty class
class LogicFactory
{

public:

	~LogicFactory(void);
	static void AddBuilder(int key, LogicBuilder* pBuilder);
	static void ClearBuilderMap(void);

	static GameLogic* CreateLogic(int key, Object *owner);

private:

	static std::map <int, LogicBuilder*> m_builderMap;

};

#endif // _LOGICFACTORY_H_