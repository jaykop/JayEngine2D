/******************************************************************************/
/*!
\file   Object.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Object's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "../../Utilities/Math/MathUtils.h"

//! Object type
enum Type { SPRITE, TEXT, PARTICLE, AUDIO };

class Object {

public:

	Object(const int id = 0, Type type = SPRITE);
	virtual ~Object();

	// Id functions
	const int GetID(void) const;
	void SetID(const int id);

	// Type functions
	Type GetObjectType(void) const;
	void SetObjectType(Type type);

private:

	// Object id
	int m_id;

	// Object type
	Type  m_type;

};

#endif // _OBJECT_H_