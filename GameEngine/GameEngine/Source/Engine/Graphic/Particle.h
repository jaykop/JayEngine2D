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

#include "Sprite.h"

class Particle : public Sprite
{
public:

	Particle(void);
	virtual ~Particle(void);

	float life;
	float speed;

private:

};


class Emitter : public Sprite
{

public:

	Emitter(void);
	~Emitter(void);

	int FindUsedParticle(void);
	void SortParticles(void);

private:

	int m_MaxParticles;
	int LastUsedParticle;
	Particle ParticlesContainer[1000];
	
};

#endif //_PARTICLE_H_
