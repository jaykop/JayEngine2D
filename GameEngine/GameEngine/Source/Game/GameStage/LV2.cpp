#include "../BaseData/BaseEnigne.h"
#include "LV2.h"

LV2Stage::LV2Stage(GameStateManager* gsm)
{
	m_GSM = gsm;
}

LV2Stage::~LV2Stage()
{

}

void LV2Stage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv2Stage::Init\n";
}

void LV2Stage::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv2Stage::Update\n";

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
}

void LV2Stage::Shutdown()
{
	std::cout << "Lv2Stage::Shutdown\n";
}