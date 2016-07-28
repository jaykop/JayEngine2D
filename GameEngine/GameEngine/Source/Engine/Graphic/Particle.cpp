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
m_slow(0.f), m_speed(vec3())
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
: m_boundary(5.f), m_emitterScl(vec3(1.f, 1.f)),
m_emitterDir(vec3(0, 0)), m_emitterSpd(1.f),
m_emitterMode(NORMAL), m_quantity(0)
{
	SetID(id);
	SetType(PARTICLE);
	SetObjectManager(obm);
	SetColor(vec4(1.f, 1.f, 1.f, 1.f));
}

Emitter::~Emitter()
{
	//delete[] m_particle_buffer_data;

	// Delete mother texture
	delete GetTexture();

	for (auto it = ParticleContainer.begin();
		it != ParticleContainer.end(); ++it)
			delete (*it);

	ParticleContainer.clear();
}

// Scale functions
void Emitter::SetScale(const vec3& scale)
{
	// init total information
	m_emitterScl = scale;

	// Refresh all particles
	for (auto it = ParticleContainer.begin();
		it != ParticleContainer.end(); ++it)
			(*it)->SetScale(m_emitterScl);
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

void Emitter::SetNumOfParticle(int quantity)
{
	m_quantity = quantity;
	for (int index = 0; index < quantity; ++index)
	{
		Particle* new_particle = new Particle(this, index);
		ParticleContainer.push_back(new_particle);
	}

	//m_particle_buffer_data = new GLfloat[20 * m_quantity];
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

void Emitter::Update(Particle* particle)
{
	// Render usual particle
	if (particle->m_life > 0.f)
		Render(particle);

	// refresh particle's info
	else
		Refresh(particle);
}

void Emitter::Render(Particle* particle)
{
	// Set new force (offset)
	//particle->m_speed += m_emitterSpd;

	vec3 new_force = vec3(
		particle->m_speed.x * particle->m_velocity.x,
		particle->m_speed.y * particle->m_velocity.y)
		* 0.169f + m_emitterDir.Normalize();

	// Update position by velocity and direction
	particle->SetPosition(vec3(
		particle->GetPosition().x + new_force.x ,
		particle->GetPosition().y + new_force.y ,
		particle->GetPosition().z));

	float new_slow = particle->m_slow * new_force.Length() / m_boundary;

	// Reduce particle's life
	particle->m_life -= new_slow;

	// Set color
	if (m_edgeColor.Length())
	{
		vec3 colorOffset = m_edgeColor - GetColor();

		particle->SetColor(vec4(
			particle->GetColor() + colorOffset * new_slow,
			particle->m_life));
	}
}

void Emitter::Refresh(Particle* particle)
{
	// Reset the original position
	particle->SetPosition(GetPosition());

	// Reset life
	particle->m_life = 1.f;

	// Reset color
	particle->SetColor(vec4(
		GetColor().x,
		GetColor().y,
		GetColor().z,
		particle->m_life));

	// Set Velocity;
	particle->m_velocity = vec3(
		Random::GetInstance().GetRandomFloat(-1.f, 1.f),
		Random::GetInstance().GetRandomFloat(-1.f, 1.f));
	particle->m_velocity = particle->m_velocity.Normalize();

	// Set speed
	particle->m_speed =
		m_emitterSpd * vec3(
		Random::GetInstance().GetRandomFloat(0.f, 1.f),
		Random::GetInstance().GetRandomFloat(0.f, 1.f));

	// Reset vanishing speed
	particle->m_slow = Random::GetInstance().GetRandomFloat(0.169f, 1.f);
}

ParticleList& Emitter::GetParticleContainer(void)
{
	return ParticleContainer;
}

void Emitter::SetColors(vec3 center, vec3 edge)
{
	SetColor(center);
	m_edgeColor = edge;
}