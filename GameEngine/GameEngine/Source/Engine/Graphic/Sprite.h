/******************************************************************************/
/*!
\file   Sprite.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Sprite's class and members
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <map>
#include "Texture.h"
#include "../Utilities/Math/MathUtils.h"

//! Sprite's type
enum Type {NORMAL, TEXT, PARTICLE};

//! Sprites' shape
enum Shape { CIRCLE, RECTANGLE };

//! Sprite's prohection type
enum Projt { PERSPECTIVE, ORTHOGONAL };
class RigidBody;

//! Pointer to GameStateManager
class GameStateManager;

//! Sprite class
class Sprite
{

public:
	
	//Constructor and destructor
	Sprite(const int id = 0, Type type = NORMAL);
	~Sprite();

	// Id functions
	const int GetID(void) const;
	void SetID(const int id);

	// Type functions
	Type GetSpriteType(void) const;
	void SetSpriteType(Type type);

	// Transforming functions
	void SetPosition(const vec3& position);
	void SetScale(const vec3& scale);
	void SetRotation(float degree);
	
	vec3 GetPosition(void) const;
	vec3 GetScale(void) const;
	float GetRotation(void) const;

	// Color and texture setting
	void SetColor(const vec4& color);
	vec4 GetColor(void) const;
	
	// Physics setting
	void BindRigidBody(void);
	RigidBody* GetRigidBody(void) const;
	void RemoveRigidBody(void);
	bool HasRigidBody(void) const;

	// Sprite's shape type
	void SetSpriteShape(Shape type);
	Shape GetSpriteShape(void) const;

	// Sprite's texture 
	void SetTexture(Texture* texture);
	Texture* GetTexture(void) const;

	// Projection type
	void SetProjectionType(Projt projection);
	Projt GetProjectionType(void) const;

	// Empty functions; for Text class
	virtual void SetText(wchar_t* text);
	virtual wchar_t* GetText(void) const;

private:
	
	// Sprite id
	int m_id;

	// Drawing Info
	// Math info
	vec3 m_position;
	vec3 m_scale;
	vec4 m_color;
	float m_degree;

	// Type Info
	Type  m_type;
	Shape m_shape;
	Projt m_prjt;

	// Texture Info
	Texture* m_texture;

	// Physics Info
	bool m_HasBody;
	RigidBody* m_body;

};

#endif // _SPRITE_H_