#include "Sprite.h"

Sprite::Sprite(void)
{
	m_position = vec3(0.f, 0.f, 0.f);
	m_scale = vec3(1.f, 1.f, 0.f);
	m_degree = 0;
	m_color = vec4(1.f);
}

Sprite::~Sprite(void)
{}

const int Sprite::GetID(void) const
{
	return m_id;
}

void Sprite::Init(void)
{
	//Todo: something here?
}

void Sprite::SetPosition(const vec3& position)
{
	m_position = position;
}

void Sprite::SetScale(const vec3& scale)
{
	m_scale = scale;
}

void Sprite::SetRotation(float degree)
{
	m_degree = degree;
}

vec3 Sprite::GetPosition(void) const
{
	return m_position;
}

vec3 Sprite::GetScale(void) const
{
	return m_scale;
}

float Sprite::GetRotation(void) const
{
	return m_degree;
}

void Sprite::SetColor(const vec4& color)
{
	m_color = color;
}

vec4 Sprite::GetColor(void) const
{
	return m_color;
}