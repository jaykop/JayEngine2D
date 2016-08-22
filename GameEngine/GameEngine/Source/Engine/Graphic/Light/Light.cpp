/******************************************************************************/
/*!
\file   Light.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/22(yy/mm/dd)

\description
Contains Light's class functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Light.h"
#include "../../ObjectManager/ObjectManager.h"

Light::Light(const int id, ObjectManager* obm)
:Sprite(id, obm), 
m_diffuse(vec3()), m_direction(vec3()), m_radius(0.f)
{
	SetType(LIGHT);
}

Light::Light(Light& light)
:Sprite(light)
{
	m_diffuse = light.m_diffuse;
	m_direction = light.m_direction;
	m_radius = light.m_radius;
}

Light::~Light()
{
	//None
}

void Light::SetDiffuse(const vec3& diffuse)
{
	m_diffuse = diffuse;
}

void Light::SetDirection(const vec3& direction)
{
	m_direction = direction;
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

const vec3& Light::GetDirection(void) const
{
	return m_direction;
}

float Light::GetRadius(void) const
{
	return m_radius;
}