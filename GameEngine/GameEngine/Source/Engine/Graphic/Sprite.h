/******************************************************************************/
/*!
\file   Sprite.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Sprite's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <map>
#include "Texture.h"
#include "../Utilities/Time.h"
#include "../ObjectManager/Object/Object.h"

//! Sprite's prohection type
enum Projt { PERSPECTIVE, ORTHOGONAL };

class RigidBody;

//! Sprite class
class Sprite : public Object
{

public:
	
	//Constructor and destructor
	Sprite(const int id = 0, Type type = SPRITE, ObjectManager* obm = 0);
	virtual ~Sprite();

	// Transforming functions
	void SetPosition(const vec3& position);
	void SetScale(const vec3& scale);
	void SetRotation(float degree);
	
	vec3 GetPosition(void) const;
	vec3 GetScale(void) const;
	float GetRotation(void) const;

	// Color and texture setting
	void SetColor(const vec4& color);
	vec4 GetColor(void) const;
	
	// Physics setting
	void BindRigidBody(void);
	RigidBody* GetRigidBody(void) const;
	void RemoveRigidBody(void);
	bool HasRigidBody(void) const;

	// Sprite's texture 
	void SetTexture(Texture* texture);
	Texture* GetTexture(void) const;

	// Projection type
	void SetProjectionType(Projt projection);
	Projt GetProjectionType(void) const;

	// Animation functions
	// For users
	void PlayAnimation(bool play);				// Set play toggle
	bool GetPlayToggle(void) const;				// Get play toggle
	void SetAnimation(int frame, float speed);	// Set animation
	void FixAnimation(int fixed_frame);			// Set fixed scene
	int GetAnimationFrame(void) const;			// Get the nimber of scene  
	float GetAnimationSpeed(void) const;		// Get the animation speed

	// For developers
	float GetDividedSpeed(void) const;	// Get divided speed 
	float GetDividedFrame(void) const;	// Get divided scene 
	float GetCurrentScene(void) const;	// Get current animation scene 
	void SetCurrentScene(float currnet);// Set curremt scene

	Timer& GetTimer(void);			// Frame timer 

private:

	// Drawing Info
	// Math info
	vec3 m_position;
	vec3 m_scale;
	vec4 m_color;
	float m_degree;

	// Type Info
	Projt m_prjt;

	// Texture Info
	bool  ani_play;
	Timer m_timer;
	float ani_frame;
	float ani_speed;
	float m_curScene;
	Texture* m_texture;

	// Physics Info
	bool m_HasBody;
	RigidBody* m_body;

};

#endif // _SPRITE_H_