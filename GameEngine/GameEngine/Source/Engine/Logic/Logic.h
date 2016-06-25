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

#include <hash_map>
#include "../ObjectManager/ObjectManager.h"

class Sprite;
//class ObjectManager;

//! Type definition for list
typedef std::hash_map<int, Sprite*> ObjectList;

class Logic
{

public:

	Logic(void);
	~Logic(void);

	void Init(const ObjectList& objList);
	void Update(const ObjectList& objList);
	void Shutdown(const ObjectList& objList);

private:

	//ObjectManager* m_OBM;

};

#endif //_LOGIC_G_