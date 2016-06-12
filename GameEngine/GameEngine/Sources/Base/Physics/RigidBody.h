#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include "../Math/MathUtils.h"

//enum CollisionType {RECT, CIRCLE};

class Sprite;
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

	//Manage Body's status
	void ActivateMove(bool move);
	bool GetMoveToggle(void) const;

	void ActivateCollider(bool active);
	bool GetColliderToggle(void) const;

	void CheckCollided(bool collided);
	bool IsCollided(void) const;

	void  SetFriction(float friction);
	float GetFriction(void) const;

private:

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
};

#endif // _RIGIDBODY_H_