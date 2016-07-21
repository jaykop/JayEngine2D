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

#define MaxParticle 100

class Emitter;
class Particle : public Sprite
{
public:
	Particle(Emitter* parent = 0, int index = 0);
	virtual ~Particle(void);
	float m_life;
	float m_dirAngle;
	float m_slow;
	vec3 velocity, m_speed;
	int m_index;
	Emitter *m_parent;

private:
	
};

//class Particle : public Sprite
//{
//public:
//
//	Particle(Emitter* parent = 0, int index = 0);
//	virtual ~Particle(void);
//	float m_life;
//	int m_index;
//	vec3 m_speed;
//
//private:
//
//	Emitter* m_parent;
//};
//
//typedef std::vector<Particle> ParticleList;

class Emitter : public Sprite
{

public:

	Emitter(const int id = 0, ObjectManager* obm = 0);
	virtual ~Emitter(void);

	int FindUnusedParticle(void);
	void SortParticles(void);

	int GetNumOfParticle(void) const;
	void SetNumOfParticle(int numOfParticle);
	
	Particle ParticlesContainer[MaxParticle];
	int LastUsedParticle;

	void PositionUpdate(void);

	//ParticleList& GetParticleContainer(void);

private:

	//ParticleList ParticlesContainer;
	
};

#endif //_PARTICLE_H_
