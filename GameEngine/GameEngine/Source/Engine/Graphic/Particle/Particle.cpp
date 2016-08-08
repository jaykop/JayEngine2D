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

#include "Particle.h"
#include "../../Utilities/Random.h"
#include "../../Physics//RigidBody/RigidBody.h"
#define DELTA_TIME 0.169F
/******************************************************************************/
/*!
\brief - Particle Constructor
\param parent - particle's parent emitter
\param index - particle's index number
*/
/******************************************************************************/
Particle::Particle(Emitter* parent, int index)
:m_parent(parent), m_index(index)
{
	SetType(PARTICLE);
	m_life = DELTA_TIME;
	SetColor(vec4(GetColor(), m_life));
	SetPosition(m_parent->GetPosition());
	SetRigidBody();
	GetRigidBody()->ActivateCollider(false);
	m_speed = parent->GetSpeed() * vec3(
		Random::GetInstance().GetRandomFloat(0.f, 1.f),
		Random::GetInstance().GetRandomFloat(0.f, 1.f));
	m_fade = Random::GetInstance().GetRandomFloat(DELTA_TIME, 1.f);
	m_velocity = vec3(
		Random::GetInstance().GetRandomFloat(-1.f, 1.f),
		Random::GetInstance().GetRandomFloat(-1.f, 1.f));
	m_velocity = m_velocity.Normalize();
}

/******************************************************************************/
/*!
\brief - Particle Destructor
*/
/******************************************************************************/
Particle::~Particle(void)
{
	m_parent = 0;
}

/******************************************************************************/
/*!
\brief - Emitter Constructor
\param id - Emitter's id
\param obm - Pointer to obm
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief - Emitter Copy Constructor
*/
/******************************************************************************/
Emitter::Emitter(Emitter& emitter)
: Sprite(emitter)
{
	ParticleContainer = emitter.ParticleContainer;
	m_quantity = emitter.m_quantity;
	m_boundary = emitter.m_boundary;
	m_emitterSpd = emitter.m_emitterSpd;
	m_emitterScl = emitter.m_emitterScl;
	m_emitterDir = emitter.m_emitterDir;
	m_edgeColor = emitter.m_edgeColor;
	m_emitterMode = emitter.m_emitterMode;
}

/******************************************************************************/
/*!
\brief - Emitter Destructor
*/
/******************************************************************************/
Emitter::~Emitter()
{
	//delete[] m_particle_buffer_data;

	for (auto it = ParticleContainer.begin();
		it != ParticleContainer.end(); ++it)
	{
		delete (*it);
		(*it) = 0;
	}

	ParticleContainer.clear();
	ClearLogicList();
}

/******************************************************************************/
/*!
\brief - Set all particle's scale 
\param scale
*/
/******************************************************************************/
void Emitter::SetScale(const vec3& scale)
{
	// init total information
	m_emitterScl = scale;

	// Refresh all particles
	for (auto it = ParticleContainer.begin();
		it != ParticleContainer.end(); ++it)
			(*it)->SetScale(m_emitterScl);
}

/******************************************************************************/
/*!
\brief - Get all particle's scale
\return m_emitterScl
*/
/******************************************************************************/
vec3 Emitter::GetScale(void) const
{
	return m_emitterScl;
}

/******************************************************************************/
/*!
\brief - Set emitter's render mode
\param mode 
*/
/******************************************************************************/
void Emitter::SetMode(ParticleMode mode)
{
	m_emitterMode = mode;
}

/******************************************************************************/
/*!
\brief - Get emitter's render mode
\param m_emitterMode
*/
/******************************************************************************/
ParticleMode Emitter::GetMode(void) const
{
	return m_emitterMode;
}

/******************************************************************************/
/*!
\brief - Set the Number Of Particle
\param quantity - The number of particle
*/
/******************************************************************************/
void Emitter::SetNumOfParticle(int quantity)
{
	m_quantity = quantity;
	for (int index = 0; index < quantity; ++index)
	{
		Particle* new_particle = new Particle(this, index);
		ParticleContainer.push_back(new_particle);
	}
}

/******************************************************************************/
/*!
\brief - Get the Number Of Particle
\return m_quantity - The number of particle
*/
/******************************************************************************/
int Emitter::GetNumOfParticle(void) const
{
	return m_quantity;
}

