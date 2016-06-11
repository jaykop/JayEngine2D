#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include "../Math/MathUtils.h"

//enum CollisionType {RECT, CIRCLE};

class Sprite;
class RigidBody{

public:
	RigidBody();
	~RigidBody();

	void SetScale(const vec3& scale);
	vec3 GetScale(void) const;

	void SetRotation(float degree);
	float GetRotation(void) const;

	void SetStatus(bool status);
	bool GetStatus(void) const;

	void SetSpeed(const vec3& speed);
	vec3 GetSpeed(void) const;

	void SetVelocity(const vec3& velocity);
	vec3 GetVelocity(void) const;
	void ClearVelocity(void);

	void SetAcceleration(float acceleration);
	float GetAcceleration(void) const;

	void ActivateCollider(bool active);

private:

	float m_degree;
	float m_acceleration;

	vec3 m_scale;
	vec3 m_speed;
	vec3 m_velocity;

	bool m_active;
	bool m_collide;
	bool m_fixed;
};

#endif // _RIGIDBODY_H_