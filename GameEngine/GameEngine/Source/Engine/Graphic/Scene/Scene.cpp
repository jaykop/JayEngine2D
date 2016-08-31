/******************************************************************************/
/*!
\file   Scene.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Scene's class functions

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

#include <algorithm>
#include "../Text/Text.h"
#include "../Light/Light.h"
#include "../Scene/Scene.h"
#include "../Sprite/Sprite.h"
#include "../Particle/Particle.h"
//#include "../../Utilities/Time.h"
#include "../../Utilities/Random.h"
#include "../../InputManager/InputManager.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../StateManager/GameStateManager/GameStateManager.h"
#define DELTA_TIME 0.169F
/******************************************************************************/
/*!
\brief - Scene Constructor

\param pApp - pointer to Application

*/
/******************************************************************************/
Scene::Scene(GameStateManager* gsm)
: m_width(0), m_height(0), m_zNear(0),
m_zFar(0), m_fovy(0), aspectRatio(0), m_radius(0),
m_camera(vec4()), m_bgColor(vec4(0, 0, 0, 0)), 
m_darkness(false), m_maxlightZ(0.f)
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
			if (it->second->GetType() == SPRITE || it->second->GetType() == DARKNESS)
				it->second->SetTexture(m_GSM->GetGLManager()->GetTexture(0));

			// If object is particle
			// Set basic texture; basic particle
			else if (it->second->GetType() == PARTICLE)
				it->second->SetTexture(m_GSM->GetGLManager()->GetTexture(2));

			else if (it->second->GetType() == LIGHT)
				it->second->SetTexture(m_GSM->GetGLManager()->GetTexture(8));
		}
	}

	// Time runs
	Timer::GetInstance().StartTime();
}

