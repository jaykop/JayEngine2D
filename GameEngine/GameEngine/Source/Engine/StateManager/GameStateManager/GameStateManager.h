/******************************************************************************/
/*!
\file   GameStageManager.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains GameStageManager's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <stack>
#include <windows.h>
#include "../StageFactory/StageFactory.h"

using namespace Resolution;

//! forward declaration
class Stage;
class GLManager;
class Application;
class StageBuilder;
class SoundManager;

//! Stage stack information
struct StageInfo
{
	//! Stage stack's info
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

	// Destructor
	~GameStateManager();

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
	void AddStage(StageType stage, StageBuilder* pBuilder);

	//! Manage resolution
	ScreenSize GetResolution(void) const;
	void SetResolution(const ScreenSize& res);

	//! Manage window mode
	void SetFullScreen(bool scr);
	bool GetFullScreen(void) const;

	//! Pointer to app gettor
	Application* GetAppPtr(void);
	GLManager* GetGLManager(void);
	SoundManager* GetSoundManager(void);

private:

	void TriggerInputController(void);	//!< Triggered Input Controller
	void ChangeGameState(void);			//!< Changed the current stage

	bool m_isPausing;		//!< To control if the game is pausing.
	bool m_isResuming;		//!< To control if the game is resuming.
	bool m_isQuitting;      //!< To control if the game is quitting.
	bool m_isRestarting;    //!< To control if the stage should restart.

	Stage*		m_pStage;   //!< A pointer to the current stage
	Stage*		m_paused;	//!< A pointer to the pause stage
	StageType	m_next;     //!< The next stage to switch to
	StageType	m_current;  //!< The current stage to update
	StageType   m_1stStage;	//!< The 1st stage of this application

	GameData	 m_gameData;//!< Game data to be used
	StageFactory m_factory;	//!< Factory that makes new stages
	Application* m_pApp;	//!< pointer to the application

	std::stack<StageInfo> m_StageStack;
};

void ProccessMessages(void);

#endif //end GAME_MANAGER_H



