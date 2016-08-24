/******************************************************************************/
/*!
\file   Builder.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Builder's class and members
All codes are written by Jaykop Jeong...
*/
/******************************************************************************/
#ifndef _BUILDER_H_
#define _BUILDER_H_

#include "../StateManager/GameStateManager/GameStateManager.h"

//! class Builder
class StageBuilder
{
public:
	virtual ~StageBuilder(void) {};
	virtual Stage* BuildStage(GameStateManager* m_GSM) = 0;

private:

};

#endif //_BUILDER_H_