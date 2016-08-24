/******************************************************************************/
/*!
\file   Logic.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/25(yy/mm/dd)

\description
Contains Logic builder's class

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

#ifndef _LOGICBUILDER_H_
#define _LOGICBUILDER_H_

#include "GameLogic/GameLogic.h"

class Object;

//! Virtual logic builder class
class LogicBuilder{

public:

	//! Basic constructor and destructor,
	//! build function
	LogicBuilder() {};
	virtual ~LogicBuilder(void) {};
	virtual GameLogic* BuildLogic(Object* Owner) const = 0;

private:

};

#endif //_LOGICBUILDER_H_