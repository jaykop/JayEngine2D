/******************************************************************************/
/*!
\file   ObjectManager.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains ObjectManager's class
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include <hash_map>
#include <vector>
#include "../Graphic/Text.h"

class Scene;
class World;
class Sprite;
class Application;

//! type definition for the list
typedef std::hash_map<int, bool> Relation;
typedef std::hash_map<int, Sprite*> ObjectList;

//! ObjectManager class
class ObjectManager
{
public:
	
	// Constructor and Destructoer
	ObjectManager(void);
	~ObjectManager();

	// Functions manages objects
	void AddObject(const int SpriteID, Type type);
	Sprite* GetSprite(const int id);
	Text* GetText(const int id);
	bool HasObject(const int id);
	void RemoveObject(const int id);
	
	// Manage list
	const ObjectList& GetList(void) const;
	void ClearObjectList(void);

	// Manage main system
	void BindGameSystem(Application* pApp);
	void InitGameSystem(void);
	void UpdateGameSystem(void);
	void ShutdownGameSystem(void);

	// Game System gettor
	Scene* GetGameScene(void) const;
	World* GetGameWorld(void) const;

	const ObjectList& GetObjectList(void) const;

private:
	
	// Sprites info
	ObjectList m_ObjectList;

	// The number of the sprites
	int number_of_Obj;

	// Game system
	Scene* scenePtr;
	World* worldPtr;

};

#endif //_OBJECTMANAGER_H_