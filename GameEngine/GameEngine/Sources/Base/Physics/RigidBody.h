#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include "../Math/MathUtils.h"

class RigidBody{

public:
	RigidBody();
	~RigidBody();

	void Set(const vec3& width, float mass);
	void AddForce(const vec3& force);

	vec3 m_position;
	vec3 m_velocity;
	vec3 m_force;
	vec3 m_width;

	float m_rotation;
	float m_angularVelocity;
	float m_torque;
	float m_friction;
	float m_mass, m_invMass;
	float m_l, m_invl;

private:

};

#endif // _RIGIDBODY_H_