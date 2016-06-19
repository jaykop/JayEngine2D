/******************************************************************************/
/*!
\file   GameStageManager.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains GameStageManager's class and member function
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "../../../Game/BaseData/BaseStage.h"
#include "../../InputManager/InputManager.h"
#include "../../Apps/Application.h"

/******************************************************************************/
/*!
\brief - Function that will initialize the GameStateManager data.

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
\brief - Main game loop that controls Stage switching.

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
			m_pApp->GetGLManager()->GetHDC());

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
\brief - Deallocates game resources

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

\brief - Lets client know if quit has been requested.

\return    - True if the GameStateManager will quit, false otherwise.

*/
/******************************************************************************/
bool GameStateManager::IsQuitting(void) const
{
	return m_isQuitting;
}
/******************************************************************************/
/*!

\brief - Lets the client request a stage change.

\param stageType - The stageType to change to.

\return - NONE

*/
/******************************************************************************/
void GameStateManager::SetNextStage(StageType stageType)
{
	m_next = stageType;
}
/******************************************************************************/
/*!

\brief - Allows the client to request that the game quit.

\param isQuitting - he bool value to set to.

\return - NONE

*/
/******************************************************************************/
void GameStateManager::SetQuit(bool isQuitting)
{
	m_isQuitting = isQuitting;
}
/******************************************************************************/
/*!

\brief - Function to delete old stage and create a new one.

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

/******************************************************************************/
/*!
\brief - Manage proccess messages
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief - Manage proccess messages

\param stage - stage to make
\param pBuilder - pointer to builder
*/
/******************************************************************************/
void GameStateManager::AddStage(StageType stage, Builder* pBuilder)
{
	m_factory.AddBuilder(stage, pBuilder);
}

/******************************************************************************/
/*!
\brief - Refresh key input status 
*/
/******************************************************************************/
void GameStateManager::TriggerInputController(void)
{
	//Get button's status and set trigger's condition
	if (InputManager::GetInstance().GetPressedStatus() == DOWN)
		InputManager::GetInstance().SetTriggerToggle(false);

	else
		InputManager::GetInstance().SetTriggerToggle(true);
}

/******************************************************************************/
/*!
\brief - Restart stage
\param isRestarted
*/
/******************************************************************************/
void GameStateManager::Restart(bool isRestarted)
{
	m_isRestarting = isRestarted;
}

/******************************************************************************/
/*!
\brief - Pause stage
*/
/******************************************************************************/
void GameStateManager::Pause(void)
{
	m_isPausing = true;
}

/******************************************************************************/
/*!
\brief - Resume stage
*/
/******************************************************************************/
void GameStateManager::Resume(void)
{
	//Bo back to the last state
	m_isPausing = false;
}

/******************************************************************************/
/*!
\brief - Set First Stage of app

\param first - stage to be 1st
*/
/******************************************************************************/
void GameStateManager::SetFirstStage(StageType first)
{
	m_1stStage = first;
}

/******************************************************************************/
/*!
\brief - Get aplication's resolution

\return app's resolution
*/
/******************************************************************************/
ScreenSize GameStateManager::GetResolution(void) const
{
	return m_pApp->GetResolution();
}

/******************************************************************************/
/*!
\brief - Set aplication's resolution

\param res - screen resolution
*/
/******************************************************************************/
void GameStateManager::SetResolution(const ScreenSize& res)
{
	m_pApp->SetResolution(res);
}

/******************************************************************************/
/*!
\brief - Set aplication's screen mode

\param scr - screen mode (full ? windowed)
*/
/******************************************************************************/
void GameStateManager::SetFullScreen(bool scr)
{
	m_pApp->SetFullScreen(scr);
}

/******************************************************************************/
/*!
\brief - Get aplication's screen mode

\return app's screen mode
*/
/******************************************************************************/
bool GameStateManager::GetFullScreen(void) const
{
	return m_pApp->GetFullScreen();
}

/******************************************************************************/
/*!
\brief - Get pointer to the app

\return m_pApp
*/
/******************************************************************************/
Application* GameStateManager::GetAppPtr(void)
{
	return m_pApp;
}