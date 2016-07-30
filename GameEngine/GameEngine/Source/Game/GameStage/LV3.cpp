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
}

void LV3Stage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv3Stage::Init\n";
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
}

void LV3Stage::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv3Stage::Shutdown\n";
}

void LV3Stage::Unload(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "LV3Stage::Unload\n";
}

void LV3Stage::LoadObjects(const wchar_t* fileName)
{

}