/******************************************************************************/
/*!
\brief - Draw sprites
\param sprite - sprite to be drawn
*/
/******************************************************************************/
void Scene::DrawSprites(Sprite* sprite)
{
	if (sprite->GetType() == DARKNESS)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);

	else
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

		glUniformMatrix4fv(m_GSM->GetGLManager()->GetUnifrom(UV), 1, GL_FALSE, &m_animation.m_member[0][0]);
		glUniform4f(m_GSM->GetGLManager()->GetUnifrom(COLOR), sptColor.x, sptColor.y, sptColor.z, (*it)->m_life);

		//emitter->GetDirection();
		//emitter->GetSpeed();
		//emitter->GetPosition();
		//emitter->GetBoundary();
		//(*it)->m_life;
		//(*it)->m_fade;


		//glUniform3f(m_GSM->GetGLManager()->GetUnifrom(PARTICLE_DIR), "Particle_Dir");
		//glUniform3f(m_GSM->GetGLManager()->GetUnifrom(PARTICLE_SPD), "Particle_Spd");
		//glUniform3f(m_GSM->GetGLManager()->GetUnifrom(PARTICLE_POS), "Particle_Pos");
		//glUniform3f(m_GSM->GetGLManager()->GetUnifrom(PARTICLE_FORCE), "Particle_Force");	
		//glUniform1f(m_GSM->GetGLManager()->GetUnifrom(PARTICLE_FADE), "Particle_Fade");	
		//glUniform1f(m_GSM->GetGLManager()->GetUnifrom(PARTICLE_BOUND), "Particle_Bound");
		//glUniform1f(m_GSM->GetGLManager()->GetUnifrom(PARTICLE_LIFE), "Particle_Life");		
		//glUniform1f(m_GSM->GetGLManager()->GetUnifrom(PARTICLE_ROT), "Particle_Rot");	
		//glUniform4f(m_GSM->GetGLManager()->GetUnifrom(PARTICLE_COLOR), "Particle_Color");
		//glUniform4f(m_GSM->GetGLManager()->GetUnifrom(PARTICLE_EDGE), "Particle_edgeColor");

		UpdateParticle((*it));

		//Refresh the buffer data
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertex_buffer_data), m_vertex_buffer_data, GL_STATIC_DRAW);

		// Bind our texture in Texture Unit 0
		glBindTexture(GL_TEXTURE_2D, emitter->GetTexture()->GetTexId());

		// Draw the quad
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
\brief - Draw light
\param light - light to be drawn
*/
/******************************************************************************/
void Scene::DrawLights(Light* light)
{
	// Get diffuse
	vec3 diffuse = light->GetDiffuse();

	glUniform3f(m_GSM->GetGLManager()->GetUnifrom(LIGHT_DIFFUSE), diffuse.x, diffuse.y, diffuse.z);
	glUniform1f(m_GSM->GetGLManager()->GetUnifrom(LIGHT_DISTANCE), light->GetDistance());
	glUniform1f(m_GSM->GetGLManager()->GetUnifrom(LIGHT_RADIUS), light->GetRadius());

	glEnable(GL_BLEND);
	// If ther is darkness sprite,
	if (m_darkness)
		glBlendFuncSeparate(GL_DST_ALPHA, GL_ONE, GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);

	// If not,
	else
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	//Refresh the buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertex_buffer_data), m_vertex_buffer_data, GL_STATIC_DRAW);

	// Bind our texture in Texture Unit 0
	glBindTexture(GL_TEXTURE_2D, light->GetTexture()->GetTexId());

	// Draw the triangle
	glDrawArrays(GL_QUADS, 0, 4);
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
			glUniform1f(m_GSM->GetGLManager()->GetUnifrom(TIME), Timer::GetInstance().GetElapsedTime());

			//Todo: high quality?
			//glUniformMatrix4fv();

			// Draw Texts 
			if ((*it)->GetType() == TEXT)
				DrawTexts(static_cast<Text*>(*it));
			
			else if ((*it)->GetType() == LIGHT)
				DrawLights(static_cast<Light*>(*it));

			// Draw Sprites
			else if ((*it)->GetType() == SPRITE ||
				(*it)->GetType() == DARKNESS)
				DrawSprites(*it);

		}

		// Draw Particles
		else 
			DrawParticle(static_cast<Emitter*>(*it), dt);
		
	}
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

	glUniformMatrix4fv(m_GSM->GetGLManager()->GetUnifrom(MODEL), 1, GL_FALSE, &model.m_member[0][0]);
	glUniformMatrix4fv(m_GSM->GetGLManager()->GetUnifrom(VIEWPORT), 1, GL_FALSE, &camera.m_member[0][0]);
	glUniformMatrix4fv(m_GSM->GetGLManager()->GetUnifrom(PROJECTION), 1, GL_FALSE, &projection.m_member[0][0]);

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

	if (sprite->HasEffect())
	{
		// Wave effect part...
		auto wave_effect = sprite->GetEffect(WAVE);
		if (wave_effect && wave_effect->GetWaveToggle())
		{
			m_phase.x -= wave_effect->GetWavePhase().x * dt;
			m_phase.y += wave_effect->GetWavePhase().y * dt;
			if (m_phase.x < -1.f || m_phase.y > 1.f)
				m_phase.x = m_phase.y = 0.f;

			glUniform1d(m_GSM->GetGLManager()->GetUnifrom(WAVE_TOGGLE), sprite->GetEffect(WAVE)->GetWaveToggle());
		}

		auto sobel_effect = sprite->GetEffect(SOBEL);
		if (sobel_effect && sobel_effect->GetSobelToggle())
		{
			glUniform1d(m_GSM->GetGLManager()->GetUnifrom(SOBEL_TOGGLE), sprite->GetEffect(SOBEL)->GetSobelToggle());
			glUniform1f(m_GSM->GetGLManager()->GetUnifrom(SOBEL_AMOUNT), sprite->GetEffect(SOBEL)->GetSobelAmount());

		}

		auto manip_effect = sprite->GetEffect(MANIPULATION);
		if (manip_effect && manip_effect->GetManipToggle())
		{
			glUniform1d(m_GSM->GetGLManager()->GetUnifrom(MANIP_TOGGLE), sprite->GetEffect(MANIPULATION)->GetManipToggle());
			
		}

		auto blur_effect = sprite->GetEffect(BLUR);
		if (blur_effect && blur_effect->GetBlurToggle())
		{
			glUniform1d(m_GSM->GetGLManager()->GetUnifrom(BLUR_TOGGLE), sprite->GetEffect(BLUR)->GetBlurToggle());
			glUniform1f(m_GSM->GetGLManager()->GetUnifrom(BLUR_AMOUNT), sprite->GetEffect(BLUR)->GetBlurAmount());
		}
	}

	else
	{
		glUniform1d(m_GSM->GetGLManager()->GetUnifrom(WAVE_TOGGLE), sprite->HasEffect());
		glUniform1d(m_GSM->GetGLManager()->GetUnifrom(SOBEL_TOGGLE), sprite->HasEffect());
		glUniform1d(m_GSM->GetGLManager()->GetUnifrom(BLUR_TOGGLE), sprite->HasEffect());
		glUniform1d(m_GSM->GetGLManager()->GetUnifrom(MANIP_TOGGLE), sprite->HasEffect());
	}

	glUniform2f(m_GSM->GetGLManager()->GetUnifrom(WAVE_PHASE), m_phase.x, m_phase.y);
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
	auto it = m_DrawList.begin();	// Declare outside

	// If there is darkness sprite,
	// turn the toggle on...
	if (sprite->GetType() == DARKNESS)
		m_darkness = true;

	// Set max light z order...
	else if (sprite->GetType() == LIGHT &&
		m_maxlightZ < sprite->GetPosition().z)
		m_maxlightZ = sprite->GetPosition().z;

	for (; it != m_DrawList.end(); ++it)
	{
		// If new sprite's z order is lower than next sprite
		// Stop here
		if ((*it)->GetPosition().z > sprite->GetPosition().z)
			break;
	}

	// Set Darkness's z order;
	if (m_darkness)
		sprite->SetPosition(vec3(
		sprite->GetPosition().x,
		sprite->GetPosition().y,
		m_maxlightZ + 1.f));

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
			if ((*it)->GetType() == DARKNESS)
				m_darkness = false;

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

