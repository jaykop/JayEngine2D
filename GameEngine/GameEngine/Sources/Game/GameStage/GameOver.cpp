#include "../BaseData/BaseEnigne.h"
#include "GameOver.h"

GameOverStage::GameOverStage(GameStateManager* gsm)
{
	m_GSM = gsm;
}

GameOverStage::~GameOverStage()
{

}

void GameOverStage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "GameOverStage::Init\n";
}

void GameOverStage::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "GameOverStage::Update\n";

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

void GameOverStage::Shutdown()
{
	DEBUG_PRINT("GameOverStage::Shutdown\n");
}