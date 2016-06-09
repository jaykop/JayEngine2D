#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include "../Math/MathUtils.h"

//enum CollisionType {RECT, CIRCLE};

class RigidBody{

public:
	RigidBody();
	~RigidBody();

	//void Set(const vec3& width, float mass);
	//void AddForce(const vec3& force);
	void WorkCollide();
	void ActivateCollider(bool active);

	void SetStatus(bool status);
	bool GetStatus(void) const;

	vec3 m_position;
	vec3 m_scale;
	vec3 m_velocity;
	vec3 m_force;
	vec3 m_width;

	//float m_rotation;
	//float m_angularVelocity;
	//float m_torque;
	//float m_friction;
	//float m_mass, m_invMass;
	//float m_inertia, m_invlnertia;

	bool m_active;
	bool m_collide;
	bool m_fixed;

private:

};

#endif // _RIGIDBODY_H_