/******************************************************************************/
/*!
\brief - Set particles' render speed
\param speed 
*/
/******************************************************************************/
void Emitter::SetSpeed(float speed)
{
	if (speed < 0) speed = -speed;
	m_emitterSpd = speed;
}

/******************************************************************************/
/*!
\brief - Get particles' render speed
\return m_emitterSpd
*/
/******************************************************************************/
float Emitter::GetSpeed(void) const
{
	return m_emitterSpd;
}

/******************************************************************************/
/*!
\brief - Set emitter's main direction
\param dir
*/
/******************************************************************************/
void Emitter::SetDirection(const vec3& dir)
{
	m_emitterDir = dir;
}

/******************************************************************************/
/*!
\brief - Get emitter's main direction
\return m_emitterDir
*/
/******************************************************************************/
vec3 Emitter::GetDirection(void) const
{
	return m_emitterDir;
}

/******************************************************************************/
/*!
\brief - Set emitter's spread boundary
\param range
*/
/******************************************************************************/
void Emitter::SetBoundary(float range)
{
	m_boundary = range;
}

/******************************************************************************/
/*!
\brief - Get emitter's spread boundary
\return m_boundary
*/
/******************************************************************************/
float Emitter::GetBoundary(void) const
{
	return m_boundary;
}

/******************************************************************************/
/*!
\brief - Main update function
\param particle
*/
/******************************************************************************/
void Emitter::Update(Particle* particle)
{
	// Render usual particle
	if (particle->m_life > 0.f)
		Render(particle);

	// refresh particle's info
	else
		Refresh(particle);
}

/******************************************************************************/
/*!
\brief - Render each particle
\param particle
*/
/******************************************************************************/
void Emitter::Render(Particle* particle)
{
	// Set new force (offset)
	//particle->m_speed += m_emitterSpd;

	vec3 norm_dir = m_emitterDir.Normalize();
	vec3 new_force;
	
	if (!m_emitterDir.Length())
		new_force = vec3(
		particle->m_velocity.x * particle->m_speed.x,
		particle->m_velocity.y * particle->m_speed.y) * DELTA_TIME;

	else
		new_force = vec3(
		particle->m_speed.x * norm_dir.x + norm_dir.x,
		particle->m_speed.y * norm_dir.y + norm_dir.y) * DELTA_TIME;

	// Update position by velocity and direction
	particle->SetPosition(vec3(
		particle->GetPosition().x + new_force.x,
		particle->GetPosition().y + new_force.y,
		particle->GetPosition().z));

	// Set new fade
	float new_fade = particle->m_fade * new_force.Length() / m_boundary;

	// Reduce particle's life
	particle->m_life -= new_fade;

	// Color effect
	// Change color from inside noe to outside one
	if (m_edgeColor.Length())
	{
		vec3 colorOffset = m_edgeColor - GetColor();

		particle->SetColor(vec4(
			particle->GetColor() + colorOffset * new_fade,
			particle->m_life));
	}
}

/******************************************************************************/
/*!
\brief - Refresh each particle
\param particle
*/
/******************************************************************************/
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
	if (!m_emitterDir.Length())
	{
		particle->m_velocity = vec3(
			Random::GetInstance().GetRandomFloat(-1.f, 1.f),
			Random::GetInstance().GetRandomFloat(-1.f, 1.f));
		particle->m_velocity = particle->m_velocity.Normalize();
	}

	// Set speed
	particle->m_speed =
		m_emitterSpd * vec3(
		Random::GetInstance().GetRandomFloat(0.f, 1.f),
		Random::GetInstance().GetRandomFloat(0.f, 1.f));

	// Reset vanishing speed
	particle->m_fade = Random::GetInstance().GetRandomFloat(DELTA_TIME, 1.f);
}

/******************************************************************************/
/*!
\brief - Get emitter's particle container
\return ParticleContainer
*/
/******************************************************************************/
ParticleList& Emitter::GetParticleContainer(void)
{
	return ParticleContainer;
}

/******************************************************************************/
/*!
\brief - Set emitter's color
\param center - center color
\param edge - edge color
*/
/******************************************************************************/
void Emitter::SetColors(vec3 center, vec3 edge)
{
	SetColor(center);
	m_edgeColor = edge;
}