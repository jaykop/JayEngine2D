/******************************************************************************/
/*!
\file   Scene.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Scene's class functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include <algorithm>
#include "Scene.h"
#include "Text.h"
#include "Sprite.h"
#include "Particle.h"
#include "../Utilities/Random.h"
#include "../InputManager/InputManager.h"
#include "../ObjectManager/ObjectManager.h"
#include "../StateManager/GameStateManager/GameStateManager.h"

/******************************************************************************/
/*!
\brief - Scene Constructor

\param pApp - pointer to Application

*/
/******************************************************************************/
Scene::Scene(GameStateManager* gsm)
: m_width(0), m_height(0), m_zNear(0),
m_zFar(0), m_fovy(0), aspectRatio(0), m_radius(0),
m_camera(vec4()), m_bgColor(vec4(0,0,0,0))
{
	m_GSM = gsm;
	m_DrawList.clear();
}

/******************************************************************************/
/*!
\brief - Scene Destructor
*/
/******************************************************************************/
Scene::~Scene(void)
{}

/******************************************************************************/
/*!
\brief - Initiaiize Scene
*/
/******************************************************************************/
void Scene::Init(const ObjectList& objList)
{
	//Get projection information
	ProjectionInfo temp = m_GSM->GetGLManager()->GetProjectionInfo();

	// Set basic scene infomation
	m_width = static_cast<int>(temp.m_width);
	m_height = static_cast<int>(temp.m_height);
	m_zNear = static_cast<float>(temp.m_zNear);
	m_zFar = static_cast<float>(temp.m_zFar);
	m_fovy = static_cast<float>(temp.m_fovy);
	aspectRatio = static_cast<float>(m_width) / static_cast<float>(m_height);
	m_camera = vec4(0, 0, 80, 0);

	// Init every sprites
	for (auto it = objList.begin(); it != objList.end(); ++it)
	{
		// If sprite has no texture...
		if (!it->second->GetTexture()->IsLoaded())
		{
			// If object is normal sprite,
			// Set basic texture; box
			if (it->second->GetType() == SPRITE)
				it->second->GetTexture()->LoadTexture("Resource/Texture/rect.png");

			// If object is particle
			// Set basic texture; basic particle
			if (it->second->GetType() == PARTICLE)
				it->second->GetTexture()->LoadTexture("Resource/Texture/particle.png");
		}
	}
}

/******************************************************************************/
/*!
\brief - Draw sprites

\param sprite - sprite to be drawn
*/
/******************************************************************************/
void Scene::DrawSprites(Sprite* sprite)
{
	//Refresh the buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertex_buffer_data), m_vertex_buffer_data, GL_STATIC_DRAW);

	// Bind our texture in Texture Unit 0
	glBindTexture(GL_TEXTURE_2D, sprite->GetTexture()->GetTexId());

	// Draw the triangle
	glDrawArrays(GL_QUADS, 0, 4);
}

