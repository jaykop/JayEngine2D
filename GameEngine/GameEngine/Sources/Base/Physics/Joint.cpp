#include "Joint.h"
#include "RigidBody.h"
#include "../Math/Matrix/Matrix2x2.h"

typedef Matrix2x2 mat22;

void Joint::Set(RigidBody* body1, RigidBody* body2, const vec3& anchor)
{
	m_body1 = body1;
	m_body2 = body2;

	mat22 Rot1(m_body1->m_rotation);
	mat22 Rot2(m_body2->m_rotation);
	
	mat22 Rot1T = Rot1.Transpose();
	mat22 Rot2T = Rot2.Transpose();

	anchor;
}

void Joint::PreStep(float inv_dt)
{
	inv_dt;
}

void Joint::ApplyImpulse(void)
{

}