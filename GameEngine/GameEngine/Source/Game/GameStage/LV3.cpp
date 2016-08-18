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
	// m_OBM.LoadStageData("Resource/Data/Sample.json");
}

void LV3Stage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv3Stage::Init\n";

	// Depth map
	glGenFramebuffers(1, &depthMapFBO);

	// 2d texture
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		m_GSM->GetResolution().width, m_GSM->GetResolution().height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	m_OBM.InitGameSystem(gd);

}

void LV3Stage::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv3Stage::Update\n";

	if (InputManager::GetInstance().KeyPressed(KEY_ESC))
		m_GSM->SetQuit(true);

	else if (InputManager::GetInstance().KeyPressed(KEY_1))
		m_GSM->SetNextStage(ST_LV1);

	else if (InputManager::GetInstance().KeyPressed(KEY_2))
		m_GSM->SetNextStage(ST_LV2);

	else if (InputManager::GetInstance().KeyPressed(KEY_3))
		m_GSM->SetNextStage(ST_LV3);

	else if (InputManager::GetInstance().KeyPressed(KEY_0))
		m_GSM->SetNextStage(ST_MENU);

	else if (InputManager::GetInstance().KeyTriggered(KEY_R))
		m_GSM->Restart(true);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.f, 0.f, 0.f, 0.f);

	mat44 lightProjection, lightView;
	mat44 lightSpaceMatrix;
	GLfloat near_plane = 1.0f, far_plane = 7.5f;
	lightProjection = mat44::Ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	lightView = mat44::LookAt(vec3(0.f, 0.f, 0.f), vec3(0.0f), vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;
	// - render scene from light's point of view
	glUniformMatrix4fv(glGetUniformLocation(m_GSM->GetGLManager()->GetShader().m_programID, "lightSpaceMatrix"), 1, GL_FALSE, &lightSpaceMatrix.m_member[0][0]);

	glViewport(0, 0, m_GSM->GetResolution().width, m_GSM->GetResolution().height);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
		// Here render depth map
	SampleRender();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, m_GSM->GetResolution().width, m_GSM->GetResolution().height);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// matrix
	glBindTexture(GL_TEXTURE_2D, depthMap);
	SampleRender();
		 //Here render scene

	//m_OBM.UpdateGameSystem(gd);
}

void LV3Stage::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv3Stage::Shutdown\n";

	m_OBM.ShutdownGameSystem(gd);
}

void LV3Stage::Unload(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "LV3Stage::Unload\n";

	// m_OBM.UnloadStageData();
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