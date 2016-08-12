#include "DemoLogic_LV2.h"
#include "../BaseData/BaseEnigne.h"

GameLogic* DemoLogic_LV2Builder::BuildLogic(Object* Owner) const
{
	return new DemoLogic_LV2(Owner);
}

DemoLogic_LV2::DemoLogic_LV2(Object* owner)
: m_Owner(owner), m_OBM(owner->GetOBM()), m_GSM(owner->GetOBM()->GetGSM())
{}

void DemoLogic_LV2::Load(const Json::Value& data)
{
	UNREFERENCED_PARAMETER(data);
}

void DemoLogic_LV2::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "DemoLogic_LV2 Inited\n";

	m_OBM->GetGameObject<Sprite>(10)->SetAnimation(2, 0);
	m_OBM->GetGameObject<Sprite>(10)->FixAnimation(0);

	m_OBM->GetGameObject<Sprite>(11)->SetAnimation(2, 0);
	m_OBM->GetGameObject<Sprite>(11)->FixAnimation(0);

	bgm_toggle = se_toggle = false;
	volume = 0.5f;
}

void DemoLogic_LV2::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	//std::cout << "DemoLogic_LV2 Update\n";

	BasicControl();
	SountTest();
	ToggleAnimation();
	//UnprojectSample();
	//m_OBM->GetGameScene()->GetPerspPosition();
	
	mat44 matProjection = mat44::Perspective(
		m_GSM->GetGLManager()->GetProjectionInfo().m_fovy,
		m_GSM->GetGLManager()->GetProjectionInfo().m_width / m_GSM->GetGLManager()->GetProjectionInfo().m_height,
		m_GSM->GetGLManager()->GetProjectionInfo().m_zNear,
		m_GSM->GetGLManager()->GetProjectionInfo().m_zFar).Transpose()
		* mat44::LookAt(
		vec3(m_OBM->GetGameScene()->GetCamera()),
		vec3(m_OBM->GetGameScene()->GetCamera().x, m_OBM->GetGameScene()->GetCamera().y, 0),
		vec3(cosf(Math::DegToRad((m_OBM->GetGameScene()->GetCamera().w + 90.f))),
		sinf(Math::DegToRad((m_OBM->GetGameScene()->GetCamera().w + 90.f))),
		0)).Transpose();

	mat44 matInverse = matProjection.Inverse();

	float in[4];
	float winZ = 1.0;

	in[0] = (2.f * ((float)(InputManager::GetInstance().GetRawMousePosition().x - 0) / (m_OBM->GetGSM()->GetResolution().width - 0))) - 1.0f,
		in[1] = 1.f - (2.f * ((float)(InputManager::GetInstance().GetRawMousePosition().y - 0) / (m_OBM->GetGSM()->GetResolution().height - 0)));
	in[2] = 2.f * winZ - 1.f;
	in[3] = 1.f;

	vec4 vIn = vec4(in[0], in[1], in[2], in[3]);
	vec4 pos = matInverse * vIn;

	pos.w = 1.f / pos.w;

	pos.x *= pos.w;
	pos.y *= pos.w;
	pos.z *= pos.w;
	//mat44 pos;
	//pos.SetIdentity();
	//pos.m_member[0][0] = 2.f;
	//pos.m_member[1][1] = 10.f;
	//pos.m_member[3][3] = 5.f;
	std::cout << pos << std::endl;

	//sprintf(strTitle, "%f %f %f / %f,%f,%f ", m_pCamera->m_vPosition.x, m_pCamera->m_vPosition.y, m_pCamera->m_vPosition.z, pos.x, pos.y, pos.z);

}

void DemoLogic_LV2::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "DemoLogic_LV2 Shutdown\n";
}

void DemoLogic_LV2::Unload(void)
{
	std::cout << "DemoLogic_LV2 Unload\n";	
}

void DemoLogic_LV2::BasicControl(void)
{
	if (InputManager::GetInstance().KeyTriggered(KEY_ESC))
		m_GSM->SetQuit(true);

	else if (InputManager::GetInstance().KeyTriggered(KEY_1))
		m_GSM->SetNextStage(ST_LV1);

	else if (InputManager::GetInstance().KeyPressed(KEY_2))
		m_GSM->SetNextStage(ST_LV2);

	else if (InputManager::GetInstance().KeyTriggered(KEY_3))
		m_GSM->SetNextStage(ST_LV3);

	else if (InputManager::GetInstance().KeyTriggered(KEY_0))
		m_GSM->SetNextStage(ST_MENU);

	else if (InputManager::GetInstance().KeyTriggered(KEY_R))
		m_GSM->Restart(true);

	if (InputManager::GetInstance().KeyTriggered(KEY_P))
		m_GSM->Pause();
}

