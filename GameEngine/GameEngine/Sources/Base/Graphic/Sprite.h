#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <map>
#include <string>
#include "../Apps/GLApplication.h"
#include "../Math/MathUtils.h"

class Shader;
class Sprite
{
public:
	
	//Constructor and destructor
	Sprite();
	~Sprite();

	//Cretae and delete function
	static Sprite* Create(const std::string& textureDir);
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
	
	/********** To do *********/
	//void SetTexture();
	//GetTexture(void) const;

private:
	
	vec3 m_position;
	vec3 m_scale;
	vec4 m_color;
	float m_degree;

	int m_id;

	//Texture m_texure;
};

#endif // _SPRITE_H_