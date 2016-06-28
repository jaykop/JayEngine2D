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
#include "../ObjectManager/Object/Object.h"

//! Sprites' shape
enum Shape { CIRCLE, RECTANGLE };

//! Sprite's prohection type
enum Projt { PERSPECTIVE, ORTHOGONAL };
class RigidBody;

//! Sprite class
class Sprite : public Object
{

public:
	
	//Constructor and destructor
	Sprite(const int id = 0, Type type = SPRITE, ObjectManager* obm = 0);
	virtual ~Sprite();

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

	// Animation functions
	void SetAnimation(int, float);
	void FixAnimation(int);
	float GetAnimationSpeed(void) const;
	int GetAnimationFrame(void) const;

private:

	// Drawing Info
	// Math info
	vec2 m_uv;
	vec3 m_position;
	vec3 m_scale;
	vec4 m_color;
	float m_degree;

	// Type Info
	Shape m_shape;
	Projt m_prjt;

	// Texture Info
	Texture* m_texture;

	// Physics Info
	bool m_HasBody;
	RigidBody* m_body;

};

#endif // _SPRITE_H_