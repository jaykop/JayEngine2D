#include "RigidBody.h"
#include <cfloat>

RigidBody::RigidBody()
{
	m_position = vec3();
	m_velocity = vec3();
	m_force = vec3();
	m_width = vec3();

	m_rotation = 0.f;
	m_angularVelocity = 0.f;
	m_friction = 0.2f;
	m_invMass = 0.f;
	m_invl = 0.f;

	m_mass = FLT_MAX;
	m_l = FLT_MAX;
}


RigidBody::~RigidBody()
{

}

void RigidBody::Set(const vec3& width, float mass)
{
	m_position = vec3();
	m_velocity = vec3();
	m_force = vec3();
	
	m_rotation = 0.f;
	m_angularVelocity = 0.f;
	m_friction = 0.2f;
	m_invMass = 0.f;

	m_width = width;
	m_mass = mass;

	if (m_mass < FLT_MAX)
	{
		m_invMass = 1.f / m_mass;
		m_l = m_mass * (width.x * width.x + width.y * width.y) / 12.f;
		m_invl = 1.f / m_l;
	}

	else
	{
		m_invMass = 0.f;
		m_l = FLT_MAX;
		m_invl = 0.f;
	}
}

void RigidBody::AddForce(const vec3& force)
{
	m_force += force; 
}

