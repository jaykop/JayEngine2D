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

#include <vector>
#include <algorithm>

#include "Particle.h"

Particle::Particle()
{

}

Particle::~Particle()
{

}

Emitter::Emitter()
: m_MaxParticles(1000)
{
	// m_texture->LoadTexture("Resource/Texture/particle.png");
}

Emitter::~Emitter()
{

}

int Emitter::FindUnusedParticle(void)
{
	for (int i = LastUsedParticle; i < 1000; ++i)
	if (ParticlesContainer[i].life < 0){
		LastUsedParticle = i;
		return i;
	}

	for (int i = 0; i < 1000; ++i)
	if (ParticlesContainer[i].life < 0){
		LastUsedParticle = i;
		return i;
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

Particle& Emitter::GetParticle(const int index)
{
	return ParticlesContainer[index];
}