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
typedef std::hash_map<int, Sprite*> SpriteList;
typedef std::hash_map<int, Text*> TextList;

//! ObjectManager class
class ObjectManager
{
public:
	
	// Constructor and Destructoer
	ObjectManager(void);
	~ObjectManager();

	// Functions manages objects
	void AddObject(const int SpriteID, Type type = NORMAL,
		const char* textureDir = "Resource/Texture/rect.png");
	Sprite* GetGameObject(const int id, Type type = NORMAL);
	bool HasObject(const int id, Type type = NORMAL);
	void RemoveObject(const int id, Type type = NORMAL);
	
	// Manage list
	const SpriteList& GetList(void) const;
	void ClearObjectList(void);

	// Manage main system
	void BindGameSystem(Application* pApp);
	void InitGameSystem();
	void UpdateGameSystem(void);
	void ShutdownGameSystem();

	// Game System gettor
	Scene* GetGameScene(void) const;
	World* GetGameWorld(void) const;

	const SpriteList& GetSpriteList(void) const;
	const TextList& GetTextList(void) const;

private:
	
	// Sprites info
	SpriteList m_SpriteList;
	TextList m_TextList;

	// The number of the sprites
	int number_of_Spt;

	// Game system
	Scene* scenePtr;
	World* worldPtr;

};

#endif //_OBJECTMANAGER_H_