#include "Sprite.h"
#include "../Physics/RigidBody.h"

Sprite::Sprite(const int id)
{
	m_position = vec3(0.f, 0.f, 0.f);
	m_scale = vec3(5.f, 5.f, 0.f);
	m_degree = 0;
	m_color = vec4(1.f);
	m_HasBody = false;
	m_body = 0;
	m_id = id;
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

void Sprite::BindRigidBody(void)
{
	m_body = new RigidBody();
	m_body->SetScale(m_scale);
	m_HasBody = true;
}

RigidBody* Sprite::GetRigidBody(void) const
{
	if (m_HasBody)
		return m_body;

	return nullptr;
}

void Sprite::RemoveRigidBody(void)
{
	if (m_body)
	{
		delete m_body;
		m_body = 0;
		m_HasBody = false;
	}
}

bool Sprite::HasRigidBody(void) const
{
	return m_HasBody;
}