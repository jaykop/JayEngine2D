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

#include <map>
#include "GameLogic/GameLogic.h"
#include "../ObjectManager/ObjectManager.h"

class Sprite;

//! Logic System class
class Logic
{

public:

	//! Constructor and Destructor
	Logic(void);
	~Logic(void);

	//! Loop functions
	void Load(const ObjectList& objList, const Json::Value& data);
	void Init(const ObjectList& objList, GameData& gd);
	void Update(const ObjectList& objList, GameData& gd);
	void Shutdown(const ObjectList& objList, GameData& gd);
	void Unload(const ObjectList& objList);

private:

};

#endif //_LOGIC_G_