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
	void AddBuilder(const char* logic, LogicBuilder* pBuilder);
	void DeleteAllBuilders(void);

	GameLogic* CreateLogic(const char* logic, Object *owner);

private:

	std::map <const char*, LogicBuilder*> m_builderMap;

};

#endif // _LOGICFACTORY_H_