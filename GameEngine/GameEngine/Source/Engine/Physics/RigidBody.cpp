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
RigidBody::RigidBody(Sprite* owner)
:m_move(true), m_collider(true), m_isCollided(false),
m_speed(vec3()), m_velocity(vec3()), m_lastPos(vec3()),
m_direction(0), m_scale(0), m_acceleration(0), m_friction(0),
m_shape(BOX), m_mass(1.f), m_owner(owner),
m_verts(Vertices()), m_edges(Edges())
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

	if (m_speed.x < 0)
		m_speed.x = -m_speed.x;

	if (m_speed.y < 0)
		m_speed.y = -m_speed.y;
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

/******************************************************************************/
/*!
\brief - Set opponent's address

\param partner - opponent's address
*/
/******************************************************************************/
void RigidBody::SetCollisionWith(Sprite* partner)
{
	m_with = partner;
}

/******************************************************************************/
/*!
\brief - Check if specific sprite's been collided to 

\param partner - opponent's address
\return bool
*/
/******************************************************************************/
bool RigidBody::IsCollisionWith(Sprite* partner)
{
	// If parameter's address is same to saved m_with
	if (m_with == partner)
		return true;

	return false;
}

/******************************************************************************/
/*!
\brief - Get collided one's address

\return m_with - collided one's address
*/
/******************************************************************************/
Sprite* RigidBody::GetCollisionWith(void) const
{
	return m_with;
}

/******************************************************************************/
/*!
\brief - Set body's mass

\param mass - body's mass
*/
/******************************************************************************/
void RigidBody::SetMass(float mass)
{
	if (mass <= 1.f)
		m_mass = 1.f;
	
	else
		m_mass = mass;
}

/******************************************************************************/
/*!
\brief - Get body's mass

\return m_mass - body's mass
*/
/******************************************************************************/
float RigidBody::GetMass(void) const
{
	return m_mass;
}

/******************************************************************************/
/*!
\brief - Get sprite's 4 vertices

    vert[1]     vert[2]
      *----------*
      |		     |
      |	  spt    |
	  |		     |
	  *----------*
	vert[0]     vert[3]

\return m_verts
*/
/******************************************************************************/
Vertices RigidBody::GetVertices(void)
{
	if (m_shape == BOX)
	{
		// This scale is body's scale, not sprite's.
		m_verts[0] = vec3(m_owner->GetPosition().x - m_scale.x / 2, m_owner->GetPosition().y - m_scale.y / 2, m_owner->GetPosition().z);
		m_verts[1] = vec3(m_owner->GetPosition().x - m_scale.x / 2, m_owner->GetPosition().y + m_scale.y / 2, m_owner->GetPosition().z);
		m_verts[2] = vec3(m_owner->GetPosition().x + m_scale.x / 2, m_owner->GetPosition().y + m_scale.y / 2, m_owner->GetPosition().z);
		m_verts[3] = vec3(m_owner->GetPosition().x + m_scale.x / 2, m_owner->GetPosition().y - m_scale.y / 2, m_owner->GetPosition().z);

		//If sprite is rotated...
		if (m_owner->GetRotation())
		{
			m_verts[0] = m_verts[0].Rotation(m_owner->GetRotation(), m_owner->GetPosition());
			m_verts[1] = m_verts[1].Rotation(m_owner->GetRotation(), m_owner->GetPosition());
			m_verts[2] = m_verts[2].Rotation(m_owner->GetRotation(), m_owner->GetPosition());
			m_verts[3] = m_verts[3].Rotation(m_owner->GetRotation(), m_owner->GetPosition());
		}
	}
	return m_verts;
}

/******************************************************************************/
/*!
\brief - Get sprite's 4 edges

				edge[1]
			* ---------- *
			|			 |
	edge[0]	|	 spt	 |	edge[2]
			|			 |
			* ---------- *
				edge[3]


\return m_edges
*/
/******************************************************************************/
Edges RigidBody::GetEdges(void)
{
	if (m_shape == BOX)
	{
		// Init vertices
		GetVertices();

		//				edge[1]
		//			* ---------- *
		//			|			 |
		//	edge[0]	|	 spt	 |	edge[2]
		//			|			 |
		//			* ---------- *
		//				edge[3]

		// Set 4 edges
		m_edges[0] = m_verts[1] - m_verts[0];
		m_edges[1] = m_verts[2] - m_verts[1];
		m_edges[2] = m_verts[3] - m_verts[2];
		m_edges[3] = m_verts[0] - m_verts[3];
	}
	return m_edges;
}

/******************************************************************************/
/*!
\brief - Get body's owner sprite

\return m_owner
*/
/******************************************************************************/
Sprite* RigidBody::GetOwnerSprite(void) const
{
	return m_owner;
}