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
	std::cout << "DemoLogic_LV2 Update\n";

	BasicControl();
	SountTest();
	ToggleAnimation();
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

	if (InputManager::GetInstance().KeyPressed(MOUSE_LEFT))
	{
		if (m_OBM->GetGameObject<Sprite>(12)->GetRigidBody()->IsCollisionWith(
			m_OBM->GetGameObject<Sprite>(10)))
		{
			if (!bgm_toggle)
			{
				m_OBM->GetGameObject<Text>(13)->SetText("Play BGM");
				m_OBM->GetGameSound()->PlayBGM(0);
				bgm_toggle = true;		
			}

			else
			{
				m_OBM->GetGameObject<Text>(13)->SetText("Stop BGM");
				m_OBM->GetGameSound()->StopBGM();
				bgm_toggle = false;
			}
		}

		else if (m_OBM->GetGameObject<Sprite>(12)->GetRigidBody()->IsCollisionWith(
			m_OBM->GetGameObject<Sprite>(11)))
		{
			if (!se_toggle)
			{
				m_OBM->GetGameObject<Text>(13)->SetText("Play Sound effect");
				m_OBM->GetGameSound()->PlaySE(1);
				bgm_toggle = true;
			}

			else
			{
				m_OBM->GetGameObject<Text>(13)->SetText("Stop Sound effect");
				m_OBM->GetGameSound()->StopSE();
				bgm_toggle = false;
			}
		}
	}
}