#include "../BaseData/BaseEnigne.h"
#include "GameOver.h"

GameOverStage::GameOverStage(GameStateManager* gsm)
{
	m_GSM = gsm;
}

GameOverStage::~GameOverStage()
{

}

void GameOverStage::Load(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "GameOverStage::Load\n";

	m_OBM.BindGameSystem(m_GSM);
}

void GameOverStage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "GameOverStage::Init\n";

	m_OBM.InitGameSystem(gd);
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

	m_OBM.UpdateGameSystem(gd);
}

void GameOverStage::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	DEBUG_PRINT("GameOverStage::Shutdown\n");

	m_OBM.ShutdownGameSystem(gd);
}

void GameOverStage::Unload(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "GameOverStage::Unload\n";

	m_OBM.UnloadStageData();
}
