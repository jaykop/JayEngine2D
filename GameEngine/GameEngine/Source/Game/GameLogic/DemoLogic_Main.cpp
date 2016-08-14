#include "DemoLogic_Main.h"
#include "../BaseData/BaseEnigne.h"

GameLogic* DemoLogic_MainBuilder::BuildLogic(Object* Owner) const
{
	return new DemoLogic_Main(Owner);
}

DemoLogic_Main::DemoLogic_Main(Object* owner)
: m_Owner(owner), m_OBM(owner->GetOBM()), m_GSM(owner->GetOBM()->GetGSM())
{
	color = vec4(1,1,1,1);
	rotation = m_dt = 0.f;
	position = vec3(-30.f, -30.f); scale = vec3(5.f, 5.f, 0);
	pos_toggle = false, scale_toggle = false;
	color_offset = 0;
}

void DemoLogic_Main::Load(const Json::Value& data)
{
	UNREFERENCED_PARAMETER(data);
	std::cout << "DemoLogic_Main Load\n";
}

void DemoLogic_Main::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "DemoLogic_Main Inited\n";

	deltaTime = frameCount = timeElapsed = dt_stack = 0.f;
	m_fps.StartTime();
}

void DemoLogic_Main::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	//std::cout << "DemoLogic_Main Update\n";

	BasicControl();
	MovingSprite();
	ColoredTexts(gd.dt);
	MousePosition();
	CalculateFPS(gd.dt);
}

void DemoLogic_Main::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "DemoLogic_Main Shutdown\n";
}

void DemoLogic_Main::Unload(void)
{
	std::cout << "DemoLogic_Main Unload\n";
}

void DemoLogic_Main::BasicControl(void)
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

void DemoLogic_Main::MovingSprite(void)
{
	rotation++;
	if (rotation > 360) rotation = 0;

	if (scale_toggle)
	{
		scale.x += 0.05f;
		scale.y += 0.05f;
		if (scale.x > 7.5f) scale_toggle = !scale_toggle;
	}

	else
	{
		scale.x -= 0.05f;
		scale.y -= 0.05f;
		if (scale.x < 2.5f) scale_toggle = !scale_toggle;
	}

	position.x = 10 * cos(Math::DegToRad(rotation)) + -30;
	position.y = 10 * sin(Math::DegToRad(rotation)) + -20;

	m_OBM->GetGameObject<Sprite>(10)->SetPosition(position);
	m_OBM->GetGameObject<Sprite>(10)->SetScale(scale);
	m_OBM->GetGameObject<Sprite>(10)->SetRotation(rotation);
}

void DemoLogic_Main::ColoredTexts(float dt)
{
	m_dt += dt;

	switch (color_offset)
	{
	case 0:
		color.x += 0.01f;
		color.y -= 0.01f;
		color.z -= 0.01f;
		if (m_dt > 1.f)
		{
			m_dt = 0;
			color_offset++;
		}
		break;
	case 1:
		color.x -= 0.01f;
		color.y += 0.01f;
		color.z -= 0.01f;
		if (m_dt > 1.f)
		{
			m_dt = 0;
			color_offset++;
		}
		break;
	case 2:
		color.x -= 0.01f;
		color.y -= 0.01f;
		color.z += 0.01f;
		if (m_dt > 1.f)
		{
			m_dt = 0;
			color_offset = 0;
		}
		break;
	}

	if (color.x > 1.f) color.x = 1.f;
	else if (color.x < 0.f) color.x = 0.f;
	if (color.y > 1.f) color.y = 1.f;
	else if (color.y < 0.f) color.y = 0.f;
	if (color.z > 1.f) color.z = 1.f;
	else if (color.z < 0.f) color.z = 0.f;

	m_OBM->GetGameObject<Sprite>(30)->SetColor(color);
}

void DemoLogic_Main::MousePosition(void)
{
	vec3 ortho_mpos = InputManager::GetInstance().GetOrthoPosition();
	vec3 world_mpos = InputManager::GetInstance().GetPerspPosition();
	m_OBM->GetGameObject<Text>(40)->SetPosition(ortho_mpos / 2.f);
	m_OBM->GetGameObject<Text>(40)->SetText("Ortho Position: [ %.2f, %.2f ]\nWorld Position: [ %.2f, %.2f ]", ortho_mpos.x, ortho_mpos.y, world_mpos.x, world_mpos.y);
}

void DemoLogic_Main::CalculateFPS(float dt)
{
	frameCount++;
	dt_stack += deltaTime;
	timeElapsed += dt;

	float fps = frameCount / m_fps.GetElapsedTime();
	m_OBM->GetGameObject<Text>(50)->SetText("FPS: %f\nDelta Time: %f\nTime Stack: %f", fps, deltaTime, dt_stack);
	
	if (timeElapsed >= 1.0f)
	{
		deltaTime = m_fps.GetElapsedTime() / 60.f;
		frameCount = 0;
		timeElapsed = 0.f;
		m_fps.StartTime();
	}
}