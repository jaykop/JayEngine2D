/******************************************************************************/
/*!
\file   Sprite.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Sprite's class functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "../Text/Text.h"
#include "../Sprite/Sprite.h"
#include "../../Physics/RigidBody/RigidBody.h"
#include "../../ObjectManager/ObjectManager.h"

/******************************************************************************/
/*!
\brief - Sprite consturctor
\param id - Sprite's id

*/
/******************************************************************************/
Sprite::Sprite(const int id, ObjectManager* obm)
:m_texture(0), ani_frame(1), ani_speed(0), m_curScene(0),
m_degree(0), m_color(vec4(1.f, 1.f, 1.f, 1.f)),
m_HasBody(false), m_body(0), m_prjt(PERSPECTIVE), ani_play(false),
m_position(vec3(0.f, 0.f, 0.f)), m_scale(vec3(5.f, 5.f, 0.f)),
m_wave(false), m_phase(vec2(0, 0))
{
	SetID(id);
	SetType(SPRITE);
	SetObjectManager(obm);
}

/******************************************************************************/
/*!
\brief - Sprite's Copy Constructor
*/
/******************************************************************************/
Sprite::Sprite(Sprite& sprite)
: Object(sprite)
{
	m_position = sprite.m_position;
	m_scale = sprite.m_scale;
	m_degree = sprite.m_degree;

	m_prjt = sprite.m_prjt;
	m_color = sprite.m_color;
	m_curScene = sprite.m_curScene;
	m_texture = sprite.m_texture;
	m_timer = sprite.m_timer;
	ani_frame = sprite.ani_frame;
	ani_speed = sprite.ani_speed;
	ani_play = sprite.ani_play;

	if (m_HasBody)
	{
		sprite.SetRigidBody();
		sprite.GetRigidBody()->ActivateCollider(m_body->GetColliderToggle());
		sprite.GetRigidBody()->ActivateMove(m_body->GetMoveToggle());
		sprite.GetRigidBody()->SetAcceleration(m_body->GetAcceleration());
		sprite.GetRigidBody()->SetDirectionAngle(m_body->GetDirectionAngle());
		sprite.GetRigidBody()->SetFriction(m_body->GetFriction());
		sprite.GetRigidBody()->SetMass(m_body->GetMass());
		sprite.GetRigidBody()->SetSpeed(m_body->GetSpeed());
		sprite.GetRigidBody()->SetScale(m_body->GetScale());
		sprite.GetRigidBody()->SetShape(m_body->GetShape());
		sprite.GetRigidBody()->SetVelocity(m_body->GetVelocity());
	}
}

/******************************************************************************/
/*!
\brief - Sprite desturctor
*/
/******************************************************************************/
Sprite::~Sprite(void)
{
	if (m_HasBody)
	{
		delete m_body;
		m_body = 0;
	}

	ClearLogicList();
}

/******************************************************************************/
/*!
\brief - Set Sprite;s position
\param position - sprite's position
*/
/******************************************************************************/
void Sprite::SetPosition(const vec3& position)
{
	m_position = position;
}

/******************************************************************************/
/*!
\brief - Set Sprite;s scale
\param scale - sprite's scale
*/
/******************************************************************************/
void Sprite::SetScale(const vec3& scale)
{
	m_scale = scale;
}

/******************************************************************************/
/*!
\brief - Set Sprite;s degree
\param degree - sprite's degree
*/
/******************************************************************************/
void Sprite::SetRotation(float degree)
{
	m_degree = degree;
	if (degree > 360.f) degree -= 360.f;
}

/******************************************************************************/
/*!
\brief - Get Sprite;s position
\return m_position - sprite's position
*/
/******************************************************************************/
vec3 Sprite::GetPosition(void) const
{
	return m_position;
}

/******************************************************************************/
/*!
\brief - Get Sprite;s scale

\return m_scale - sprite's scale
*/
/******************************************************************************/
vec3 Sprite::GetScale(void) const
{
	return m_scale;
}

/******************************************************************************/
/*!
\brief - Get Sprite;s m_degree
\return m_degree - sprite's degree
*/
/******************************************************************************/
float Sprite::GetRotation(void) const
{
	return m_degree;
}

/******************************************************************************/
/*!
\brief - Set Sprite;s color
\param color - sprite's color
*/
/******************************************************************************/
void Sprite::SetColor(const vec4& color)
{
	m_color = color;
}

/******************************************************************************/
/*!
\brief - Get Sprite;s color
\return m_color - sprite's color
*/
/******************************************************************************/
vec4 Sprite::GetColor(void) const
{
	return m_color;
}

/******************************************************************************/
/*!
\brief - Bind rigid body to sprite
\param new_body
*/
/******************************************************************************/
void Sprite::SetRigidBody(void)
{
	// If sprite has no body,
	// bind new body
	if (!m_HasBody)
	{
		m_body = new RigidBody(this);
		m_body->SetScale(m_scale);
		m_HasBody = true;
	}
}

