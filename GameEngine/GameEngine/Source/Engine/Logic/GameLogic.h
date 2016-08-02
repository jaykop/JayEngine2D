/******************************************************************************/
/*!
\file   GameLogic.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/01(yy/mm/dd)

\description
Contains GameLogic's virtual class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_

#include "../ObjectManager/Object/Object.h"
#include "../ObjectManager/ObjectManager.h"
#include "../Utilities/Json/JsonParser.h"

class GameStateManager;
class GameLogic
{
public:

	GameLogic(Object* owner = 0)
		:m_Owner(owner), m_OBM(0), m_GSM(0) {};

	virtual ~GameLogic(void) {};

	virtual void Load(const Json::Value& data) = 0;
	virtual void Init(GameData& gd) = 0;
	virtual void Update(GameData& gd) = 0;
	virtual void Shutdown(GameData& gd) = 0;
	virtual void Unload(void) = 0;

private:

	Object* m_Owner;
	ObjectManager* m_OBM;
	GameStateManager* m_GSM;
};

#endif // _GAMELOGIC_H_