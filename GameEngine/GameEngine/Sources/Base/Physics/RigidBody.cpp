#include "RigidBody.h"
#include <cfloat>

RigidBody::RigidBody()
: m_fixed(true), m_collide(true), m_active(true), 
m_degree(0), m_position(vec3()), m_velocity(vec3())
{}

RigidBody::~RigidBody()
{}

void RigidBody::SetStatus(bool status)
{
	m_fixed = status;
}

bool RigidBody::GetStatus(void) const
{
	return m_fixed;
}

void RigidBody::ActivateCollider(bool active)
{
	m_active = active;
}

void RigidBody::SetVertices(void)
{
	//  vert[1]     vert[2]
	//    |----------|
	//    |		     |
	//    |		     |
	//    |		     |
	//    |----------|
	//	vert[0]     vert[4]

	m_vertice[0] = vec3(m_position.x - m_scale.x / 2, m_position.y - m_scale.y / 2, m_position.z);
	m_vertice[1] = vec3(m_position.x - m_scale.x / 2, m_position.y + m_scale.y / 2, m_position.z);
	m_vertice[2] = vec3(m_position.x + m_scale.x / 2, m_position.y + m_scale.y / 2, m_position.z);
	m_vertice[3] = vec3(m_position.x + m_scale.x / 2, m_position.y - m_scale.y / 2, m_position.z);
}

vec3 RigidBody::GetVertice(int index) const
{
	return m_vertice[index];
}

void RigidBody::SetVelocity(vec3& velocity)
{
	m_velocity = velocity;
}

vec3 RigidBody::GetVelocity(void) const
{
	return m_velocity;
}

void RigidBody::WorkVelocity(void)
{
	m_position.x += m_velocity.x * cosf(m_degree);
	m_position.y += m_velocity.y * sinf(m_degree);
}

void RigidBody::ClearVelocity(void)
{
	m_velocity = vec3();
	m_degree = 0;
}

void RigidBody::SetPosition(vec3& position)
{
	m_position = position;
}
vec3 RigidBody::GetPosition(void) const
{
	return m_position;
}
void RigidBody::SetScale(vec3& scale)
{
	m_scale = scale;
}
vec3 RigidBody::GetScale(void) const
{
	return m_scale;
}
void RigidBody::SetRotation(float degree)
{
	m_degree = degree;
}
float RigidBody::GetRotation(void) const
{
	return m_degree;
}

void RigidBody::WorkCollide()
{

}
