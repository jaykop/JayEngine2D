/******************************************************************************/
/*!
\file   Effect.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/24(yy/mm/dd)

\description
Contains Effect's class functions

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

#include "Effect.h"

Effect::Effect(Sprite* owner)
: m_wave(false), m_phase(vec2()),
m_blur(false),
m_sobel(false),
m_manip(false)
{
	m_owner = owner;
}

Effect::~Effect()
{

}

void Effect::SetMode(EffectType mode)
{
	m_mode = mode;
}

EffectType Effect::GetMode(void) const
{
	return m_mode;
}

/******************************************************************************/
/*!
\brief - Activate wave toggle
\param toggle - wave toggle
*/
/******************************************************************************/
void Effect::ActivateWaveToggle(bool toggle)
{
	m_wave = toggle;
}

/******************************************************************************/
/*!
\brief - Get wave toggle
\return m_wave - wave toggle
*/
/******************************************************************************/
bool Effect::GetWaveToggle(void) const
{
	return m_wave;
}

/******************************************************************************/
/*!
\brief - Set vector2 phase
\param phase - vector phase
*/
/******************************************************************************/
void Effect::SetWavePhase(vec2 phase)
{
	m_phase = phase;
}

/******************************************************************************/
/*!
\brief - Get phase vector
\return m_phase
*/
/******************************************************************************/
const vec2& Effect::GetWavePhase(void) const
{
	return m_phase;
}

void Effect::ActivateBlurToggle(bool toggle)
{
	m_blur = toggle;
}

bool Effect::GetBlurToggle(void) const
{
	return m_blur;
}

void Effect::ActivateSobelToggle(bool toggle)
{
	m_sobel = toggle;
}

bool Effect::GetSobelToggle(void) const
{
	return m_sobel;
}

void Effect::ActivateManipToggle(bool toggle)
{
	m_manip = toggle;
}

bool Effect::GetManipToggle(void) const
{
	return m_manip;
}