/******************************************************************************/
/*!
\file   GameStateManager.cpp
\author Matt Casanova
\par    email: mcasanov\@digipen.edu

\brief
GameStateManager implementation for the C++ game engine skeleton.

*/
/******************************************************************************/

#include "../../../Game/BaseData/BaseStage.h"
#include "../../InputManager/InputManager.h"
#include "../../Apps/Application.h"

/******************************************************************************/
/*!
Function that will initialize the GameStateManager data.

\return - NONE
*/
/******************************************************************************/
void GameStateManager::Init(Application* pApp)
{
	//Init gsm info
	m_pApp = pApp;
	m_current = m_1stStage;
	m_next = ST_MENU;
	m_pStage = 0;
	m_gameData.dt = 0;
	m_isQuitting = false;
	m_isRestarting = false;
	m_isPausing = false;
	m_isPausing = false;
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

	//Vsync
	wglSwapIntervalEXT(1);
	
	//Timer timer;
	//timer.StartTime();
	//clock_t current;

	//Update stage in a loop until a stage change/quit/restart is requested.
	while (!m_isQuitting && !m_isRestarting &&
		m_current == m_next)
	{
		//current = clock();				//dt settor
		m_gameData.dt = 1.f / 60;

		ProccessMessages();				//Proccess Messages
		m_pStage->Update(m_gameData);	//Game data update
		TriggerInputController();		//Triggered Input Controller
		SwapBuffers(					//Swap Buffer
			GLApplication::GetInstance().GetHDC());	

		//clock_t newTime;
		//do{
		//	newTime = clock();
		//} while ((newTime - current < CLOCKS_PER_SEC / 60));
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
	m_pStage = m_factory.CreateStage(m_current, this);
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

void GameStateManager::AddStage(StageType stage, Builder* pBuilder)
{
	m_factory.AddBuilder(stage, pBuilder);
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
	m_isPausing = true;
}

void GameStateManager::Resume(void)
{
	//Bo back to the last state
	m_isPausing = false;
}

void GameStateManager::SetFirstStage(StageType first)
{
	m_1stStage = first;
}

ScreenSize GameStateManager::GetResolution(void) const
{
	return m_pApp->GetResolution();
}

void GameStateManager::SetResolution(const ScreenSize& res)
{
	m_pApp->SetResolution(res);
}

void GameStateManager::SetFullScreen(bool scr)
{
	m_pApp->SetFullScreen(scr);
}

bool GameStateManager::GetFullScreen(void) const
{
	return m_pApp->GetFullScreen();
}