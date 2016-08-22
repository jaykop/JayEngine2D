/******************************************************************************/
/*!
\file   Light.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/22(yy/mm/dd)

\description
Contains Light's class and member

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "../Sprite/Sprite.h"

//! Light class
class Light : public Sprite
{

public:

	//! Constructor and destructor
	Light(const int id = 0, ObjectManager* obm = 0);
	Light(Light& light);
	virtual ~Light();

	// Manage light info
	void SetDiffuse(const vec3& diffuse);
	void SetDirection(const vec3& direction);
	void SetRadius(float radius);

	const vec3& GetDiffuse(void) const;
	const vec3& GetDirection(void) const;
	float GetRadius(void) const;

private:

	vec3 m_diffuse;
	vec3 m_direction;
	float m_radius;

};