/******************************************************************************/
/*!
\file   GameStateManager.cpp
\author Matt Casanova
\par    email: mcasanov\@digipen.edu

\brief
GameStateManager implementation for the C++ game engine skeleton.

*/
/******************************************************************************/

#include "../../States/BaseStage/BaseStage.h"
#include "../../States/BaseStage/LoadStages.h"
#include "../../States/BaseStage/GameData.h"
#include "../InputManager/InputManager.h"
#include "../Apps/GLApplication.h"
#include "GameStateManager.h"
#include <iostream>

/******************************************************************************/
/*!
Function that will initialize the GameStateManager data.

\return - NONE
*/
/******************************************************************************/
void GameStateManager::Init(void)
{
	//Init gsm info
	m_current = ST_MENU;
	m_next = ST_MENU;
	m_pStage = 0;
	m_isQuitting = false;
	m_isRestarting = false;
	m_isPaused = false;
	m_pPause = new PauseStage(this);

}
/******************************************************************************/
/*!
Main game loop that controls Stage switching.

\return - NONE
*/
/******************************************************************************/
void GameStateManager::Update(void)
{
	//if we are not restarting, we need to change stages
	ChangeGameState();

	//Init current stage
	m_pStage->Init(m_gameData);
	m_pPause->Init(m_gameData);

	//Vsync
	wglSwapIntervalEXT(1);

	//Update stage in a loop until a stage change/quit/restart is requested.
	while (!m_isQuitting && !m_isRestarting &&
		m_current == m_next)
	{
		ProccessMessages();

		//Game data update
		if (!m_isPaused)
			m_pStage->Update(m_gameData);
		else
			m_pPause->Update(m_gameData);
		
		//Triggered Input Controller
		TriggerInputController();

		//Swap Buffer
		SwapBuffers(GLApplication::GetInstance().GetHDC());
	}

	//shutdown current stage
	m_pStage->Shutdown();
	m_pPause->Shutdown();

}
/******************************************************************************/
/*!
Deallocates game resources

\return - NONE
*/
/******************************************************************************/
void GameStateManager::Shutdown(void)
{
	//The last stage doesn't get deleted in the loop, so it is deleted here.
	delete m_pStage;
	delete m_pPause;
	m_pStage = 0;
	m_pPause = 0;
}
/******************************************************************************/
/*!

Lets client know if quit has been requested.

\return    - True if the GameStateManager will quit, false otherwise.

*/
/******************************************************************************/
bool GameStateManager::IsQuitting(void) const
{
	return m_isQuitting;
}
/******************************************************************************/
/*!

Lets the client request a stage change.

\param stageType
The stageType to change to.

\return - NONE

*/
/******************************************************************************/
void GameStateManager::SetNextStage(StageType stageType)
{
	m_next = stageType;
}
/******************************************************************************/
/*!

Allows the client to request that the game quit.

\param isQuitting
The bool value to set to.

\return - NONE

*/
/******************************************************************************/
void GameStateManager::SetQuit(bool isQuitting)
{
	m_isQuitting = isQuitting;
}
/******************************************************************************/
/*!

Function to delete old stage and create a new one.

\return - NONE

*/
/******************************************************************************/
void GameStateManager::ChangeGameState(void)
{
	//Update information that was changed last frame.
	m_current = m_next;
	m_isRestarting = false;

	//Delete the old stage
	delete m_pStage;
	m_pStage = 0;

	//dynamically allocate a new stage based on the current state (use a swtich)
	switch (m_current)
	{
	case ST_MENU:
		m_pStage = new MenuStage(this);
		break;
	case ST_LV1:
		m_pStage = new LV1Stage(this);
		break;
	case ST_LV2:
		m_pStage = new LV2Stage(this);
		break;
	case ST_LV3:
		m_pStage = new LV3Stage(this);
		break;
	case ST_GAMEOVER:
		m_pStage = new GameOverStage(this);
		break;
	//case ST_PAUSE:
		//m_pPause = new PauseStage(this);
		break;
	}
}

void ProccessMessages(void)
{
	//m_window->NULL??
	MSG message;
	while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

void GameStateManager::TriggerInputController(void)
{
	//Get button's status and set trigger's condition
	if (InputManager::GetInstance().GetPressedStatus() == DOWN)
		InputManager::GetInstance().SetTriggerToggle(false);

	else
		InputManager::GetInstance().SetTriggerToggle(true);
}

void GameStateManager::Restart(bool isRestarted)
{
	m_isRestarting = isRestarted;
}

void GameStateManager::Pause(void)
{
	//Goto pause state(?)
	m_isPaused = true;
}

void GameStateManager::Resume(void)
{
	//Bo back to the last state
	m_isPaused = false;
}