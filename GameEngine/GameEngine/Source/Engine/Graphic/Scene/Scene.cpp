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
#include <sstream>
#include "../Scene/Scene.h"
#include "../Text/Text.h"
#include "../Sprite/Sprite.h"
#include "../Particle/Particle.h"
#include "../../Utilities/Random.h"
#include "../../InputManager/InputManager.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../StateManager/GameStateManager/GameStateManager.h"

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
	m_width = temp.m_width;
	m_height = temp.m_height;
	m_zNear = temp.m_zNear;
	m_zFar = temp.m_zFar;
	m_fovy = temp.m_fovy;
	aspectRatio = m_width / m_height;

	// Init every sprites
	for (auto it = objList.begin(); it != objList.end(); ++it)
	{
		// If sprite has no texture...
		if (!it->second->GetTexture())
		{
			// If object is normal sprite,
			// Set basic texture; box
			if (it->second->GetType() == SPRITE)
				it->second->SetTexture(m_GSM->GetGLManager()->GetTexture(0));

			// If object is particle
			// Set basic texture; basic particle
			if (it->second->GetType() == PARTICLE)
				it->second->SetTexture(m_GSM->GetGLManager()->GetTexture(2));
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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
void Scene::DrawParticle(Emitter* emitter, float dt)
{
	// Simulate all particles
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	
	// Get type "particle"
	glUniform1i(m_GSM->GetGLManager()->GetUnifrom(TYPE), emitter->GetType());

	for (auto it = emitter->GetParticleContainer().begin();
		it != emitter->GetParticleContainer().end(); ++it)
	{
		// Update pipeline
		Pipeline(*it, dt);
		vec4 sptColor = (*it)->GetColor();

		glUniformMatrix4fv(m_GSM->GetGLManager()->GetUnifrom(TRANSFORM), 1, GL_FALSE, &m_mvp.m_member[0][0]);
		glUniformMatrix4fv(m_GSM->GetGLManager()->GetUnifrom(UV), 1, GL_FALSE, &m_animation.m_member[0][0]);
		glUniform4f(m_GSM->GetGLManager()->GetUnifrom(COLOR), sptColor.x, sptColor.y, sptColor.z, (*it)->m_life);
		glUniform1d(m_GSM->GetGLManager()->GetUnifrom(WAVE), (*it)->GetWaveToggle());
		glUniform2f(m_GSM->GetGLManager()->GetUnifrom(PHASE), m_phase.x, m_phase.y);

		emitter->Update((*it));

		//Refresh the buffer data
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertex_buffer_data), m_vertex_buffer_data, GL_STATIC_DRAW);

		// Bind our texture in Texture Unit 0
		glBindTexture(GL_TEXTURE_2D, emitter->GetTexture()->GetTexId());

		// Draw the quad
		glDrawArrays(GL_QUADS, 0, 4);
	}

	//Todo: How to make this worked by GPU
	//Refresh the buffer data
	//glBufferData(GL_ARRAY_BUFFER, emitter->GetNumOfParticle() * sizeof(emitter->m_particle_buffer_data), NULL, GL_STREAM_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, emitter->GetNumOfParticle() * sizeof(emitter->m_particle_buffer_data), emitter->m_particle_buffer_data);
	//glBindTexture(GL_TEXTURE_2D, emitter->GetTexture()->GetTexId());
	//glDrawArraysInstanced(GL_QUADS, 0, 4, emitter->GetNumOfParticle());
}

/******************************************************************************/
/*!
\brief - Draw texts

\param text - text to be drawn
*/
/******************************************************************************/
void Scene::DrawTexts(Text* text)
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set init values
	GLfloat new_x = static_cast<GLfloat>(text->GetPosition().x);
	GLfloat init_x = new_x, lower_y = 0, nl_offset = 2.f/3.f;
	int num_newline = 1;

	// Iterate all character
	std::string::const_iterator c;
	for (c = text->GetText().begin(); c != text->GetText().end(); ++c)
	{
		Character ch = text->GetFontData().m_chars[*c];
		GLfloat xpos = new_x + ch.Bearing.x * text->GetScale().x;
		GLfloat ypos = text->GetPosition().y - (ch.Size.y - ch.Bearing.y) * text->GetScale().y - lower_y;
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
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_vertex_buffer_data), vertices);
		glDrawArrays(GL_QUADS, 0, 4);
		
		const char newline = *c;
		if (newline == '\n')
		{
			new_x = init_x;
			lower_y = text->GetFontData().m_fontSize * nl_offset * num_newline;
			++num_newline;
		}

		else
			new_x += (ch.Advance >> 6) * text->GetScale().x;
	}
}

