#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include "../Math/MathUtils.h"

//enum CollisionType {RECT, CIRCLE};

class RigidBody{

public:
	RigidBody();
	~RigidBody();

	void SetPosition(vec3& position);
	vec3 GetPosition(void) const;

	void SetScale(vec3& scale);
	vec3 GetScale(void) const;

	void SetRotation(float degree);
	float GetRotation(void) const;

	void WorkCollide();
	void ActivateCollider(bool active);

	void SetStatus(bool status);
	bool GetStatus(void) const;

	void SetVertices(void);
	vec3 GetVertice(int index) const;

	void SetVelocity(vec3& velocity);
	vec3 GetVelocity(void) const;
	void WorkVelocity(void);
	void ClearVelocity(void);

	vec3 m_position;
	vec3 m_scale;

private:

	float m_degree;


	vec3 m_velocity;
	vec3 m_force;
	vec3 m_width;

	vec3 m_vertice[4];

	bool m_active;
	bool m_collide;
	bool m_fixed;

};

#endif // _RIGIDBODY_H_