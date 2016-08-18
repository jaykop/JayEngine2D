#include "DemoLogic_GameOver.h"
#include "../BaseData/BaseEnigne.h"

GameLogic* DemoLogic_GameOverBuilder::BuildLogic(Object* Owner) const
{
	return new DemoLogic_GameOver(Owner);
}

DemoLogic_GameOver::DemoLogic_GameOver(Object* owner)
: m_Owner(owner), m_OBM(owner->GetOBM()), m_GSM(owner->GetOBM()->GetGSM())
{}

void DemoLogic_GameOver::Load(const Json::Value& data)
{
	UNREFERENCED_PARAMETER(data);
	std::cout << "SanpleLogic Load\n";
}

void DemoLogic_GameOver::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "SanpleLogic Inited\n";
}

void DemoLogic_GameOver::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "SanpleLogic Update\n";

	BasicControl();
}

void DemoLogic_GameOver::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "SanpleLogic Shutdown\n";
}

void DemoLogic_GameOver::Unload(void)
{
	std::cout << "SanpleLogic Unload\n";
}

void DemoLogic_GameOver::BasicControl(void)
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