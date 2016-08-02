/******************************************************************************/
/*!
\file   Logic.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/25(yy/mm/dd)

\description
Contains Logic's class

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _LOGIC_G_
#define _LOGIC_G_

#include <vector>
//#include <hash_map>
#include "GameLogic.h"
#include "../ObjectManager/ObjectManager.h"

class Sprite;
//class ObjectManager;

//! Type definition for list
//typedef std::hash_map<int, Sprite*> ObjectList;
typedef std::vector<GameLogic*> LogicList;
class Logic
{

public:

	Logic(void);
	~Logic(void);

	void AddLogic(GameLogic* logic);
	void RemoveLogic(GameLogic* logic);
	void ClearLogicList(void);
	const LogicList& GetLogicList(void) const;

	void Init(GameData& gd);
	void Update(GameData& gd);
	void Shutdown(GameData& gd);

private:

	//ObjectManager* m_OBM;
	LogicList m_logicList;

};

#endif //_LOGIC_G_