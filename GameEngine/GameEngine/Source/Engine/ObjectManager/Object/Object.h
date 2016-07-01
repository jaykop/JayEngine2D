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

//! Object type
enum Type { SPRITE, TEXT, PARTICLE };

class GameLogic;
class ObjectManager;

typedef std::hash_map<const char*, GameLogic*> LogicList;

class Object {

public:

	Object(const int id = 0, Type type = SPRITE, ObjectManager* obm = 0);
	virtual ~Object();

	// Id functions
	const int GetID(void) const;
	void SetID(const int id);

	// Type functions
	Type GetObjectType(void) const;
	void SetObjectType(Type type);

	// GameLogic normal function
	void AddLogic(GameLogic* logic);
	void ClearLogicList(void);
	const LogicList& GetLogicList(void) const;

	// GameLogic template function
	template <class Type>
	bool HasLogic(void)
	{
		LogicList::iterator found = m_logicList.find(typeid(Type).name());
		if (found != m_logicList.end())
			return true;

		return false;
	}

	template <class Type>
	Type* GetLogic(void)
	{
		LogicList::iterator found = m_logicList.find(typeid(Type).name());
		if (found != m_logicList.end())
			return static_cast<Type*>(found->second);

		return nullptr;
	}

	template <class Type>
	void DeleteLogic(void)
	{
		LogicList::iterator found = m_logicList.find(typeid(Type).name());
		if (found != m_logicList.end())
			delete found->second;
		
		m_logicList.erase(found);
	}

	ObjectManager* GetOBM(void);

protected:

	//! Just for derived classes
	void SetObjectManager(ObjectManager* obm);

private:

	int m_id;				//! Object id
	Type  m_type;			//! Object type
	ObjectManager* m_OBM;	//! Pointer to object manager
	LogicList m_logicList;	//! Logic list;
};

#endif // _OBJECT_H_