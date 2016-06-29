/******************************************************************************/
/*!
\file   RigidBody.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains RigidBody's class member functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "../Graphic/Sprite.h"
#include "RigidBody.h"

/******************************************************************************/
/*!
\brief - RigidBody Constructor
*/
/******************************************************************************/
RigidBody::RigidBody()
:m_move(true), m_collider(true), m_isCollided(false),
m_speed(vec3()), m_velocity(vec3()), m_lastPos(vec3()),
m_direction(0), m_scale(0), m_acceleration(0), m_friction(0), m_shape(RECTANGLE)
{}

/******************************************************************************/
/*!
\brief - RigidBody destructor
*/
/******************************************************************************/
RigidBody::~RigidBody()
{}

/******************************************************************************/
/*!
\brief - Activate to move

\param move 
*/
/******************************************************************************/
void RigidBody::ActivateMove(bool move)
{
	m_move = move;
}

/******************************************************************************/
/*!
\brief - Get Move Toggle

\return m_move
*/
/******************************************************************************/
bool RigidBody::GetMoveToggle(void) const
{
	return m_move;
}

/******************************************************************************/
/*!
\brief - Set body's collision toggle

\param active
*/
/******************************************************************************/
void RigidBody::ActivateCollider(bool active)
{
	m_collider = active;
}

/******************************************************************************/
/*!
\brief - Get Collider Toggle

\return m_collider
*/
/******************************************************************************/
bool RigidBody::GetColliderToggle(void) const
{
	return m_collider;
}

/******************************************************************************/
/*!
\brief - Set body's acceleration

\param acceleration
*/
/******************************************************************************/
void RigidBody::SetAcceleration(float acceleration)
{
	m_acceleration = acceleration;
}

/******************************************************************************/
/*!
\brief - Get Acceleration

\return m_acceleration
*/
/******************************************************************************/
float RigidBody::GetAcceleration(void) const
{
	return m_acceleration;
}

/******************************************************************************/
/*!
\brief - Set body's speed

\param speed
*/
/******************************************************************************/
void RigidBody::SetSpeed(const vec3& speed)
{
	m_speed = speed;
}

/******************************************************************************/
/*!
\brief - Get speed

\return m_speed
*/
/******************************************************************************/
vec3 RigidBody::GetSpeed(void) const
{
	return m_speed;
}

/******************************************************************************/
/*!
\brief - Set body's velocity

\param velocity
*/
/******************************************************************************/
void RigidBody::SetVelocity(const vec3& velocity)
{
	m_velocity = velocity;
}

/******************************************************************************/
/*!
\brief - Get velocity

\return m_velocity
*/
/******************************************************************************/
vec3 RigidBody::GetVelocity(void) const
{
	return m_velocity;
}

/******************************************************************************/
/*!
\brief - Clear all velocity and speed from body
*/
/******************************************************************************/
void RigidBody::ClearVelocity(void)
{
	m_speed = vec3();
	m_velocity = vec3();
	m_direction = 0;
}

/******************************************************************************/
/*!
\brief - Set body's scale (! Not sprite's scale !)

\param scale
*/
/******************************************************************************/
void RigidBody::SetScale(const vec3& scale)
{
	m_scale = scale;
}

/******************************************************************************/
/*!
\brief - Get body's scale (! Not sprite's scale !)

\return m_velocity
*/
/******************************************************************************/
vec3 RigidBody::GetScale(void) const
{
	return m_scale;
}

/******************************************************************************/
/*!
\brief - Set direction

\param direction
*/
/******************************************************************************/
void RigidBody::SetDirectionAngle(float direction)
{
	m_direction = direction;
}

/******************************************************************************/
/*!
\brief - Get Direction Angle

\return m_direction
*/
/******************************************************************************/
float RigidBody::GetDirectionAngle(void) const
{
	return m_direction;
}

/******************************************************************************/
/*!
\brief - Set position

\param position - position just before collided
*/
/******************************************************************************/
void RigidBody::SetLastPosition(const vec3& position)
{
	m_lastPos = position;
}

/******************************************************************************/
/*!
\brief - Get position just before the collision

\return m_lastPos
*/
/******************************************************************************/
vec3 RigidBody::GetLastPosition(void) const
{
	return m_lastPos;
}

/******************************************************************************/
/*!
\brief - Set force

\param force - combine velocity speed
*/
/******************************************************************************/
void RigidBody::SetForce(const vec3& force)
{
	vec3 get_force = force;
	m_velocity = get_force;
	m_speed = get_force.Absolute();
}

/******************************************************************************/
/*!
\brief - Check if body got either collided or not

\return m_isCollided
*/
/******************************************************************************/
bool RigidBody::IsCollided(void) const
{
	return m_isCollided;
}

/******************************************************************************/
/*!
\brief - Set collided status

\param collided
*/
/******************************************************************************/
void RigidBody::CheckCollided(bool collided)
{
	m_isCollided = collided;
}

/******************************************************************************/
/*!
\brief - Set friction

\param friction
*/
/******************************************************************************/
void RigidBody::SetFriction(float friction)
{
	m_friction = friction;
}

/******************************************************************************/
/*!
\brief - Get friction

\return m_friction
*/
/******************************************************************************/
float RigidBody::GetFriction(void) const
{
	return m_friction;
}

/******************************************************************************/
/*!
\brief - Set body's shape

\param shape - body's shape
*/
/******************************************************************************/
void RigidBody::SetShape(Shape shape)
{
	m_shape = shape;
}

/******************************************************************************/
/*!
\brief - Get body's shape

\return m_shape - body's shape
*/
/******************************************************************************/
Shape RigidBody::GetShape(void) const
{
	return m_shape;
}