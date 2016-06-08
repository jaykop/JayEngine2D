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
	m_invlnertia = 0.f;

	m_mass = FLT_MAX;
	m_inertia = FLT_MAX;
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
		m_inertia = m_mass * (width.x * width.x + width.y * width.y) / 12.f;
		m_invlnertia = 1.f / m_inertia;
	}

	else
	{
		m_invMass = 0.f;
		m_inertia = FLT_MAX;
		m_invlnertia = 0.f;
	}
}

void RigidBody::AddForce(const vec3& force)
{
	m_force += force; 
}

bool RigidBody::DetectCollide(RigidBody* other)
{
	//Shoul I do hard code?
	vec3 halfScl = m_scale/2;
	vec3 other_halfScl = other->m_scale/2;

	if (m_position.x + halfScl.x < other->m_position.x - other_halfScl.x ||
		m_position.x - halfScl.x > other->m_position.x + other_halfScl.x ||
		m_position.y + halfScl.y < other->m_position.y - other_halfScl.y ||
		m_position.y - halfScl.y > other->m_position.y + other_halfScl.y)
		return false;

	return true;
}

void RigidBody::WorkCollide()
{

}