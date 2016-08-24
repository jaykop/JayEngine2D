/******************************************************************************/
/*!
\file   Particle.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/27(yy/mm/dd)

\description
Contains Particle and Emitter's class and members

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <vector>

#include "../Sprite/Sprite.h"

//! Particle rendering type
enum ParticleMode{ NORMAL, FIRE, EXPLOSION, SNOW };

class Emitter;

//! Particle class
class Particle : public Sprite
{
public:

	Particle(Emitter* parent = 0, int index = 0);
	virtual ~Particle(void);
	int m_index;
	float m_life;
	float m_fade;
	vec3 m_velocity;
	vec3 m_speed;
	mat44 m_mvp;
	Emitter *m_parent;

private:
	
};

//! type definition of particle list
typedef std::vector<Particle*> ParticleList;

//! Set of particles
class Emitter : public Sprite
{

public:

	Emitter(const int id = 0, ObjectManager* obm = 0);
	Emitter(Emitter& emitter);
	virtual ~Emitter(void);

	// Scale functions
	virtual void SetScale(const vec3& scale);
	virtual vec3 GetScale(void) const;

	virtual void SetProjectionType(Projt projection);

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

	// Snow mode functions
	void SetSnowBoundary(const vec3& start, const vec3& end);
	const vec3& GetSnowStartingPoint(void) const;
	const vec3& GetSnowEndingPoint(void) const;

	void ActivateRotate(bool spin);
	bool GetRotateToggle(void) const;

	// Explosion toggle
	void ActivateExplosion(bool toggle);
	bool GetExplosionToggle(void) const;

	// Random scale functions
	void SetRandomScaleRange(const vec2& range);
	const vec2& SetRandomScaleRange(void) const;
	void ActivateRandomScale(bool toggle);
	bool GetRandomScaleToggle(void) const;

	// Get Particle container
	ParticleList& GetParticleContainer(void);

	//GLfloat *m_particle_buffer_data;

private:

	// Particle container
	ParticleList ParticleContainer;

	// Emitter info
	int m_quantity;
	float m_boundary;
	float m_emitterSpd;
	vec3 m_emitterScl;
	vec3 m_emitterDir;
	vec3 m_edgeColor;
	ParticleMode m_emitterMode;

	vec3 m_snowStart;
	vec3 m_snowEnd;
	vec2 m_rangeScl;

	bool m_spin;
	bool m_explosion;
	bool m_refreshing;
	bool m_randomScl;
};

#endif //_PARTICLE_H_
