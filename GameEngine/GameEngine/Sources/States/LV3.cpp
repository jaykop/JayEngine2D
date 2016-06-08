#include "BaseStage\BaseEnigne.h"
#include "LV3.h"

LV3Stage::LV3Stage(GameStateManager* gsm, InputManager* im)
{
	m_GSM = gsm;
	m_IM = im;
}

LV3Stage::~LV3Stage()
{

}

void LV3Stage::Init()
{
	DEBUG_PRINT("Lv3Stage::Init\n");
}

void LV3Stage::Update()
{
	DEBUG_PRINT("Lv3Stage::Update\n");
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

void LV3Stage::Shutdown()
{
	DEBUG_PRINT("Lv3Stage::Shutdown\n");
}