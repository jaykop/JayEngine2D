#include "Scene.h"
#include "../Graphic//Sprite.h"
#include "../ObjectManager/ObjectManager.h"

Scene::Scene(void)
: m_width(0), m_height(0), m_zNear(0),
m_zFar(0), m_fovy(0), aspectRatio(0),
m_camera(vec4()), m_bgColor(vec4(0,0,0,0))
{}

Scene::~Scene(void)
{}

void Scene::Init()
{
	//Get projection information
	ProjectionInfo temp = GLApplication::GetInstance().GetProjectionInfo();

	m_width = static_cast<int>(temp.m_width);
	m_height = static_cast<int>(temp.m_height);
	m_zNear = static_cast<float>(temp.m_zNear);
	m_zFar = static_cast<float>(temp.m_zFar);
	m_fovy = static_cast<float>(temp.m_fovy);
	aspectRatio = static_cast<float>(m_width) / static_cast<float>(m_height);

	m_camera = vec4(0, 0, 80, 0);
}

void Scene::Draw(const ObjectManager& ObjM)
{
	//

	//Refresh the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(m_bgColor.x, m_bgColor.y, m_bgColor.z, m_bgColor.w);

	for (auto it = ObjM.GetList().begin(); it != ObjM.GetList().end(); ++it)
	{
		//Update pipeline
		Pipeline(*it->second);

		//Initialize matrix
		m_matrixID = glGetUniformLocation(GLApplication::GetInstance().GetShader().m_programID, "MVP");

		//Implement Matrix
		glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &m_mvp.m_member[0][0]);

		vec4 sptColor = (it->second->GetColor());
		GLuint color = glGetUniformLocation(GLApplication::GetInstance().GetShader().m_programID, "myColor");
		glUniform4f(color, sptColor.x, sptColor.y, sptColor.z, sptColor.w);
		
		//More high quality?
		//glUniformMatrix4fv();

		//first attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, GLApplication::GetInstance().GetVertexBuffer());
		glVertexAttribPointer(
			0,				// must be match the layout in the shader
			3,				// size
			GL_FLOAT,		// type
			GL_FALSE,		// normalized
			0,				// stride
			(void*)0		// array buffer offset
			);

		// Draw the triangle
		glDrawArrays(GL_QUADS, 0, 4);
		glDisableVertexAttribArray(0);
	}
}

void Scene::Shutdown()
{
	
}


void Scene::Pipeline(const Sprite& sprite)
{
	//Setting Perspection
	mat44 projection = mat44::Perspective(m_fovy, aspectRatio, m_zNear, m_zFar);

	// Ortho Perspection
	// mat44 projection = mat44::Ortho(-m_width / 2.f, m_width / 2.f, -m_height / 2.f, m_height / 2.f, m_zNear, m_zFar);

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
	model = model * mat44::Scale(sprite.GetScale());
	model = model * mat44::Rotate(Math::DegToRad(sprite.GetRotation()), vec3(.0f, .0f, 1.f));
	model = model * mat44::Translate(sprite.GetPosition());

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