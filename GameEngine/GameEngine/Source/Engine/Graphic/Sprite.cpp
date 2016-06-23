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

#include "Text.h"
#include "Sprite.h"
#include "../Physics/RigidBody.h"
#include "../StateManager/GameStateManager/GameStateManager.h"

/******************************************************************************/
/*!
\brief - Sprite consturctor

\param id - Sprite's id

*/
/******************************************************************************/
Sprite::Sprite(const int id, Type type)

{
	m_position = vec3(0.f, 0.f, 0.f);
	m_scale = vec3(5.f, 5.f, 0.f);
	m_degree = 0;
	m_color = vec4(1.f, 1.f, 1.f, 1.f);
	m_HasBody = false;
	m_body = 0;
	m_id = id;
	m_shape = RECTANGLE;
	m_prjt = PERSPECTIVE;
	m_texture = 0;
	m_type = type;
}

/******************************************************************************/
/*!
\brief - Sprite desturctor

*/
/******************************************************************************/
Sprite::~Sprite(void)
{
	if (m_HasBody)
		delete m_body;

	delete m_texture;
}

/******************************************************************************/
/*!
\brief - Get Sprite;s id

\return m_id - sprite's id
*/
/******************************************************************************/
const int Sprite::GetID(void) const
{
	return m_id;
}

/******************************************************************************/
/*!
\brief - Set Sprite;s id

\param id - sprite's id
*/
/******************************************************************************/
void Sprite::SetID(const int id)
{
	m_id = id;
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

*/
/******************************************************************************/
void Sprite::BindRigidBody(void)
{
	m_body = new RigidBody();
	m_body->SetScale(m_scale);
	m_HasBody = true;
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
\brief - Get Sprite;s type

\return m_type - sprite's shape
*/
/******************************************************************************/
Type Sprite::GetSpriteType(void) const
{
	return m_type;
}

/******************************************************************************/
/*!
\brief - Set Sprite;s type

\param type - sprite's type
*/
/******************************************************************************/
void Sprite::SetSpriteType(Type type)
{
	m_type = type;
}

/******************************************************************************/
/*!
\brief - Set Sprite;s shape

\param shape - sprite's shape
*/
/******************************************************************************/
void Sprite::SetSpriteShape(Shape shape)
{
	m_shape = shape;
}

/******************************************************************************/
/*!
\brief - Get Sprite;s shape

\return m_shape - sprite's shape
*/
/******************************************************************************/
Shape Sprite::GetSpriteShape(void) const
{
	return m_shape;
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
\brief - Do nothing!
*/
/******************************************************************************/
void Sprite::SetText(wchar_t* text)
{
	UNREFERENCED_PARAMETER(text);
}

/******************************************************************************/
/*!
\brief - Do nothing!
*/
/******************************************************************************/
wchar_t* Sprite::GetText(void) const
{
	return 0;
}
