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

	/******************************************************************************/
	/*!
	\brief - Add Object to the list

	\param type - new sprite
	*/
	/******************************************************************************/
	template <class Type>
	void AddObject(Type* type)
	{
		//Make new sprite
		Type* new_sprite = type;

		static_cast<Sprite*>(new_sprite)->SetTexture(new Texture);

		//Push it into the list
		m_ObjectList.insert(std::hash_map<int, Sprite*>::value_type(
			new_sprite->GetID(), new_sprite));

		scenePtr->AddSprite(new_sprite);

		//Change id number and the number of sprites;
		++number_of_Obj;
	}

	///******************************************************************************/
	///*!
	//\brief - Make sprite's clone

	//\param new_sprite - new sprite
	//\param quantity - quantity of clone
	//*/
	///******************************************************************************/
	//template <class Type>
	//void MakeClone(Type* new_sprite, Type* existing, int quantity)
	//{
	//	for (int i = 1; i <= quantity; ++i)
	//		AddObject(new_sprite);
	//}

	/******************************************************************************/
	/*!
	\brief - Get Sprite from the obm

	\param SpriteID - sprite's id
	*/
	/******************************************************************************/
	template <class Type>
	Type* GetGameObject(const int id)
	{
		auto found = m_ObjectList.find(id);

		// if found one is in the list,
		// return it
		if (found != m_ObjectList.end())
			return static_cast<Type*>(found->second);

		// if not, return 0
		return nullptr;
	}

	bool HasObject(const int id);
	void RemoveObject(const int id);
	void MakeClone(const int id, const int clone_id, int quantity = 1);

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