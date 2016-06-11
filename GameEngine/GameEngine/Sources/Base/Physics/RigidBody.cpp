#include "../Graphic/Sprite.h"
#include "RigidBody.h"

RigidBody::RigidBody()
:m_fixed(true), m_collider(true), m_body(true),
m_speed(vec3()), m_velocity(vec3()), m_direction(0),
m_scale(0), m_acceleration(0)
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
	m_collider = active;
}

bool RigidBody::GetColliderToggle(void) const
{
	return m_collider;
}

void RigidBody::ActivateBody(bool active)
{
	m_body = active;
}

bool RigidBody::GetBodyToggle(void) const
{
	return m_body;
}

void RigidBody::SetAcceleration(float acceleration)
{
	m_acceleration = acceleration;
}

float RigidBody::GetAcceleration(void) const
{
	return m_acceleration;
}

void RigidBody::SetSpeed(const vec3& speed)
{
	m_speed = speed;
}

vec3 RigidBody::GetSpeed(void) const
{
	return m_speed;
}

void RigidBody::SetVelocity(const vec3& velocity)
{
	m_velocity = velocity;
}

vec3 RigidBody::GetVelocity(void) const
{
	return m_velocity;
}

void RigidBody::ClearVelocity(void)
{
	m_speed = vec3();
	m_velocity = vec3();
	m_direction = 0;
}

void RigidBody::SetScale(const vec3& scale)
{
	m_scale = scale;
}

vec3 RigidBody::GetScale(void) const
{
	return m_scale;
}

void RigidBody::SetRotation(float direction)
{
	m_direction = direction;
}

float RigidBody::GetRotation(void) const
{
	return m_direction;
}
