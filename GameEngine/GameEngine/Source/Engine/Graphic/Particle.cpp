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
:m_parent(parent), m_index(index), m_speed(vec3())
{
}

Particle::~Particle(void)
{
	m_parent = 0;
}

Emitter::Emitter(const int id, Type type, ObjectManager* obm)
: m_MaxParticles(1), LastUsedParticle(0)
{
	SetID(id);
	SetObjectType(type);
	SetObjectManager(obm);

	for (int index = 0; index < m_MaxParticles; ++index)
		ParticlesContainer.push_back(Particle(this, index));
}

Emitter::~Emitter()
{
	ParticlesContainer.clear();
}

int Emitter::FindUnusedParticle(void)
{
	for (auto it = ParticlesContainer.begin(); it != ParticlesContainer.end(); ++it)
		if ((*it).m_life < 0){
			LastUsedParticle = (*it).m_index;
			return (*it).m_index;
	}

	for (auto it = ParticlesContainer.begin(); it != ParticlesContainer.end();)
	if ((*it).m_life < 0){
		LastUsedParticle = (*it).m_index;
		return (*it).m_index;
	}

	return 0;
}

void Emitter::SortParticles(void)
{
	//std::sort(&ParticlesContainer[0], &ParticlesContainer[1000]);
}

int Emitter::GetNumOfParticle(void) const
{
	return m_MaxParticles;
}

void Emitter::SetNumOfParticle(int numOfParticle)
{
	m_MaxParticles = numOfParticle;
}

ParticleList& Emitter::GetParticleContainer(void)
{
	return ParticlesContainer;
}