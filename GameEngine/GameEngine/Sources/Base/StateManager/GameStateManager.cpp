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
void GameStateManager::Init(InputManager* im)
{
	//Init gsm info
	m_current = ST_MENU;
	m_next = ST_MENU;
	m_pStage = 0;
	m_deltaTime = 0;
	m_isQuitting = false;
	m_isRestarting = false;
	m_IM = im;

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
	if (!m_isRestarting)
		ChangeGameState();

	//Init current stage
	m_pStage->Init(m_gameData);

	//Vsync
	wglSwapIntervalEXT(1);

	//Update stage in a loop until a stage change/quit/restart is requested.
	while (!m_isQuitting && !m_isRestarting &&
		m_current == m_next)
	{
		ProccessMessages();

		//Refresh the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.f, 0.f, 0.f, 0.f);

		//Game data update
		m_pStage->Update(m_gameData);

		//Triggered Input Controller
		TriggerInputController();

		//Swap Buffer
		SwapBuffers(GLApplication::GetInstance().GetHDC());
	}

	//shutdown current stage
	m_pStage->Shutdown();

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
	m_pStage = 0;
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
		m_pStage = new MenuStage(this, m_IM);
		break;
	case ST_LV1:
		m_pStage = new LV1Stage(this, m_IM);
		break;
	case ST_LV2:
		m_pStage = new LV2Stage(this, m_IM);
		break;
	case ST_LV3:
		m_pStage = new LV3Stage(this, m_IM);
		break;
	case ST_GAMEOVER:
		m_pStage = new GameOverStage(this, m_IM);
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

void GameStateManager::SetRestart(bool isRestarted)
{
	m_isRestarting = isRestarted;
}

void GameStateManager::SetPause(bool isPaused)
{
	//Goto pause state(?)
	isPaused;
}

void GameStateManager::SetResume(void)
{
	//Bo back to the last state
}