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

class LogicFactory
{

public:

	~LogicFactory(void);
	static void AddBuilder(const std::string& name, LogicBuilder* pBuilder);
	static void DeleteAllBuilders(void);

	static GameLogic* CreateLogic(const std::string& name, Object *owner);

private:

	static std::map <std::string, LogicBuilder*> m_builderMap;

};

#endif // _LOGICFACTORY_H_