/******************************************************************************/
/*!
\brief - Draw Scene
*/
/******************************************************************************/
void Scene::Update(const ObjectList& objList, float dt)
{
	UNREFERENCED_PARAMETER(objList);

	//Refresh the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(m_bgColor.x, m_bgColor.y, m_bgColor.z, m_bgColor.w);

	// Set mouse position
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
			Pipeline((*it), dt);
			vec4 sptColor = (*it)->GetColor();

			glUniform4f(m_GSM->GetGLManager()->GetUnifrom(COLOR), sptColor.x, sptColor.y, sptColor.z, sptColor.w);
			glUniform1i(m_GSM->GetGLManager()->GetUnifrom(TYPE), (*it)->GetType());
			glUniform1f(m_GSM->GetGLManager()->GetUnifrom(TIME), dt);
			
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
			DrawParticle(static_cast<Emitter*>(*it), dt);
		
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
void Scene::Pipeline(Sprite* sprite, float dt)
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
	model = model * mat44::Scale(sprite->GetScale())
		* mat44::Rotate(Math::DegToRad(sprite->GetRotation()), vec3(.0f, .0f, 1.f))
		* mat44::Translate(sprite->GetPosition());

	//calculate fined final matrix
	//glUniformMatrix4fv(m_GSM->GetGLManager()->GetUnifrom(CAMERA), 1, GL_FALSE, &camera.m_member[0][0]);
	//glUniformMatrix4fv(m_GSM->GetGLManager()->GetUnifrom(PROJECTION), 1, GL_FALSE, &projection.m_member[0][0]);
	//glUniformMatrix4fv(m_GSM->GetGLManager()->GetUnifrom(MODEL), 1, GL_FALSE, &model.m_member[0][0]);

	m_mvp = projection.Transpose() * camera.Transpose() * model.Transpose();
	m_mvp = m_mvp.Transpose();

	glUniformMatrix4fv(m_GSM->GetGLManager()->GetUnifrom(TRANSFORM), 1, GL_FALSE, &m_mvp.m_member[0][0]);

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
	m_animation.SetIdentity();
	m_animation = m_animation * mat44::Scale(vec3(sprite->GetDividedFrame(), 1.f));
	m_animation = m_animation * mat44::Translate(vec3(sprite->GetCurrentScene(), 0.f));
	glUniformMatrix4fv(m_GSM->GetGLManager()->GetUnifrom(UV), 1, GL_FALSE, &m_animation.m_member[0][0]);

	if (sprite->GetWaveToggle())
	{
		m_phase.x -= sprite->GetWavePhase().x * dt;
		m_phase.y += sprite->GetWavePhase().y * dt;
		if (m_phase.x < -1.f || m_phase.y > 1.f)
			m_phase.x = m_phase.y = 0.f;

		glUniform1d(m_GSM->GetGLManager()->GetUnifrom(WAVE), sprite->GetWaveToggle());
		glUniform2f(m_GSM->GetGLManager()->GetUnifrom(PHASE), m_phase.x, m_phase.y);
	}

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
void Scene::RemoveSprite(const int id)
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
	mat44 matProjection = mat44::Perspective(
		m_GSM->GetGLManager()->GetProjectionInfo().m_fovy,
		m_GSM->GetGLManager()->GetProjectionInfo().m_width / m_GSM->GetGLManager()->GetProjectionInfo().m_height,
		m_GSM->GetGLManager()->GetProjectionInfo().m_zNear,
		m_GSM->GetGLManager()->GetProjectionInfo().m_zFar).Transpose()
		* mat44::LookAt(
		vec3(m_camera),
		vec3(m_camera.x, m_camera.y, 0),
		vec3(cosf(Math::DegToRad((m_camera.w + 90.f))),
		sinf(Math::DegToRad((m_camera.w + 90.f))),
		0)).Transpose();

	mat44 matInverse = matProjection.Inverse();

	float in[4];
	float winZ = 1.0;

	in[0] = (2.f * (InputManager::GetInstance().GetRawMousePosition().x / m_width)) - 1.0f;
	in[1] = 1.f - (2.f * (InputManager::GetInstance().GetRawMousePosition().y / m_height));
	in[2] = 2.f * winZ - 1.f;
	in[3] = 1.f;

	vec4 vIn = vec4(in[0], in[1], in[2], in[3]);
	vec4 pos = matInverse * vIn;

	pos.w = 1.f / pos.w;

	pos.x *= pos.w;
	pos.y *= pos.w;
	pos.z = 0.f;

	InputManager::GetInstance().SetPerspMouse(pos);
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

	InputManager::GetInstance().SetOrthoMouse(vec3((float)posX, -(float)posY, 0.f));
}