/******************************************************************************/
/*!
\brief - Draw particles

\param particle - particle to be drawn
*/
/******************************************************************************/
void Scene::DrawParticle(Emitter* emitter)
{
	// Simulate all particles
	for (int i = 0;	i != MaxParticle; ++i)
	{
		//Update pipeline
		Pipeline(&(emitter->ParticlesContainer[i]));
		vec4 sptColor = emitter->ParticlesContainer[i].GetColor();

		glUniformMatrix4fv(m_GSM->GetGLManager()->GetUnifrom(TRANSFORM), 1, GL_FALSE, &m_mvp.m_member[0][0]);
		glUniformMatrix4fv(m_GSM->GetGLManager()->GetUnifrom(UV), 1, GL_FALSE, &m_animation.m_member[0][0]);
		glUniform4f(m_GSM->GetGLManager()->GetUnifrom(COLOR), sptColor.x, sptColor.y, sptColor.z, emitter->ParticlesContainer[i].m_life);
		glUniform1d(m_GSM->GetGLManager()->GetUnifrom(TYPE), emitter->ParticlesContainer[i].GetType());

		//Particle &particle = emitter->ParticlesContainer[i];
		if (emitter->ParticlesContainer[i].m_life > 0.f)
		{
			//emitter->ParticlesContainer[i].m_life -= 0.0000169f;	//Decrease life
			emitter->SetColor(vec4(
				emitter->ParticlesContainer[i].GetColor().x, 
				emitter->ParticlesContainer[i].GetColor().y, 
				emitter->ParticlesContainer[i].GetColor().z, 
				emitter->ParticlesContainer[i].m_life));
			//emitter->ParticlesContainer[i].m_speed += vec3(0.0f, -.098f) * 0.169f * 5.f;
			
			vec3 new_speed = emitter->ParticlesContainer[i].m_speed /* + emitter->ParticlesContainer[i].m_slow */ ;
			vec3 new_force = vec3(new_speed.x * cosf(Math::DegToRad(emitter->ParticlesContainer[i].m_dirAngle)),
				new_speed.y * sinf(Math::DegToRad(emitter->ParticlesContainer[i].m_dirAngle)), 0);

			//Update position by velocity and direction
			emitter->ParticlesContainer[i].SetPosition(vec3(
				emitter->ParticlesContainer[i].GetPosition().x + new_force.x,
				emitter->ParticlesContainer[i].GetPosition().y + new_force.y,
				emitter->ParticlesContainer[i].GetPosition().z));

			emitter->ParticlesContainer[i].m_life -= emitter->ParticlesContainer[i].m_slow;
		}

		else
		{
			// Reset the original position
			emitter->ParticlesContainer[i].SetPosition(emitter->GetPosition());

			// Set new velocity
			emitter->ParticlesContainer[i].velocity = vec3(
				Random::GetInstance().GetRandomFloat(-1.f, 1.f),
				Random::GetInstance().GetRandomFloat(-1.f, 1.f));

			//Update particle's speed and velocity
			emitter->ParticlesContainer[i].velocity
				= emitter->ParticlesContainer[i].velocity.Normalize();

			emitter->ParticlesContainer[i].m_dirAngle = Math::RadToDeg(acosf(emitter->ParticlesContainer[i].velocity.DotProduct(vec3(1, 0, 0))));

			//Set directed angle 
			if (emitter->ParticlesContainer[i].velocity.y < 0)
				emitter->ParticlesContainer[i].m_dirAngle = (360 - emitter->ParticlesContainer[i].m_dirAngle);

			emitter->ParticlesContainer[i].m_speed = vec3(
				Random::GetInstance().GetRandomFloat(0.f, 1.f),
				Random::GetInstance().GetRandomFloat(0.f, 1.f));

			// Reset life
			emitter->ParticlesContainer[i].m_life = 1.f;

			// Reset vanishing speed
			emitter->ParticlesContainer[i].m_slow = Random::GetInstance().GetRandomFloat(0.f, 0.169f);
		}

		//Refresh the buffer data
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertex_buffer_data), m_vertex_buffer_data, GL_STATIC_DRAW);

		// Bind our texture in Texture Unit 0
		glBindTexture(GL_TEXTURE_2D, emitter->GetTexture()->GetTexId());

		// Draw the triangle
		glDrawArrays(GL_QUADS, 0, 4);
	}
}

/******************************************************************************/
/*!
\brief - Draw texts

\param text - text to be drawn
*/
/******************************************************************************/
void Scene::DrawTexts(Text* text)
{
	GLfloat new_x = static_cast<GLfloat>(text->GetPosition().x);

	// Iterate all character
	std::wstring::const_iterator c;
	for (c = text->GetText().begin(); c != text->GetText().end(); ++c)
	{
		Character ch = m_GSM->GetGLManager()->GetCharacters()[*c];
		GLfloat xpos = new_x + ch.Bearing.x * text->GetScale().x;
		GLfloat ypos = text->GetPosition().y - (ch.Size.y - ch.Bearing.y) * text->GetScale().y;
		GLfloat zpos = text->GetPosition().z;

		GLfloat w = ch.Size.x * text->GetScale().x;
		GLfloat h = ch.Size.y * text->GetScale().y;

		//Update vbo
		GLfloat vertices[4][5] = {
			{ xpos, ypos + h, zpos, 0.0, 0.0 },
			{ xpos, ypos, zpos, 0.0, 1.0 },
			{ xpos + w, ypos, zpos, 1.0, 1.0 },
			{ xpos + w, ypos + h, zpos, 1.0, 0.0 }
		};

		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glDrawArrays(GL_QUADS, 0, 4);
		new_x += (ch.Advance >> 6) * text->GetScale().x;
	}
}

