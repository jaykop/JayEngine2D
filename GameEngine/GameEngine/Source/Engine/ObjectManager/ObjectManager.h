/******************************************************************************/
/*!
\file   ObjectManager.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains ObjectManager's class
All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include "../Graphic/Text/Text.h"
#include "../../Game/BaseData/GameData.h"
#include "../Utilities/Json/JsonParser.h"

class Sound;
class Logic;
class Scene;
class World;
class GameStateManager;

//! type definition for the list
typedef std::unordered_map<int, bool> Relation;
typedef std::unordered_map<int, Sprite*> ObjectList;

//! ObjectManager class
class ObjectManager
{
public:
	
	//! Constructor and Destructoer
	ObjectManager(void);
	~ObjectManager();

	//! Functions manages objects
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

		//Push it into the list
		m_ObjectList.insert(std::unordered_map<int, Sprite*>::value_type(
			new_sprite->GetID(), new_sprite));

		scenePtr->AddSprite(new_sprite);

		//Change id number and the number of sprites;
		++number_of_Obj;
	}

	/******************************************************************************/
	/*!
	\brief - Make sprite's clone

	\param new_sprite - new sprite
	\param quantity - quantity of clone
	*/
	/******************************************************************************/
	template <class Type>
	void MakeClone(Type* new_sprite, int quantity, bool same_id)
	{
		for (int i = 1; i <= quantity; ++i)
		{
			Type* new_Object = new Type(*new_sprite);
			if (!same_id)
			{
				Sprite* converted = static_cast<Sprite*>(new_Object);
				converted->SetID(new_sprite->GetID() + i);
				converted->SetTexture(new Texture(
					*static_cast<Sprite*>(new_sprite)->GetTexture()));
			}
			AddObject(new_Object, true);
		}
	}

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

	//! Manage list
	const ObjectList& GetList(void) const;
	void ClearObjectList(void);

	//! Manage main system
	void BindGameSystem(GameStateManager* gsm);
	void LoadStageData(char* dir);
	void InitGameSystem(GameData& gd);
	void UpdateGameSystem(GameData& gd);
	void ShutdownGameSystem(GameData& gd);
	void UnloadStageData(void);

	//! Game System gettor
	Scene* GetGameScene(void) const;
	World* GetGameWorld(void) const;
	Logic* GetGameLogic(void) const;
	Sound* GetGameSound(void) const;

	const ObjectList& GetObjectList(void) const;
	GameStateManager* GetGSM(void);

private:
	
	//! Sprites info
	ObjectList m_ObjectList;

	//! Json Parser
	JsonParser m_Loader;

	//! The number of the sprites
	int number_of_Obj;

	//! Game system
	Scene* scenePtr;
	World* worldPtr;
	Logic* logicPtr;
	Sound* soundPtr;

	//! Pointer to GameStateManager
	GameStateManager* m_GSM;
};

#endif //_OBJECTMANAGER_H_