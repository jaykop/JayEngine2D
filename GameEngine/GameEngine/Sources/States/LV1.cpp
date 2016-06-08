#include "BaseStage/BaseEnigne.h"
#include "LV1.h"

LV1Stage::LV1Stage(GameStateManager* gsm, InputManager* im)
{
	m_GSM = gsm;
	m_IM = im;
}

LV1Stage::~LV1Stage()
{

}

void LV1Stage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv1Stage::Init\n";
}

void LV1Stage::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv1Stage::Update\n";

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

}

void LV1Stage::Shutdown()
{
	std::cout << "Lv1Stage::Shutdown\n";
}