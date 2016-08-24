/******************************************************************************/
/*!
\file   Light.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/22(yy/mm/dd)

\description
Contains Light's class functions

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

#include "Light.h"
#include "../../ObjectManager/ObjectManager.h"

Light::Light(const int id, ObjectManager* obm)
:Sprite(id, obm), 
m_diffuse(vec3()), m_distance(0.f), m_radius(0.f)
{
	SetType(LIGHT);
}

Light::Light(Light& light)
:Sprite(light)
{
	m_radius = light.m_radius; 
	m_diffuse = light.m_diffuse;
	m_distance = light.m_distance;
}

Light::~Light()
{
	//None
}

void Light::SetDiffuse(const vec3& diffuse)
{
	m_diffuse = diffuse;
}

void Light::SetDistance(float direction)
{
	m_distance = direction;
}

void Light::SetRadius(float radius)
{
	m_radius = radius;
	SetScale(vec3(radius, radius));
}

const vec3& Light::GetDiffuse(void) const
{
	return m_diffuse;
}

float Light::GetDistance(void) const
{
	return m_distance;
}

float Light::GetRadius(void) const
{
	return m_radius;
}