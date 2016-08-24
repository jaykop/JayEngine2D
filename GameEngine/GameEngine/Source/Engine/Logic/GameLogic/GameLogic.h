/******************************************************************************/
/*!
\file   GameLogic.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/01(yy/mm/dd)

\description
Contains GameLogic's virtual class

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_

#include "../../ObjectManager/Object/Object.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../Utilities/Json/JsonParser.h"

class GameStateManager;

//! Virtual GameLogic class
class GameLogic
{
public:

	// Constructor and Destructor
	/******************************************************************************/
	/*!
	\brief - ObjectManager Constructor
	\param - Logic's original id number
	*/
	/******************************************************************************/
	GameLogic(int key = 0) {
		m_key = key;
	}

	virtual ~GameLogic(void) {};

	// Virtual basic functions
	virtual void Load(const Json::Value& data) = 0;
	virtual void Init(GameData& gd) = 0;
	virtual void Update(GameData& gd) = 0;
	virtual void Shutdown(GameData& gd) = 0;
	virtual void Unload(void) = 0;

	static int GetKey();

private:

	static int m_key;
};

#endif // _GAMELOGIC_H_