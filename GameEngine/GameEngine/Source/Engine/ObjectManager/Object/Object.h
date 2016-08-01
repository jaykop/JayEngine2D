/******************************************************************************/
/*!
\file   Object.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/25(yy/mm/dd)

\description
Contains Object's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <hash_map>
#include "../../Utilities/Math/MathUtils.h"

enum ObjectType{ TEXT, SPRITE, PARTICLE, LIGHT };

class GameLogic;
class ObjectManager;

typedef std::hash_map<const char*, GameLogic*> LogicMap;

//! Basic Object class
class Object {

public:

	Object(const int id = 0, ObjectManager* obm = 0);
	Object(const Object& object);
	virtual ~Object();

	// Id functions
	const int GetID(void) const;
	void SetID(const int id);
	ObjectType GetType(void) const;

	// GameLogic normal function
	void AddLogic(GameLogic* logic);
	void ClearLogicList(void);
	const LogicMap& GetLogicList(void) const;

	/******************************************************************************/
	/*!
	\brief - Check if there is specific logic
	*/
	/******************************************************************************/
	template <class Type>
	bool HasLogic(void)
	{
		LogicMap::iterator found = m_logicList.find(typeid(Type).name());
		if (found != m_logicList.end())
			return true;

		return false;
	}

	/******************************************************************************/
	/*!
	\brief - Get specific logic
	*/
	/******************************************************************************/
	template <class Type>
	Type* GetLogic(void)
	{
		LogicMap::iterator found = m_logicList.find(typeid(Type).name());
		if (found != m_logicList.end())
			return static_cast<Type*>(found->second);

		return nullptr;
	}

	/******************************************************************************/
	/*!
	\brief - Delete specific logic
	*/
	/******************************************************************************/
	template <class Type>
	void DeleteLogic(void)
	{
		LogicMap::iterator found = m_logicList.find(typeid(Type).name());
		if (found != m_logicList.end())
			delete found->second;
		
		m_logicList.erase(found);
	}

	ObjectManager* GetOBM(void);

protected:

	//! Just for derived classes
	void SetObjectManager(ObjectManager* obm);
	void SetType(ObjectType type);

private:

	int m_id;				//! Object id
	ObjectManager* m_OBM;	//! Pointer to object manager
	LogicMap m_logicList;	//! Logic list;
	ObjectType m_type;		//! Object type
};

#endif // _OBJECT_H_