/******************************************************************************/
/*!
\file   Particle.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Particle's class and member functions

All codes are written by Jaykop Jeong...
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
	m_life = 0.f;
	SetColor(vec4(GetColor(), m_life));
	SetPosition(m_parent->GetPosition());
	SetRigidBody();
	GetRigidBody()->ActivateCollider(false);
	m_speed = vec3(
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
m_emitterDir(vec3(0, 0)), m_emitterSpd(1.f), m_refreshing(true),
m_emitterMode(NORMAL), m_quantity(0), m_spin(false), m_explosion(true),
m_randomScl(false), m_rangeScl(vec2())
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
\brief - Set Random Scale's Range
\param range
*/
/******************************************************************************/
void Emitter::SetRandomScaleRange(const vec2& range)
{
	// init total information
	m_rangeScl = range;
}

/******************************************************************************/
/*!
\brief - Get Random Scale's Range
\return m_rangeScl
*/
/******************************************************************************/
const vec2& Emitter::GetRandomScaleRange(void) const
{
	return m_rangeScl;
}

/******************************************************************************/
/*!
\brief - Set Random Scale's Range
\param range
*/
/******************************************************************************/
void Emitter::ActivateRandomScale(bool toggle)
{
	m_randomScl = toggle;
}

/******************************************************************************/
/*!
\brief - Set Random Scale's Range
\param range
*/
/******************************************************************************/
bool Emitter::GetRandomScaleToggle(void) const
{
	return m_randomScl;
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
	for (auto it = ParticleContainer.begin();
		it != ParticleContainer.end(); ++it)
		(*it)->m_speed = m_emitterSpd * vec3(
		Random::GetInstance().GetRandomFloat(0.f, 1.f),
		Random::GetInstance().GetRandomFloat(0.f, 1.f));
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
const vec3& Emitter::GetDirection(void) const
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
	for (auto it = ParticleContainer.begin();
		it != ParticleContainer.end(); ++it)
		(*it)->SetColor(center);
}

/******************************************************************************/
/*!
\brief - Set snow mode's starting position boundary
\param start
\param end
*/
/******************************************************************************/
void Emitter::SetSnowBoundary(const vec3& start, const vec3& end)
{
	m_snowStart = start;
	m_snowEnd = end;

	vec3 snowStart = m_snowStart;
	vec3 snowEnd = m_snowEnd;

	for (auto it = ParticleContainer.begin();
		it != ParticleContainer.end(); ++it)
		(*it)->SetPosition(GetPosition() +
		vec3(
		Random::GetInstance().GetRandomFloat(snowStart.x, snowEnd.x),
		Random::GetInstance().GetRandomFloat(snowStart.y, snowEnd.y)));

}

/******************************************************************************/
/*!
\brief - Get snow mode's starting point of starting position
\return m_snowStart
*/
/******************************************************************************/
const vec3& Emitter::GetSnowStartingPoint(void) const
{
	return m_snowStart;
}

/******************************************************************************/
/*!
\brief - Get snow mode's ending point of starting position
\return m_snowEnd
*/
/******************************************************************************/
const vec3& Emitter::GetSnowEndingPoint(void) const
{
	return m_snowEnd;
}

/******************************************************************************/
/*!
\brief - Set emitter's projection type
\param projection
*/
/******************************************************************************/
void Emitter::SetProjectionType(Projt projection)
{
	for (auto it = ParticleContainer.begin();
		it != ParticleContainer.end(); ++it)
		(*it)->SetProjectionType(projection);
}

/******************************************************************************/
/*!
\brief - Set emitter's spin toggle
\param spin
*/
/******************************************************************************/
void Emitter::ActivateRotate(bool spin)
{
	m_spin = spin;
}

/******************************************************************************/
/*!
\brief - Get emitter's  spin toggle
\return m_spin
*/
/******************************************************************************/
bool Emitter::GetRotateToggle(void) const
{
	return m_spin;
}

/******************************************************************************/
/*!
\brief - Set emitter's explosion toggle
\param toggle
*/
/******************************************************************************/
void Emitter::ActivateExplosion(bool toggle)
{
	m_explosion = toggle;
	m_refreshing = false;
	if (m_explosion)
	{
		for (auto it = ParticleContainer.begin();
			it != ParticleContainer.end(); ++it)
			Refresh((*it));
	}
	m_refreshing = true;
}

/******************************************************************************/
/*!
\brief - Get emitter's explosion toggle
\return m_spin
*/
/******************************************************************************/
bool Emitter::GetExplosionToggle(void) const
{
	return m_explosion;
}

/******************************************************************************/
/*!
\brief - Get emitter's refreshing toggle
\return m_spin
*/
/******************************************************************************/
bool Emitter::GetRefreshingToggle(void) const
{
	return m_refreshing;
}

/******************************************************************************/
/*!
\brief - Get emitter's edgeColor
\return m_edgeColor
*/
/******************************************************************************/
const vec3& Emitter::GetEdgeColor(void) const
{
	return m_edgeColor;
}

/******************************************************************************/
/*!
\brief - Refresh each particle
\param particle
*/
/******************************************************************************/
void Emitter::Refresh(Particle* particle)
{
	// If the emitter mode is explosion,
	// there is no more refreshing precess
	if (m_explosion)
	{
		// Reset the original position
		if (m_emitterMode == FIRE)
		{
			m_emitterDir = vec3(0.f, 1.f);
			float repos_offset = 3.f/5.f;
			float new_pos = m_boundary * repos_offset;
			particle->SetPosition(GetPosition() +
				vec3(
				Random::GetInstance().GetRandomFloat(-new_pos, new_pos),
				Random::GetInstance().GetRandomFloat(-new_pos, new_pos)));
		}

		else if (m_emitterMode == SNOW)
		{
			particle->SetPosition(GetPosition() +
				vec3(
				Random::GetInstance().GetRandomFloat(m_snowStart.x, m_snowEnd.x),
				Random::GetInstance().GetRandomFloat(m_snowStart.y, m_snowEnd.y)));
		}

		else
			particle->SetPosition(GetPosition());

		// Rescale?
		if (m_randomScl)
		{
			float randomSize = Random::GetInstance().GetRandomFloat(m_rangeScl.x, m_rangeScl.y);
			particle->SetScale(vec3(randomSize,	randomSize));
		}

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
	
		if (m_emitterMode == EXPLOSION && m_refreshing)
			m_explosion = false;
	}
}
