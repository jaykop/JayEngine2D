/******************************************************************************/
/*!
\file   GameManager.h
\author Matt Casanova
\par    email: mcasanov\@digipen.edu
\par    Extra Classes
\par    Assignment #1
\date   01/05/2015
\brief
This is the header for the GameEngine class

*/
/******************************************************************************/
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <stack>
#include <windows.h>
#include "../Factory/Factory.h"

using namespace Resolution;

//forward declaration
class Stage;
class Builder;
class Application;
struct PauseInfo
{
	StageType stage;
	Stage* pStage;
};

/******************************************************************************/
/*!
\class GameManager

Class used to manage all stages in the game.  Allows users to set the next
stage, restart or quit.

*/
/******************************************************************************/
class GameStateManager
{
public:

	/*For use in Main*/
	void Init(Application* pApp);
	void Update(void);
	void Shutdown(void);

	bool IsQuitting(void) const;

	/*For use in Stages*/
	void SetNextStage(StageType stageType);
	void Restart(bool isRestarted);
	void SetQuit(bool isQuitting);
	
	void Pause(void);
	void Resume(void);

	StageType GetCurrentStage(void) const;
	void SetFirstStage(StageType first);
	void AddStage(StageType stage, Builder* pBuilder);

	//Manage resolution
	ScreenSize GetResolution(void) const;
	void SetResolution(const ScreenSize& res);

	void SetFullScreen(bool scr);
	bool GetFullScreen(void) const;

private:

	void TriggerInputController(void);	//Triggered Input Controller
	void ChangeGameState(void);

	bool m_isPausing;
	bool m_isResuming;
	bool m_isQuitting;      //!< To control if the game is quitting.
	bool m_isRestarting;    //!< To control if the stage should restart.

	Stage*		m_pStage;   //!< A pointer to the current stage
	StageType	m_next;     //!< The next stage to switch to
	StageType	m_current;  //!< The current stage to update
	StageType   m_1stStage;

	GameData	m_gameData;
	Factory		m_factory;	
	Application* m_pApp;

	std::stack<PauseInfo> m_pauseStack;
};

void ProccessMessages(void);

#endif //end GAME_MANAGER_H



