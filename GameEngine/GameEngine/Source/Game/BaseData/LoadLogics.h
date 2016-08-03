/******************************************************************************/
/*!
\file   LoadLogics.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/01(yy/mm/dd)

\description
Contains logic builder function.

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#pragma once

#ifndef _LOGICBUILDERLIST_H_
#define _LOGICBUILDERLIST_H_

#include "../../Engine/Logic/LogicFactory.h"
#include "../../Game/GameLogic/SampleLogic.h"

/******************************************************************************/
/*!
\brief - Build logics.
		 User should customize this part manually!
*/
/******************************************************************************/
void BuildLogics(void)
{
	// name: SampleLogic -> key: 0
	LogicFactory::AddBuilder(1, new SampleLogicBuilder);
}

#endif // _LOGICBUILDERLIST_H_