void DemoLogic_LV2::SountTest(void)
{
	if (InputManager::GetInstance().KeyTriggered(KEY_UP))
	{
		volume += 0.1f;
		if (volume > 1) volume = 1;
		m_OBM->GetGameSound()->SetMasterVolume(volume);
	}

	if (InputManager::GetInstance().KeyTriggered(KEY_DOWN))
	{
		volume -= 0.1f;
		if (volume < 0) volume = 0;
		m_OBM->GetGameSound()->SetMasterVolume(volume);
	}

	if (InputManager::GetInstance().KeyTriggered(KEY_SPACE))
		m_OBM->GetGameSound()->SetMasterMuteToggle(true);

	if (InputManager::GetInstance().KeyTriggered(KEY_ENTER))
		m_OBM->GetGameSound()->SetMasterMuteToggle(false);

	m_OBM->GetGameObject<Text>(15)->SetText("Sound Volume: %.1f", volume);
}

void DemoLogic_LV2::ToggleAnimation(void)
{
	m_OBM->GetGameScene()->GetOrthoPosition();
	vec3 mouse_pos = InputManager::GetInstance().GetOrthoPosition();
	m_OBM->GetGameObject<Text>(12)->SetPosition(mouse_pos);

	if (InputManager::GetInstance().KeyTriggered(MOUSE_LEFT))
	{
		if (m_OBM->GetGameObject<Sprite>(12)->GetRigidBody()->IsCollisionWith(
			m_OBM->GetGameObject<Sprite>(10)))
		{
			if (!bgm_toggle)
			{
				m_OBM->GetGameObject<Text>(13)->SetText("Stop BGM");
				m_OBM->GetGameSound()->PlayBGM(0);
				bgm_toggle = true;
				m_OBM->GetGameObject<Sprite>(10)->FixAnimation(1);
			}

			else
			{
				m_OBM->GetGameObject<Text>(13)->SetText("Play BGM");
				m_OBM->GetGameSound()->StopBGM();
				bgm_toggle = false;
				m_OBM->GetGameObject<Sprite>(10)->FixAnimation(0);
			}
		}

		else if (m_OBM->GetGameObject<Sprite>(12)->GetRigidBody()->IsCollisionWith(
			m_OBM->GetGameObject<Sprite>(11)))
		{
			if (!se_toggle)
			{
				m_OBM->GetGameObject<Text>(14)->SetText("Stop Sound effect");
				m_OBM->GetGameSound()->PlaySE(1);
				se_toggle = true;
				m_OBM->GetGameObject<Sprite>(11)->FixAnimation(1);
			}

			else
			{
				m_OBM->GetGameObject<Text>(14)->SetText("Play Sound effect");
				m_OBM->GetGameSound()->StopSE();
				se_toggle = false;
				m_OBM->GetGameObject<Sprite>(11)->FixAnimation(0);
			}
		}
	}
}

void DemoLogic_LV2::UnprojectSample(void)
{
	glViewport(0, 0, 
		GLsizei(m_OBM->GetGSM()->GetGLManager()->GetProjectionInfo().m_width),
		GLsizei(m_OBM->GetGSM()->GetGLManager()->GetProjectionInfo().m_height));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(m_OBM->GetGSM()->GetGLManager()->GetProjectionInfo().m_fovy,
		GLfloat(m_OBM->GetGSM()->GetGLManager()->GetProjectionInfo().m_width)/
		GLfloat(m_OBM->GetGSM()->GetGLManager()->GetProjectionInfo().m_height),
		m_OBM->GetGSM()->GetGLManager()->GetProjectionInfo().m_zNear,
		m_OBM->GetGSM()->GetGLManager()->GetProjectionInfo().m_zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLint realy;
	GLdouble wx, wy, wz;

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	GLdouble modelview[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

	GLdouble projection[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	realy = viewport[3] - GLint(InputManager::GetInstance().GetRawMousePosition().y) - 1;
	gluUnProject(GLdouble(InputManager::GetInstance().GetRawMousePosition().x),
		GLdouble(realy), 1.0, modelview, projection, viewport, &wx, &wy, &wz);

	std::cout << wx << ", " << wy << ", " << wz << std::endl;
}