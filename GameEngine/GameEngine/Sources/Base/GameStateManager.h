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
#include "Utilities\/Time.h"

/*! Enum of all stage types in the game */
enum  StageType { ST_MENU, ST_LV1, ST_LV2, ST_LV3, ST_GAMEOVER };

//forward declaration
class Stage;
class InputManager;

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
	void Init(InputManager* im);
	void Update(void);
	void Shutdown(void);

	bool IsQuitting(void) const;

	/*For use in Stages*/
	void SetNextStage(StageType stageType);
	void SetQuit(bool isQuitting);

private:
	void ChangeGameState(void);

	StageType	  m_current;         //!< The current stage to update
	StageType	  m_next;            //!< The next stage to switch to
	Stage*		  m_pStage;          //!< A pointer to the current stage
	bool      	  m_isQuitting;      //!< To control if the game is quitting.
	bool      	  m_isRestarting;    //!< To control if the stage should restart.
	Timer		  m_dt;
	float		  m_deltaTime;
	InputManager* m_IM;
};

void ProccessMessages(void);

#endif //end GAME_MANAGER_H



