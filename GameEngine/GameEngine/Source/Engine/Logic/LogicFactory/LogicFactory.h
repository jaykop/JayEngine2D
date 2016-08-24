/******************************************************************************/
/*!
\file   LogicFactory.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/25(yy/mm/dd)

\description
Contains LogicFactory class

All codes are written by Jaykop Jeong...
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