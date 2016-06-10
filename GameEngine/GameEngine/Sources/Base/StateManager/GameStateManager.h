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

#include <windows.h>
#include "../../States/BaseStage/GameData.h"

/*! Enum of all stage types in the game */
enum  StageType { ST_MENU, ST_LV1, ST_LV2, ST_LV3, ST_GAMEOVER, ST_PAUSE };

//forward declaration
class Stage;

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
	void Init(void);
	void Update(void);
	void Shutdown(void);

	bool IsQuitting(void) const;

	/*For use in Stages*/
	void SetNextStage(StageType stageType);
	void Restart(bool isRestarted);
	void SetQuit(bool isQuitting);
	
	void Pause(void);
	void Resume(void);

private:

	//Triggered Input Controller
	void TriggerInputController(void);

	void ChangeGameState(void);

	bool		m_isPaused;
	bool      	m_isQuitting;      //!< To control if the game is quitting.
	bool      	m_isRestarting;    //!< To control if the stage should restart.

	Stage*		m_pStage;          //!< A pointer to the current stage
	Stage*		m_pPause;
	StageType	m_next;            //!< The next stage to switch to
	StageType	m_current;         //!< The current stage to update
	
	GameData	m_gameData;
	
};

void ProccessMessages(void);

#endif //end GAME_MANAGER_H