/******************************************************************************/
/*!
\brief - Main update function
\param particle
*/
/******************************************************************************/
void Scene::UpdateParticle(Particle* particle)
{
	// Render usual particle
	if (particle->m_life > 0.f)
		RenderParticle(particle);

	// refresh particle's info
	else
		RefreshParticle(particle);
}


/******************************************************************************/
/*!
\brief - Render each particle
\param particle
*/
/******************************************************************************/
void Scene::RenderParticle(Particle* particle)
{
	Emitter* parent = particle->m_parent;

	vec3 norm_dir = parent->GetDirection();
	norm_dir = norm_dir.Normalize();
	vec3 new_force;

	if (!parent->GetDirection().Length())
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
		parent->GetPosition().z));

	// Set new fade
	float new_fade = particle->m_fade * new_force.Length() / parent->GetBoundary();

	// Reduce particle's life
	particle->m_life -= new_fade;

	// Update rotation
	particle->SetRotation(particle->GetRotation() + parent->GetSpeed());

	// Color effect
	// Change color from inside noe to outside one
	if (parent->GetEdgeColor().Length())
	{
		vec3 colorOffset = parent->GetEdgeColor() - parent->GetColor();

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
void Scene::RefreshParticle(Particle* particle)
{
	Emitter* parent = particle->m_parent;

	// If the emitter mode is explosion,
	// there is no more refreshing precess
	if (parent->GetExplosionToggle())
	{
		// Reset the original position
		if (parent->GetMode() == FIRE)
		{
			parent->SetDirection(vec3(0.f, 1.f));
			float repos_offset = 3.f / 5.f;
			float new_pos = parent->GetBoundary() * repos_offset;
			particle->SetPosition(parent->GetPosition() +
				vec3(
				Random::GetInstance().GetRandomFloat(-new_pos, new_pos),
				Random::GetInstance().GetRandomFloat(-new_pos, new_pos)));
		}

		else if (parent->GetMode() == SNOW)
		{
			particle->SetPosition(parent->GetPosition() +
				vec3(
				Random::GetInstance().GetRandomFloat(parent->GetSnowStartingPoint().x, parent->GetSnowEndingPoint().x),
				Random::GetInstance().GetRandomFloat(parent->GetSnowStartingPoint().y, parent->GetSnowEndingPoint().y)));
		}

		else
			particle->SetPosition(parent->GetPosition());

		// Rescale?
		if (parent->GetRandomScaleToggle())
		{
			float randomSize = Random::GetInstance().GetRandomFloat(parent->GetRandomScaleRange().x, parent->GetRandomScaleRange().y);
			particle->SetScale(vec3(randomSize, randomSize));
		}

		// Reset life
		particle->m_life = 1.f;

		// Reset color
		particle->SetColor(vec4(
			parent->GetColor().x,
			parent->GetColor().y,
			parent->GetColor().z,
			particle->m_life));

		// Set Velocity;
		if (!parent->GetDirection().Length())
		{
			particle->m_velocity = vec3(
				Random::GetInstance().GetRandomFloat(-1.f, 1.f),
				Random::GetInstance().GetRandomFloat(-1.f, 1.f));
			particle->m_velocity = particle->m_velocity.Normalize();
		}

		// Set speed
		particle->m_speed =
			parent->GetSpeed() * vec3(
			Random::GetInstance().GetRandomFloat(0.f, 1.f),
			Random::GetInstance().GetRandomFloat(0.f, 1.f));

		// Reset vanishing speed
		particle->m_fade = Random::GetInstance().GetRandomFloat(DELTA_TIME, 1.f);

		if (parent->GetMode() == EXPLOSION && parent->GetRefreshingToggle())
			parent->ActivateExplosion(false);
	}
}
