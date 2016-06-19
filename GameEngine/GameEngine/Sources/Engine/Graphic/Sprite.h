#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <string>
#include "Texture.h"
#include "../Utilities/Math/MathUtils.h"

//Sprites' shape
enum Shape { CIRCLE, RECTANGLE };
enum Projt { PERSPECTIVE, ORTHOGONAL };
class RigidBody;
class Sprite
{
	//friend ObjectManager;

public:
	
	//Constructor and destructor
	Sprite(const int id);
	~Sprite();

	// Id gettor
	const int GetID(void) const;

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
	Shape m_type;
	Projt m_prjt;

	// Texture Info
	Texture* m_texture;

	// Physics Info
	bool m_HasBody;
	RigidBody* m_body;

};

#endif // _SPRITE_H_