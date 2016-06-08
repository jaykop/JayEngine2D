#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <string>
#include "../Apps/GLApplication.h"
#include "../Math/MathUtils.h"

class RigidBody;
class Sprite
{
	//friend ObjectManager;

public:
	
	//Constructor and destructor
	Sprite(const int id);
	~Sprite();

	//Cretae and delete function
	static Sprite* Create(const std::string& textureDir = 0);
	void Init();

	const int GetID(void) const;

	//Transforming functions
	void SetPosition(const vec3& position);
	void SetScale(const vec3& scale);
	void SetRotation(float degree);
	
	vec3 GetPosition(void) const;
	vec3 GetScale(void) const;
	float GetRotation(void) const;

	//Color and texture setting
	void SetColor(const vec4& color);
	vec4 GetColor(void) const;
	
	//Physics setting
	void BindRigidBody(void);
	RigidBody* GetRigidBody(void) const;
	void RemoveRigidBody(void);

	/********** To do *********/
	//void SetTexture();
	//GetTexture(void) const;

private:
	
	vec3 m_position;
	vec3 m_scale;
	vec4 m_color;
	float m_degree;

	int m_id;

	RigidBody* m_body;
	//Texture m_texure;

};

#endif // _SPRITE_H_