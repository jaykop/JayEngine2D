/******************************************************************************/
/*!
\file   LogicBuilderList.h.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/01(yy/mm/dd)

\description
Contains LogicBuilderList's function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#pragma once

#ifndef _LOGICBUILDERLIST_H_
#define _LOGICBUILDERLIST_H_

#include "../Logic/LogicFactory.h"
#include "../../Game/GameLogic/SampleLogic.h"

void BuildLogics(void)
{
	LogicFactory::AddBuilder("SampleLogic", new SampleLogicBuilder);
}

#endif // _LOGICBUILDERLIST_H_