/******************************************************************************/
/*!
\file   Particle.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/27(yy/mm/dd)

\description
Contains Particle and Emitter's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <vector>
#include <algorithm>
#include "Sprite.h"

class Emitter;
class Particle : public Sprite
{
public:

	Particle(Emitter* parent = 0, int index = 0);
	virtual ~Particle(void);
	float m_life;
	int m_index;
	vec3 m_speed;

private:

	Emitter* m_parent;
};

typedef std::vector<Particle> ParticleList;

class Emitter : public Sprite
{

public:

	Emitter(const int id = 0, ObjectManager* obm = 0);
	virtual ~Emitter(void);

	int FindUnusedParticle(void);
	void SortParticles(void);

	int GetNumOfParticle(void) const;
	void SetNumOfParticle(int numOfParticle);

	ParticleList& GetParticleContainer(void);

private:

	int m_MaxParticles;
	int LastUsedParticle;
	ParticleList ParticlesContainer;
	
};

#endif //_PARTICLE_H_