/******************************************************************************/
/*!
\brief - Draw Scene
*/
/******************************************************************************/
void Scene::Update(const ObjectList& objList)
{
	UNREFERENCED_PARAMETER(objList);

	//Refresh the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(m_bgColor.x, m_bgColor.y, m_bgColor.z, m_bgColor.w);

	GetPerspPosition();
	GetOrthoPosition();

	//Todo: Lambda loop expression
	//std::for_each(m_DrawList.begin(), m_DrawList.end(), [&](DrawList::iterator& it)
	//{

	for (auto it = m_DrawList.begin(); it != m_DrawList.end(); ++it)
	{
		if ((*it)->GetType() != PARTICLE)
		{
			//Update pipeline
			Pipeline((*it));
			vec4 sptColor = ((*it)->GetColor());

			glUniformMatrix4fv(m_GSM->GetGLManager()->GetUnifrom(TRANSFORM), 1, GL_FALSE, &m_mvp.m_member[0][0]);
			glUniformMatrix4fv(m_GSM->GetGLManager()->GetUnifrom(UV), 1, GL_FALSE, &m_animation.m_member[0][0]);
			glUniform4f(m_GSM->GetGLManager()->GetUnifrom(COLOR), sptColor.x, sptColor.y, sptColor.z, sptColor.w);
			glUniform1d(m_GSM->GetGLManager()->GetUnifrom(TYPE), (*it)->GetType());

			//Todo: high quality?
			//glUniformMatrix4fv();

			// Draw Texts 
			if ((*it)->GetType() == TEXT)
				DrawTexts(static_cast<Text*>(*it));

			// Draw Sprites
			else if ((*it)->GetType() == SPRITE)
				DrawSprites(*it);

		}

		// Draw Particles
		else 
		{
			DrawParticle(static_cast<Emitter*>(*it));
		}
	}

	//std::cout <<  "\n";
	//}); //Lambda loop expression
}

/******************************************************************************/
/*!
\brief - Shutdown Scene
*/
/******************************************************************************/
void Scene::Shutdown(const ObjectList& objList)
{
	UNREFERENCED_PARAMETER(objList);

	// Clear all sprites from the list to draw
	m_DrawList.clear();
}

/******************************************************************************/
/*!
\brief - Scene's graphic pipeline

\param sprite - sprite to be drawed
*/
/******************************************************************************/
void Scene::Pipeline(Sprite* sprite)
{
	//Init model matrix
	mat44 model;
	model.SetIdentity();

	//Setting Perspection
	mat44 projection;
	if (sprite->GetProjectionType() == PERSPECTIVE)
		projection = mat44::Perspective(m_fovy, aspectRatio, m_zNear, m_zFar);
	else
		projection = mat44::Ortho(-m_width / 2.f, m_width / 2.f, -m_height / 2.f, m_height / 2.f, m_zNear, m_zFar);

	//Setting Camera
	mat44 camera = mat44::LookAt(
		vec3(m_camera),
		vec3(m_camera.x, m_camera.y, 0),
		vec3(cosf(Math::DegToRad((m_camera.w + 90.f))),
			sinf(Math::DegToRad((m_camera.w + 90.f))),
			0));

	//Transform model mat
	model = model * mat44::Scale(sprite->GetScale());
	model = model * mat44::Rotate(Math::DegToRad(sprite->GetRotation()), vec3(.0f, .0f, 1.f));
	model = model * mat44::Translate(sprite->GetPosition());

	//calculate fined final matrix
	m_mvp = projection.Transpose() * camera.Transpose() * model.Transpose();
	m_mvp = m_mvp.Transpose();

	// Refresh the animation scene
	if (sprite->GetPlayToggle())
	{
		if (sprite->GetDividedSpeed() <= sprite->GetTimer().GetElapsedTime())
		{
			// If current scene is over, refresh
			if (sprite->GetCurrentScene() + sprite->GetDividedFrame() >= 1)
				sprite->SetCurrentScene(0);

			else
				sprite->SetCurrentScene(sprite->GetCurrentScene() + sprite->GetDividedFrame());

			sprite->GetTimer().StartTime();
		}
	}

	// Animation pipeline
	mat44 animation;
	animation.SetIdentity();
	animation = animation * mat44::Scale(vec3(sprite->GetDividedFrame(), 1.f));
	animation = animation * mat44::Translate(vec3(sprite->GetCurrentScene(), 0.f));

	m_animation = animation;

}

/******************************************************************************/
/*!
\brief - Camera settor

\param camera
*/
/******************************************************************************/
void Scene::SetCamera(const vec4& camera)
{
	m_camera = camera;
}

/******************************************************************************/
/*!
\brief - Camera gettor

\return m_camera
*/
/******************************************************************************/
vec4 Scene::GetCamera(void) const
{
	return m_camera;
}

