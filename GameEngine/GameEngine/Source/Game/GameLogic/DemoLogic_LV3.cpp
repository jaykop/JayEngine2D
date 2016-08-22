#include "DemoLogic_LV3.h"
#include "../BaseData/BaseEnigne.h"

GameLogic* DemoLogic_LV3Builder::BuildLogic(Object* Owner) const
{
	return new DemoLogic_LV3(Owner);
}

DemoLogic_LV3::DemoLogic_LV3(Object* owner)
: m_Owner(owner), m_OBM(owner->GetOBM()), m_GSM(owner->GetOBM()->GetGSM())
{}

void DemoLogic_LV3::Load(const Json::Value& data)
{
	UNREFERENCED_PARAMETER(data);
	std::cout << "DemoLogic_LV3 Load\n";
}

void DemoLogic_LV3::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "DemoLogic_LV3 Inited\n";

	dt_Stack = 0.f;
}

void DemoLogic_LV3::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "DemoLogic_LV3 Update\n";

	BasicControl();
	LightControl();
	ParticleExplosion(gd.dt);
}

void DemoLogic_LV3::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "DemoLogic_LV3 Shutdown\n";
}

void DemoLogic_LV3::Unload(void)
{
	std::cout << "DemoLogic_LV3 Unload\n";	
}

void DemoLogic_LV3::BasicControl(void)
{
	if (InputManager::GetInstance().KeyTriggered(KEY_ESC))
		m_GSM->SetQuit(true);

	else if (InputManager::GetInstance().KeyTriggered(KEY_1))
		m_GSM->SetNextStage(ST_LV1);

	else if (InputManager::GetInstance().KeyPressed(KEY_2))
		m_GSM->SetNextStage(ST_LV2);

	else if (InputManager::GetInstance().KeyTriggered(KEY_3))
		m_GSM->SetNextStage(ST_LV3);

	else if (InputManager::GetInstance().KeyTriggered(KEY_4))
		m_GSM->SetNextStage(ST_GAMEOVER);

	else if (InputManager::GetInstance().KeyTriggered(KEY_0))
		m_GSM->SetNextStage(ST_MENU);

	else if (InputManager::GetInstance().KeyTriggered(KEY_R))
		m_GSM->Restart(true);

	if (InputManager::GetInstance().KeyTriggered(KEY_P))
		m_GSM->Pause();
}

void DemoLogic_LV3::LightControl(void)
{
	m_OBM->GetGameObject<Light>(17)->SetPosition(vec3(
		InputManager::GetInstance().GetPerspPosition().x,
		InputManager::GetInstance().GetPerspPosition().y,
		m_OBM->GetGameObject<Light>(17)->GetPosition().z));

	if (InputManager::GetInstance().KeyTriggered(MOUSE_LEFT))
	{
		if (m_OBM->HasObject(18))
		{
			m_OBM->RemoveObject(18);
			m_OBM->GetGameObject<Light>(17)->SetDiffuse(vec3(1.f, 1.f, 1.f));
		}

		else if (!m_OBM->HasObject(18))
		{
			m_OBM->AddObject(new Darkness(18, m_OBM));
			m_OBM->GetGameObject<Darkness>(18)->SetTexture(m_GSM->GetGLManager()->GetTexture(0));
			m_OBM->GetGameObject<Light>(17)->SetDiffuse(vec3());
		}
	}
}

void DemoLogic_LV3::ParticleExplosion(float dt)
{
	// Refresh explosion
	dt_Stack += dt;
	if (dt_Stack > 3.f)
	{
		m_OBM->GetGameObject<Emitter>(12)->ActivateExplosion(true);
		dt_Stack = 0.f;
	}
}