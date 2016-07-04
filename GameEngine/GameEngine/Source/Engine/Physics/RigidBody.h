/******************************************************************************/
/*!
\file   RigidBody.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains RigidBody's class and members
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include "../Utilities/Math/MathUtils.h"

class Sprite;

//! Rigidbody' shape
enum Shape { BALL, BOX };

//! class RigidBody
class RigidBody{

public:
	RigidBody();
	~RigidBody();

	//Manage Body' scale 
	void SetScale(const vec3& scale);
	vec3 GetScale(void) const;

	//Manage Body's direction to move
	void SetDirectionAngle(float m_direction);
	float GetDirectionAngle(void) const;

	//Manager body's physics info
	void SetSpeed(const vec3& speed);
	vec3 GetSpeed(void) const;

	void SetVelocity(const vec3& velocity);
	vec3 GetVelocity(void) const;
	void ClearVelocity(void);

	void SetForce(const vec3& force);

	void SetLastPosition(const vec3& position);
	vec3 GetLastPosition(void) const;

	//Todo: What would I do???
	void SetAcceleration(float acceleration);
	float GetAcceleration(void) const;

	// Body's shape type
	void SetShape(Shape type);
	Shape GetShape(void) const;

	//Todo: do with mass
	// void SetMass(float mass);
	// float GetMass(void) const;

	//Manage Body's status
	void ActivateMove(bool move);
	bool GetMoveToggle(void) const;

	void ActivateCollider(bool active);
	bool GetColliderToggle(void) const;

	void  SetFriction(float friction);
	float GetFriction(void) const;

	// Manage Collision partner
	void CheckCollided(bool collided);
	void SetCollisionWith(Sprite* partner);

	bool IsCollided(void) const;
	bool IsCollisionWith(Sprite* partner);
	Sprite* GetCollisionWith(void) const;

private:

	//Todo: do with mass
	//float m_mass;
	float m_direction;
	float m_acceleration;
	float m_friction;

	vec3 m_lastPos;
	vec3 m_scale;
	vec3 m_speed;
	vec3 m_velocity;

	bool m_collider;
	bool m_move;
	bool m_isCollided;
	Sprite* m_with;

	Shape m_shape;
};

#endif // _RIGIDBODY_H_