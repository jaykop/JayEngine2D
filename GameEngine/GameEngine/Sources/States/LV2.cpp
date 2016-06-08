#include "BaseStage/BaseEnigne.h"
#include "LV2.h"

LV2Stage::LV2Stage(GameStateManager* gsm, InputManager* im)
{
	m_GSM = gsm;
	m_IM = im;
}

LV2Stage::~LV2Stage()
{

}

void LV2Stage::Init()
{
	DEBUG_PRINT("Lv2Stage::Init\n");
}

void LV2Stage::Update()
{
	DEBUG_PRINT("Lv2Stage::Update\n");
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

void LV2Stage::Shutdown()
{
	DEBUG_PRINT("Lv2Stage::Shutdown\n");
}