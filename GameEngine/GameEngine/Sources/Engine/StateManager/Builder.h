/******************************************************************************/
/*!
\file   Builder.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Builder's class and members
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef _BUILDER_H_
#define _BUILDER_H_

#include "../StateManager/GameStateManager/GameStateManager.h"

//! class Builder
class Builder
{
public:
	virtual ~Builder(void) {};
	virtual Stage* BuildeStage(GameStateManager* m_GSM) = 0;

private:

};

#endif //_BUILDER_H_