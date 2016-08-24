/******************************************************************************/
/*!
\file   Light.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/22(yy/mm/dd)

\description
Contains Light's class and member

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/
#ifndef _LIGHT_H_
#define _LIGHT_H_

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
	void SetDistance(float distance);
	void SetRadius(float radius);

	const vec3& GetDiffuse(void) const;
	float GetDistance(void) const;
	float GetRadius(void) const;

private:

	vec3 m_diffuse;
	float m_distance;
	float m_radius;

};

#endif // _LIGHT_H_