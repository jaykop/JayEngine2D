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
#include <stdlib.h>
#include <vector>

#include "Sprite.h"

enum ParticleMode{ NORMAL, FIRE, SMOKE, EXPLOSION };

class Emitter;

//! Particle class
class Particle : public Sprite
{
public:
	Particle(Emitter* parent = 0, int index = 0);
	virtual ~Particle(void);
	int m_index;
	float m_life;
	float m_slow;
	vec3 m_velocity;
	vec3 m_speed;
	mat44 m_mvp;
	Emitter *m_parent;

private:
	
};

typedef std::vector<Particle*> ParticleList;

//! Set of particles
class Emitter : public Sprite
{

public:

	Emitter(const int id = 0, ObjectManager* obm = 0);
	virtual ~Emitter(void);

	// Scale functions
	virtual void SetScale(const vec3& scale);
	virtual vec3 GetScale(void) const;

	void SetColors(vec3 center, vec3 edge = vec3());

	// Mode functions
	void SetMode(ParticleMode mode);
	ParticleMode GetMode(void) const;

	// Quantity of particle of emitter
	void SetNumOfParticle(int quantity);
	int GetNumOfParticle(void) const;
	
	// direction functions
	void SetDirection(const vec3& dir);
	vec3 GetDirection(void) const;

	// speed function
	void SetSpeed(float speed);
	float GetSpeed(void) const;

	// boundary functions
	void SetBoundary(float range);
	float GetBoundary(void) const;

	// Renderer functions
	void Update(Particle* particle);
	void Render(Particle* particle);
	void Refresh(Particle* particle);

	//GLfloat *m_particle_buffer_data;

	ParticleList& GetParticleContainer(void);

private:

	ParticleList ParticleContainer;

	int m_quantity;
	float m_boundary;
	float m_emitterSpd;

	vec3 m_emitterScl;
	vec3 m_emitterDir;
	ParticleMode m_emitterMode;
	vec3 m_edgeColor;

};

#endif //_PARTICLE_H_
