#include <algorithm>
#include "Scene.h"
#include "../Graphic//Sprite.h"
#include "../ObjectManager/ObjectManager.h"
#include "../Apps/Application.h"

Scene::Scene(Application* pApp)
: m_width(0), m_height(0), m_zNear(0),
m_zFar(0), m_fovy(0), aspectRatio(0), m_radius(0),
m_camera(vec4()), m_bgColor(vec4(0,0,0,0))
{
	m_pApp = pApp;
	m_DrawList.clear();
}

Scene::~Scene(void)
{}

void Scene::Init(void)
{
	//Get projection information
	ProjectionInfo temp = m_pApp->GetGLManager()->GetProjectionInfo();

	m_width = static_cast<int>(temp.m_width);
	m_height = static_cast<int>(temp.m_height);
	m_zNear = static_cast<float>(temp.m_zNear);
	m_zFar = static_cast<float>(temp.m_zFar);
	m_fovy = static_cast<float>(temp.m_fovy);
	aspectRatio = static_cast<float>(m_width) / static_cast<float>(m_height);

	m_camera = vec4(0, 0, 80, 0);

	m_texId = glGetUniformLocation(m_pApp->GetGLManager()->GetShader().m_programID, "Texture");
	
}

void Scene::Draw(void)
{
	//Refresh the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(m_bgColor.x, m_bgColor.y, m_bgColor.z, m_bgColor.w);

	//Lambda loop expression
	//std::for_each(m_DrawList.begin(), m_DrawList.end(),
	//	[&](DrawList::iterator it)
	//{

	for (auto it = m_DrawList.begin(); it != m_DrawList.end(); ++it)
	{
		//Update pipeline
		Pipeline((*it));

		//Initialize matrix
		m_matrixID = glGetUniformLocation(m_pApp->GetGLManager()->GetShader().m_programID, "MVP");

		//Implement Matrix
		glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &m_mvp.m_member[0][0]);

		//Coloring
		vec4 sptColor = ((*it)->GetColor());
		GLuint color = glGetUniformLocation(m_pApp->GetGLManager()->GetShader().m_programID, "Color");
		glUniform4f(color, sptColor.x, sptColor.y, sptColor.z, sptColor.w);

		GLuint shape = glGetUniformLocation(m_pApp->GetGLManager()->GetShader().m_programID, "Shape");
		glUniform1d(shape, (*it)->GetSpriteShape());

		//More high quality?
		//glUniformMatrix4fv();

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, (*it)->GetTexture()->GetTexId());

		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(m_texId, 0);

		glEnable(GL_NICEST);
		//first attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_pApp->GetGLManager()->GetVertexBuffer());
		glVertexAttribPointer(
			0,						// must be match the layout in the shader
			3,						// size : X+Y+Z => 3
			GL_FLOAT,				// type
			GL_FALSE,				// normalized
			5 * sizeof(GLfloat),	// stride
			(GLvoid*)0				// array buffer offset
			);

		//// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_pApp->GetGLManager()->GetVertexBuffer());
		glVertexAttribPointer(
			1,								// attribute. No particular reason for 1, but must match the layout in the shader.
			2,								// size : U+V => 2
			GL_FLOAT,						// type
			GL_TRUE,						// normalized?
			5 * sizeof(GLfloat),			// stride
			(GLvoid*)(3 * sizeof(GLfloat))	// array buffer offset
			);


		// Draw the triangle
		glDrawArrays(GL_QUADS, 0, 4);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisable(GL_NICEST);		
	}

	//}); //Lambda loop expression
}

void Scene::Shutdown()
{
	// Clear all sprites from the list to draw
	m_DrawList.clear();
}


void Scene::Pipeline(const Sprite* sprite)
{
	//Setting Perspection
	mat44 projection = mat44::Perspective(m_fovy, aspectRatio, m_zNear, m_zFar);

	// Ortho Perspection
	//mat44 projection = mat44::Ortho(-m_width / 2.f, m_width / 2.f, -m_height / 2.f, m_height / 2.f, m_zNear, m_zFar);

	//Setting Camera
	mat44 camera = mat44::LookAt(
		vec3(m_camera),
		vec3(m_camera.x, m_camera.y, 0),
		vec3(cosf(Math::DegToRad((m_camera.w + 90.f))),
			sinf(Math::DegToRad((m_camera.w + 90.f))),
			0));

	//Init model matrix
	mat44 model;
	model.SetIdentity();

	//Transform model mat
	model = model * mat44::Scale(sprite->GetScale());
	model = model * mat44::Rotate(Math::DegToRad(sprite->GetRotation()), vec3(.0f, .0f, 1.f));
	model = model * mat44::Translate(sprite->GetPosition());

	//calculate fined final matrix
	m_mvp = projection.Transpose() * camera.Transpose() * model.Transpose();
	m_mvp = m_mvp.Transpose();
}

void Scene::SetCamera(const vec4& camera)
{
	m_camera = camera;
}

vec4 Scene::GetCamera(void) const
{
	return m_camera;
}

void Scene::SetBackgroundColor(const vec4& background)
{
	m_bgColor = background;
}

vec4 Scene::GetBackgroundColor(void) const
{
	return m_bgColor;
}

namespace
{
	// Order algorithm
	bool reorder_sprites(const Sprite* a, const Sprite* b)
	{
		// Distinguish ortho type and pers type 
		if (a->GetProjectionType() == ORTHOGONAL && !(b->GetProjectionType() == ORTHOGONAL))
		{
			return false;
		}
		else if (!(a->GetProjectionType() == ORTHOGONAL) && b->GetProjectionType() == ORTHOGONAL)
		{
			return true;
		}
		else
		{
			// Return higher z order one
			return a->GetPosition().z < b->GetPosition().z;
		}
	}
}

void Scene::ReorderSprites(void)
{
	// Order algorithm
	std::sort(m_DrawList.begin(), m_DrawList.end(), reorder_sprites);
}

void Scene::AddSprite(Sprite* newSpt)
{
	// Add sprite by Zorder and Projection type

	auto it = m_DrawList.begin();

	for (; it != m_DrawList.end(); ++it)
	{
		// If new sprite's z order is lower than next sprite
		// Stop here
		if ((*it)->GetPosition().z > newSpt->GetPosition().z)
			break;	
	}

	// Add sprite to the place where stopped
	m_DrawList.insert(it, newSpt);

	// Sort
	ReorderSprites();
}

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

	ReorderSprites();
}