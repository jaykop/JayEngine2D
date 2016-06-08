#include "BaseStage/BaseEnigne.h"
#include "GameOver.h"

GameOverStage::GameOverStage(GameStateManager* gsm, InputManager* im)
{
	m_GSM = gsm;
	m_IM = im;
}

GameOverStage::~GameOverStage()
{

}

void GameOverStage::Init()
{
	DEBUG_PRINT("GameOverStage::Init\n");
	DEBUG_PRINT("[Instruction]\nPress 0: Main Menu\n"
		"Press 1: ST_LV1\nPress 2: ST_LV2\nPress 3: ST_LV3\nPress ESC: Quit App\n");
}

void GameOverStage::Update()
{
	DEBUG_PRINT("GameOverStage::Update\n");

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

void GameOverStage::Shutdown()
{
	DEBUG_PRINT("GameOverStage::Shutdown\n");
}