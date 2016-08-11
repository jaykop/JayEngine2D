/******************************************************************************/
/*!
\file   MainMenu.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains MainMenu's class functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "MainMenu.h"
#include "../BaseData/BaseEnigne.h"
#include "../GameLogic/DemoLogic_Main.h"

/******************************************************************************/
/*!
\brief - MenuStage constructor

\param gsm - pointer to the gams state manager
*/
/******************************************************************************/
MenuStage::MenuStage(GameStateManager* gsm)
{
	m_GSM = gsm;
}

/******************************************************************************/
/*!
\brief - MenuStage destructor
*/
/******************************************************************************/
MenuStage::~MenuStage()
{

}

void MenuStage::Load(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "MenuStage::Load\n";

	//Bind basic systems
	m_OBM.BindGameSystem(m_GSM);

	// Load json data
	m_OBM.LoadStageData("Resource/Data/Main.json");
}

void MenuStage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "MenuStage::Init\n";

	// Init basic systems
	m_OBM.InitGameSystem(gd);
}

void MenuStage::Update(GameData& gd)
{	
	UNREFERENCED_PARAMETER(gd);
	std::cout << "MenuStage::Update\n";

	// Update basic systems
	m_OBM.UpdateGameSystem(gd);
}

void MenuStage::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "MenuStage::Shutdown\n";

	// Shutdown basic systems
	m_OBM.ShutdownGameSystem(gd);

	// Cleare all Objects of the list
	m_OBM.ClearObjectList();
}

void MenuStage::Unload(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "MenuStage::Unload\n";

	// Unload stage data
	m_OBM.UnloadStageData();
}
