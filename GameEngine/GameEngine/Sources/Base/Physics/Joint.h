#ifndef _JOINT_H_
#define _JOINT_H_

#include "../Math/MathUtils.h"

class Body;

class Joint
{

public:
	Joint() :
		m_body1(0), m_body2(0), m_P(0.f, 0.f),
		m_biasFactor(0.2f), m_softness(0.0f){}

	void Set(Body* body1, Body* body2, const vec3& anchor);
	void PreStep(float inv_dt);
	void ApplyImpulse(void);

	float m_M[4];
	vec3 m_localAncho1, m_localAnchor2;
	vec3 m_r1, m_r2, m_bias, m_P;
	Body *m_body1, *m_body2;
	float m_biasFactor, m_softness;

private:

};

#endif // _JOINT_H_