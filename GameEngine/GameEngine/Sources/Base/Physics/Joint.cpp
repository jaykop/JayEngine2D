#include "Joint.h"
#include "RigidBody.h"

void Joint::Set(Body* body1, Body* body2, const vec3& anchor)
{
	m_body1 = body1;
	m_body2 = body2;


}
void Joint::PreStep(float inv_dt)
{}
void Joint::ApplyImpulse(void)
{}