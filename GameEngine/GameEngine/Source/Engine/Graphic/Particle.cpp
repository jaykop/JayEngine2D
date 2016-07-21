/******************************************************************************/
/*!
\file   Particle.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Particle's class and member functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Texture.h"
#include "Particle.h"
#include "../Physics//RigidBody.h"

Particle::Particle(Emitter* parent, int index)
:m_parent(parent), m_index(index), m_life(0.f),
m_dirAngle(0), velocity(vec3()), m_speed(vec3()),
m_slow(0)
{
	SetType(PARTICLE);
	SetColor(vec4(1.f, 1.f, 1.f, 1.f));
	SetRigidBody();
	GetRigidBody()->ActivateCollider(false);
}

Particle::~Particle(void)
{
	m_parent = 0;
}

Emitter::Emitter(const int id, ObjectManager* obm)
: LastUsedParticle(0)
{
	SetID(id);
	SetType(PARTICLE);
	SetObjectManager(obm);
	SetColor(vec4(0.5f, 0.5f, 0.5f, 1.f));

	for (int index = 0; index < MaxParticle; ++index)
		ParticlesContainer[index].m_parent = this;
}

Emitter::~Emitter()
{
	//ParticlesContainer.clear();
	delete GetTexture();
}

int Emitter::FindUnusedParticle(void)
{
	//for (int i = LastUsedParticle; i != MaxParticle; ++i)
	//if (ParticlesContainer[i].m_life < 0)
	//{
	//	LastUsedParticle = i;
	//	return i;
	//}

	//for (int i = 0; i<LastUsedParticle; ++i){
	//	if (ParticlesContainer[i].m_life < 0){
	//		LastUsedParticle = i;
	//		return i;
	//	}
	//}

	return 0;
}

void Emitter::SortParticles(void)
{
	//std::sort(&ParticlesContainer[0], &ParticlesContainer[MaxParticle]);
}

//int Emitter::GetNumOfParticle(void) const
//{
//	return m_MaxParticles;
//}
//
//void Emitter::SetNumOfParticle(int numOfParticle)
//{
//	m_MaxParticles = numOfParticle;
//}
//
//ParticleList& Emitter::GetParticleContainer(void)
//{
//	return ParticlesContainer;
//}

void Emitter::PositionUpdate(void)
{
	//for (int i = 0; i < MaxParticle; ++i)
	//{
	//	ParticlesContainer[i].SetPosition(
	//		ParticlesContainer[i].GetPosition() 
	//		+ ParticlesContainer[i].velocity 
	//		* ParticlesContainer[i].m_speed);
	//}
}