/******************************************************************************/
/*!
\brief - Get Sprite;s body
\return m_body - pointer to sprite's body
*/
/******************************************************************************/
RigidBody* Sprite::GetRigidBody(void) const
{
	if (m_HasBody)
		return m_body;

	return nullptr;
}

/******************************************************************************/
/*!
\brief - Remove rigid body from sprite
*/
/******************************************************************************/
void Sprite::RemoveRigidBody(void)
{
	if (m_body)
	{
		delete m_body;
		m_body = 0;
		m_HasBody = false;
	}
}

/******************************************************************************/
/*!
\brief - Check sprite has body or not
\return m_HasBody
*/
/******************************************************************************/
bool Sprite::HasRigidBody(void) const
{
	return m_HasBody;
}

/******************************************************************************/
/*!
\brief - Set Sprite;s Texture
\param texture - sprite's texture
*/
/******************************************************************************/
void Sprite::SetTexture(Texture* texture)
{
	m_texture = texture;
}

/******************************************************************************/
/*!
\brief - Get Sprite;s Texture
\return m_texture - sprite's texture
*/
/******************************************************************************/
Texture* Sprite::GetTexture(void) const
{
	return m_texture;
}

/******************************************************************************/
/*!
\brief - Set Sprite;s  projection type

\param projection - sprite's projection type
*/
/******************************************************************************/
void Sprite::SetProjectionType(Projt projection)
{
	m_prjt = projection;
}

/******************************************************************************/
/*!
\brief - Get Sprite;s  projection type
\return m_prjt - sprite's projection type
*/
/******************************************************************************/
Projt Sprite::GetProjectionType(void) const
{
	return m_prjt;
}

/******************************************************************************/
/*!
\brief - Set animaton information
\param frame - the number of frame to be animated
\param speed - animation's speed
*/
/******************************************************************************/
void Sprite::SetAnimation(int frame, float speed)
{
	if (frame)
	{
		ani_frame = 1.f / frame;
		m_curScene = 0;
	}
	if (speed) ani_speed = 1 / speed;
	ani_play = true;
}

/******************************************************************************/
/*!
\brief - Fix aniamtion
\param frame_number - frame number to be fixed
*/
/******************************************************************************/
void Sprite::FixAnimation(int frame_number)
{
	ani_speed = 0;
	ani_play = false;
	m_curScene = ani_frame * frame_number;
}

/******************************************************************************/
/*!
\brief - Get animation's speed
\return ani_speed - animation's speed
*/
/******************************************************************************/
float Sprite::GetAnimationSpeed(void) const
{
	return 1 / ani_speed;
}

/******************************************************************************/
/*!
\brief - Get the number of frames
\return ani_frame - the divided frames
*/
/******************************************************************************/
float Sprite::GetDividedFrame(void) const
{
	return ani_frame;
}

/******************************************************************************/
/*!
\brief - Get the number of frames
\return ani_frame - the number of frame to be animated
*/
/******************************************************************************/
int Sprite::GetAnimationFrame(void) const
{
	return static_cast<int>(1 / ani_frame);
}

/******************************************************************************/
/*!
\brief - Get current animation scene 
\return m_scene - current animation scene 
*/
/******************************************************************************/
float Sprite::GetCurrentScene(void) const
{
	return m_curScene;
}

/******************************************************************************/
/*!
\brief - Set curremt scene
\param currnet - frame to be current
*/
/******************************************************************************/
void Sprite::SetCurrentScene(float currnet)	
{
	m_curScene = currnet;
}

/******************************************************************************/
/*!
\brief - Get the number of frames
\return ani_frame - the number of frame to be animated
*/
/******************************************************************************/
Timer& Sprite::GetTimer(void)
{
	return m_timer;
}

/******************************************************************************/
/*!
\brief - Get the divided speed
\return ani_speed - the divided speed
*/
/******************************************************************************/
float Sprite::GetDividedSpeed(void) const
{
	return ani_speed;
}

/******************************************************************************/
/*!
\brief - Set play toggle
\return play - tplay toggle
*/
/******************************************************************************/
void Sprite::PlayAnimation(bool play)
{
	ani_play = play;
}

/******************************************************************************/
/*!
\brief - Get play toggle
\return ani_play - play toggle
*/
/******************************************************************************/
bool Sprite::GetPlayToggle(void) const
{
	return ani_play;
}

/******************************************************************************/
/*!
\brief - Activate wave toggle
\param toggle - wave toggle
*/
/******************************************************************************/
void Sprite::ActivateWaveToggle(bool toggle)
{
	m_wave = toggle;
}

/******************************************************************************/
/*!
\brief - Get wave toggle
\return m_wave - wave toggle
*/
/******************************************************************************/
bool Sprite::GetWaveToggle(void) const
{
	return m_wave;
}

/******************************************************************************/
/*!
\brief - Set vector2 phase
\param phase - vector phase
*/
/******************************************************************************/
void Sprite::SetWavePhase(vec2 phase)
{
	m_phase = phase;
}

/******************************************************************************/
/*!
\brief - Get phase vector
\return m_phase 
*/
/******************************************************************************/
const vec2& Sprite::GetWavePhase(void) const
{
	return m_phase;
}