/******************************************************************************/
/*!
\brief - Background Color settor

\param background
*/
/******************************************************************************/
void Scene::SetBackgroundColor(const vec4& background)
{
	m_bgColor = background;
}

/******************************************************************************/
/*!
\brief - Background Color gettor

\return m_bgColor
*/
/******************************************************************************/
vec4 Scene::GetBackgroundColor(void) const
{
	return m_bgColor;
}

namespace
{
	/******************************************************************************/
	/*!
	\brief - Order algorithm

	\param a - 1st compared
	\param b - 2nd compared

	*/
	/******************************************************************************/
	bool reorder_sprites(const Sprite* a, const Sprite* b)
	{
		// Distinguish ortho type and pers type 
		if (a->GetProjectionType() == ORTHOGONAL && b->GetProjectionType() == PERSPECTIVE)
			return false;
		
		else if (a->GetProjectionType() == PERSPECTIVE && b->GetProjectionType() == ORTHOGONAL)
			return true;
		
		// Return higher z order on
		else
			return a->GetPosition().z < b->GetPosition().z;
	}
}

/******************************************************************************/
/*!
\brief - Order algorithm

*/
/******************************************************************************/
void Scene::ReorderSprites(void)
{
	// Order algorithm
	std::sort(m_DrawList.begin(), m_DrawList.end(), reorder_sprites);
}

/******************************************************************************/
/*!
\brief - Add Sprite to the list

\param newSpt - sprite to put into the list
*/
/******************************************************************************/
void Scene::AddSprite(Sprite* sprite)
{
	// Add sprite by Zorder and Projection type
	auto it = m_DrawList.begin();

	for (; it != m_DrawList.end(); ++it)
	{
		// If new sprite's z order is lower than next sprite
		// Stop here
		if ((*it)->GetPosition().z > sprite->GetPosition().z)
			break;
	}

	// Add sprite to the place where stopped
	m_DrawList.insert(it, sprite);

	// Sort Sprites by projection type and z Order
	ReorderSprites();

}

/******************************************************************************/
/*!
\brief - Delete Sprite from the list

\param id - sprite's id to delete
*/
/******************************************************************************/
void Scene::DeleteSprite(const int id)
{
	//Find the sprite from the vector
	for (auto it = m_DrawList.begin(); it != m_DrawList.end(); ++it)
	{
		// If found same id that client want to get
		if ((*it)->GetID() == id)
		{
			// Delete it
			m_DrawList.erase(it);
			break;
		}
	}

	// Sort Sprites by projection type and z Order
	ReorderSprites();
}

/******************************************************************************/
/*!
\brief Set mouse position on perpective world
*/
/******************************************************************************/
void Scene::GetPerspPosition(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(m_fovy, aspectRatio, m_zNear, m_zFar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(m_camera.x, m_camera.y, m_camera.z,
		m_camera.x, m_camera.y, 0.0,
		(double)cosf((float)((m_camera.w + 90.f) * RADIAN)),
		(double)sinf((float)((m_camera.w + 90.f) * RADIAN)),
		0.0);

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	GLdouble modelview[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

	GLdouble projection[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	GLdouble winX = 0, winY = 0, winZ = 0;

	gluProject(0, 0, 0, modelview, projection, viewport, &winX, &winY, &winZ);

	winX = (float)InputManager::GetInstance().GetRawMousePosition().x;
	winY = (float)InputManager::GetInstance().GetRawMousePosition().y;
	winY = (float)viewport[3] - winY;

	GLdouble posX = m_camera.x, posY = m_camera.y, posZ = m_camera.z;

	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	InputManager::GetInstance().SetPerspMouse(vec3((float)posX, (float)posY, (float)posZ));

}

/******************************************************************************/
/*!
\brief Set mouse position on orthogonal world
*/
/******************************************************************************/
void Scene::GetOrthoPosition(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-m_width / 2.f, m_width / 2.f, m_height / 2.f, -m_height / 2.f, m_zNear, m_zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	GLdouble modelview[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

	GLdouble projection[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	GLdouble winX = 0, winY = 0, winZ = 0;

	gluProject(0, 0, 0, modelview, projection, viewport, &winX, &winY, &winZ);

	winX = (float)InputManager::GetInstance().GetRawMousePosition().x;
	winY = (float)InputManager::GetInstance().GetRawMousePosition().y;
	winY = (float)viewport[3] - winY;

	GLdouble posX = 0, posY = 0, posZ = 0;

	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	InputManager::GetInstance().SetOrthoMouse(vec3((float)posX, (float)posY, (float)posZ));
}