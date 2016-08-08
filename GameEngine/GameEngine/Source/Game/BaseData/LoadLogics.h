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

#include "../../Engine/Logic/LogicFactory/LogicFactory.h"

#include "../../Game/GameLogic/DemoLogic_Main.h"
#include "../../Game/GameLogic/DemoLogic_LV1.h"
#include "../../Game/GameLogic/DemoLogic_LV2.h"
#include "../../Game/GameLogic/DemoLogic_LV3.h"
#include "../../Game/GameLogic/DemoLogic_Pause.h"
#include "../../Game/GameLogic/DemoLogic_GameOver.h"

/******************************************************************************/
/*!
\brief - Build logics.
		 User should customize this part manually!
*/
/******************************************************************************/
void BuildLogics(void)
{
	// name: SampleLogic -> key: 0
	LogicFactory::AddBuilder(0, new DemoLogic_MainBuilder);
	LogicFactory::AddBuilder(1, new DemoLogic_LV1Builder);
	LogicFactory::AddBuilder(2, new DemoLogic_LV2Builder);
	LogicFactory::AddBuilder(3, new DemoLogic_LV3Builder);
	LogicFactory::AddBuilder(4, new DemoLogic_PauseBuilder);
	LogicFactory::AddBuilder(5, new DemoLogic_GameOverBuilder);
}

#endif // _LOGICBUILDERLIST_H_