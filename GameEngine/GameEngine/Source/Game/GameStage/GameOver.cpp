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

	//Bind basic systems
	m_OBM.BindGameSystem(m_GSM);

	// Load json data
	m_OBM.LoadStageData("Resource/Data/GameOver.json");
}

void GameOverStage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "GameOverStage::Init\n";

	// Init basic systems
	m_OBM.InitGameSystem(gd);
}

void GameOverStage::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "GameOverStage::Update\n";

	// Update basic systems
	m_OBM.UpdateGameSystem(gd);
}

void GameOverStage::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "GameOverStage::Shutdown\n";

	// Shutdown basic systems
	m_OBM.ShutdownGameSystem(gd);

	// Cleare all Objects of the list
	m_OBM.ClearObjectList();
}

void GameOverStage::Unload(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "GameOverStage::Unload\n";

	// Unload stage data
	m_OBM.UnloadStageData();
}
