#include "../BaseData/BaseEnigne.h"
#include "Pause.h"

PauseStage::PauseStage(GameStateManager* gsm)
{
	m_GSM = gsm;
}

PauseStage::~PauseStage()
{

}

void PauseStage::Load(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "PauseStage::Load\n";

	// Bind basic systems
	m_OBM.BindGameSystem(m_GSM);
	
	// Load json data
	m_OBM.LoadStageData("Resource/Data/Pause.json");
}

void PauseStage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "PauseStage::Init\n";

	// Init basic systems
	m_OBM.InitGameSystem(gd);
}

void PauseStage::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "PauseStage::Update\n";

	if (InputManager::GetInstance().KeyTriggered(KEY_ESC))
		m_GSM->SetQuit(true);

	if (InputManager::GetInstance().KeyTriggered(KEY_P))
		m_GSM->Resume();

	// Update basic systems
	m_OBM.UpdateGameSystem(gd);
}

void PauseStage::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "PauseStage::Shutdown\n";

	// Shutdown basic systems
	m_OBM.ShutdownGameSystem(gd);

	// Cleare all Objects of the list
	m_OBM.ClearObjectList();
}

void PauseStage::Unload(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "PauseStage::Unload\n";
	
	// Unload stage data
	m_OBM.UnloadStageData();
}
