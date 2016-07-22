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
#include "../Utilities/Random.h"
#include "../Physics//RigidBody.h"

Particle::Particle(Emitter* parent, int index)
:m_parent(parent), m_index(index), m_life(0.f),
m_dirAngle(0), velocity(vec3()), m_speed(0),
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
: m_boundary(5.f), m_emitterScl(vec3(1.f,1.f)),
m_emitterDir(vec3(-1, 1)), m_emitterSpd(0.5f),
m_emitterMode(NORMAL), m_quantity(0)
{
	SetID(id);
	SetType(PARTICLE);
	SetObjectManager(obm);
	SetColor(vec4(0.5f, 0.5f, 0.5f, 1.f));

	// Bind pointer to mother emitter
	for (int index = 0; index < MaxParticle; ++index)
		ParticlesContainer[index].m_parent = this;
}

Emitter::~Emitter()
{
	// Delete mother texture
	delete GetTexture();
}

// Scale functions
void Emitter::SetScale(const vec3& scale)
{
	// init total information
	m_emitterScl = scale;

	// Refresh all particles
	for (int i = 0; i < MaxParticle; ++i)
	{
		ParticlesContainer[i].SetScale(m_emitterScl);
	}
}

vec3 Emitter::GetScale(void) const
{
	return m_emitterScl;
}

// Mode functions
void Emitter::SetMode(ParticleMode mode)
{
	m_emitterMode = mode;
}

ParticleMode Emitter::GetMode(void) const
{
	return m_emitterMode;
}

// Quantity of particle of emitter
int Emitter::GetNumOfParticle(void) const
{
	return m_quantity;
}

// speed function
void Emitter::SetSpeed(float speed)
{
	if (speed < 0) speed = -speed;
	m_emitterSpd = speed;
}

float Emitter::GetSpeed(void) const
{
	return m_emitterSpd;
}

// direction functions
void Emitter::SetDirection(const vec3& dir)
{
	m_emitterDir = dir;
	m_emitterDir.Normalize();
}

vec3 Emitter::GetDirection(void) const
{
	return m_emitterDir;
}

// boundary functions
void Emitter::SetBoundary(float range)
{
	m_boundary = range;
}

float Emitter::GetBoundary(void) const
{
	return m_boundary;
}

void Emitter::Update(const int i)
{
	// Render usual particle
	if (ParticlesContainer[i].m_life > 0.f)
		Render(i);

	// refresh particle's info
	else
		Refresh(i);
}

void Emitter::Render(const int i)
{
	SetColor(vec4(
		ParticlesContainer[i].GetColor().x,
		ParticlesContainer[i].GetColor().y,
		ParticlesContainer[i].GetColor().z,
		ParticlesContainer[i].m_life));

	vec3 new_force =
		ParticlesContainer[i].m_speed * vec3(
		cosf(Math::DegToRad(ParticlesContainer[i].m_dirAngle)),
		sinf(Math::DegToRad(ParticlesContainer[i].m_dirAngle)), 0);

	//Update position by velocity and direction
	ParticlesContainer[i].SetPosition(vec3(
		ParticlesContainer[i].GetPosition().x + new_force.x,
		ParticlesContainer[i].GetPosition().y + new_force.y,
		ParticlesContainer[i].GetPosition().z));

	ParticlesContainer[i].m_life -= ParticlesContainer[i].m_slow;
}

void Emitter::Refresh(const int i)
{
	// Reset the original position
	ParticlesContainer[i].SetPosition(GetPosition());

	// Set new velocity
	ParticlesContainer[i].velocity = vec3(
		Random::GetInstance().GetRandomFloat(-1.f, 1.f),
		Random::GetInstance().GetRandomFloat(-1.f, 1.f));

	// Update particle's speed and velocity
	ParticlesContainer[i].velocity
		= ParticlesContainer[i].velocity.Normalize();

	// Set direction angle
	ParticlesContainer[i].m_dirAngle = Math::RadToDeg(acosf((ParticlesContainer[i].velocity + m_emitterDir).DotProduct(vec3(1, 0, 0))));

	// Set speed
	ParticlesContainer[i].m_speed = 
		Random::GetInstance().GetRandomFloat(0.f, 1.f) * m_emitterSpd;

	// Reset life
	ParticlesContainer[i].m_life = 1.f;

	// Reset vanishing speed
	ParticlesContainer[i].m_slow = (Random::GetInstance().GetRandomFloat(0.169f, 1.f) * ParticlesContainer[i].m_speed) / m_boundary;
}