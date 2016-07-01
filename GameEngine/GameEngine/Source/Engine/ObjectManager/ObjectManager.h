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

#include <vector>
#include "../Graphic/Text.h"

class Sound;
class Logic;
class Scene;
class World;
class Sprite;
class Emitter;
class GameStateManager;

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
	Emitter* GetEmitter(const int id);
	bool HasObject(const int id);
	void RemoveObject(const int id);
	
	// Manage list
	const ObjectList& GetList(void) const;
	void ClearObjectList(void);

	// Manage main system
	void BindGameSystem(GameStateManager* gsm);
	void InitGameSystem(void);
	void UpdateGameSystem(void);
	void ShutdownGameSystem(void);

	// Game System gettor
	Scene* GetGameScene(void) const;
	World* GetGameWorld(void) const;
	Logic* GetGameLogic(void) const;
	Sound* GetGameSound(void) const;

	const ObjectList& GetObjectList(void) const;
	GameStateManager* GetGSM(void);

private:
	
	// Sprites info
	ObjectList m_ObjectList;

	// The number of the sprites
	int number_of_Obj;

	// Game system
	Scene* scenePtr;
	World* worldPtr;
	Logic* logicPtr;
	Sound* soundPtr;

	// Pointer to GameStateManager
	GameStateManager* m_GSM;
};

#endif //_OBJECTMANAGER_H_