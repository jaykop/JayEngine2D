#include "../BaseData/BaseEnigne.h"
#include "LV3.h"

LV3Stage::LV3Stage(GameStateManager* gsm)
{
	m_GSM = gsm;
}

LV3Stage::~LV3Stage()
{

}

void LV3Stage::Load(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "LV3Stage::Load\n";

	//Bind basic systems
	m_OBM.BindGameSystem(m_GSM);

	// Load json data
	m_OBM.LoadStageData("Resource/Data/LV3.json");
}

void LV3Stage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv3Stage::Init\n";

	// Init game systems; 
	m_OBM.InitGameSystem(gd);
}

void LV3Stage::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv3Stage::Update\n";

	// Update basic systems
	m_OBM.UpdateGameSystem(gd);
}

void LV3Stage::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv3Stage::Shutdown\n";

	// Shutdown basic systems
	m_OBM.ShutdownGameSystem(gd);

	// Cleare all Objects of the list
	m_OBM.ClearObjectList();
}

void LV3Stage::Unload(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "LV3Stage::Unload\n";

	// Unload stage data
	m_OBM.UnloadStageData();
}

void LV3Stage::SampleRender(void)
{

	// Floor
	mat44 model;
	//glBindVertexArray(planeVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	//glBindVertexArray(0);
	// Cubes
	model.SetIdentity();

	//Setting Perspection
	mat44 projection;
	//if (sprite->GetProjectionType() == PERSPECTIVE)
	//	projection = mat44::Perspective(m_GSM->GetGLManager()->GetProjectionInfo().m_fovy, 
	//	m_GSM->GetGLManager()->GetProjectionInfo().aspectRatio, 
	//	m_GSM->GetGLManager()->GetProjectionInfo().m_zNear, 
	//	m_GSM->GetGLManager()->GetProjectionInfo().m_zFar);
	//else
		projection = mat44::Ortho(-m_GSM->GetGLManager()->GetProjectionInfo().m_width / 2.f, 
		m_GSM->GetGLManager()->GetProjectionInfo().m_width / 2.f,
		-m_GSM->GetGLManager()->GetProjectionInfo().m_height / 2.f, 
		m_GSM->GetGLManager()->GetProjectionInfo().m_height / 2.f, 
		m_GSM->GetGLManager()->GetProjectionInfo().m_zNear, 
		m_GSM->GetGLManager()->GetProjectionInfo().m_zFar);

	//Setting Camera
	mat44 camera = mat44::LookAt(
		vec3(m_OBM.GetGameScene()->GetCamera()),
		vec3(m_OBM.GetGameScene()->GetCamera().x, m_OBM.GetGameScene()->GetCamera().y, 0),
		vec3(cosf(Math::DegToRad((m_OBM.GetGameScene()->GetCamera().w + 90.f))),
		sinf(Math::DegToRad((m_OBM.GetGameScene()->GetCamera().w + 90.f))),
		0));

	//Transform model mats
	model = model * mat44::Scale(vec3(100, 100))
		* mat44::Rotate(Math::DegToRad(0.f), vec3(.0f, .0f, 1.f))
		* mat44::Translate(vec3(0, 0));

	mat44 m_mvp;

	//calculate fined final matrix
	m_mvp = projection.Transpose() * camera.Transpose() * model.Transpose();
	m_mvp = m_mvp.Transpose();

	mat44 m_animation;
	m_animation.SetIdentity();

	vec4 sptColor(1.f, 1.f, 1.f, 1.f);

	glUniformMatrix4fv(m_GSM->GetGLManager()->GetUnifrom(TRANSFORM), 1, GL_FALSE, &m_mvp.m_member[0][0]);
	glUniformMatrix4fv(m_GSM->GetGLManager()->GetUnifrom(UV), 1, GL_FALSE, &m_animation.m_member[0][0]);
	glUniform4f(m_GSM->GetGLManager()->GetUnifrom(COLOR), sptColor.x, sptColor.y, sptColor.z, sptColor.w);
	glUniform1i(m_GSM->GetGLManager()->GetUnifrom(TYPE), 1);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Refresh the buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertex_buffer_data), m_vertex_buffer_data, GL_STATIC_DRAW);

	// Bind our texture in Texture Unit 0
	glBindTexture(GL_TEXTURE_2D, depthMap);

	// Draw the triangle
	glDrawArrays(GL_QUADS, 0, 4);
}