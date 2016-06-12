#include "../Graphic/Sprite.h"
#include "RigidBody.h"

RigidBody::RigidBody()
:m_move(true), m_collider(true), m_isCollided(false),
m_speed(vec3()), m_velocity(vec3()), m_lastPos(vec3()),
m_direction(0), m_scale(0), m_acceleration(0), m_friction(0)
{}

RigidBody::~RigidBody()
{}

void RigidBody::ActivateMove(bool move)
{
	m_move = move;
}

bool RigidBody::GetMoveToggle(void) const
{
	return m_move;
}

void RigidBody::ActivateCollider(bool active)
{
	m_collider = active;
}

bool RigidBody::GetColliderToggle(void) const
{
	return m_collider;
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

void RigidBody::SetDirectionAngle(float direction)
{
	m_direction = direction;
}

float RigidBody::GetDirectionAngle(void) const
{
	return m_direction;
}

void RigidBody::SetLastPosition(const vec3& position)
{
	m_lastPos = position;
}

vec3 RigidBody::GetLastPosition(void) const
{
	return m_lastPos;
}

void RigidBody::SetForce(const vec3& force)
{
	vec3 get_force = force;
	m_velocity = get_force;
	m_speed = get_force.Absolute();
}

bool RigidBody::IsCollided(void) const
{
	return m_isCollided;
}

void RigidBody::CheckCollided(bool collided)
{
	m_isCollided = collided;
}

void RigidBody::SetFriction(float friction)
{
	m_friction = friction;
}

float RigidBody::GetFriction(void) const
{
	return m_friction;
}