/******************************************************************************/
/*!
\file   Effect.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/08/24(yy/mm/dd)

\description
Contains Effect's class and member

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "../../Utilities/Math/MathUtils.h"

enum EffectType{NONE, WAVE, BLUR, SOBEL, MANIPULATION};

class Sprite;

class Effect
{

public:

	Effect(Sprite* owner);
	~Effect();

	//! Sprite owner
	Sprite* GetOwnerSprite(void) const;

	// Effect mode manager
	void SetMode(EffectType mode);
	EffectType GetMode(void) const;

	// Wave effect function
	void ActivateWaveToggle(bool toggle);
	bool GetWaveToggle(void) const;
	void SetWavePhase(vec2 phase);
	const vec2& GetWavePhase(void) const;

	// Blur effect function
	void ActivateBlurToggle(bool toggle);
	bool GetBlurToggle(void) const;
	void SetBlurAmount(float amount);
	float GetBlurAmount(void) const;

	// Sobel effect function
	void ActivateSobelToggle(bool toggle);
	bool GetSobelToggle(void) const;
	void SetSobelAmount(float amount);
	float GetSobelAmount(void) const;

	// Manipulation effect function
	void ActivateManipToggle(bool toggle);
	bool GetManipToggle(void) const;

private:

	// Effect type
	EffectType m_mode;

	// Wave info
	bool m_wave;
	vec2 m_phase;

	// Blur info..
	bool m_blur;
	float m_blurAmount;

	// Sobel info..
	bool m_sobel;
	float m_sobelAmount;

	// Manipulation Info..
	bool m_manip;

	//! Sprite owner
	Sprite* m_owner;

};

#endif // _EFFECT_H_