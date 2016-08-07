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
	// m_OBM.LoadStageData("Resource/Data/Sample.json");
}

void PauseStage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "PauseStage::Init\n";

	std::cout << "[Instruction]\n"
		"Press P: Go back to Last stage\n ESC: Quit the App\n";

	std::cout << "You can control the White box with keyboard arrows!\n";
	
	m_OBM.InitGameSystem(gd);
}

void PauseStage::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	//std::cout << "PauseStage::Update\n";

	if (InputManager::GetInstance().KeyTriggered(KEY_ESC))
		m_GSM->SetQuit(true);

	if (InputManager::GetInstance().KeyTriggered(KEY_P))
		m_GSM->Resume();

	m_OBM.UpdateGameSystem(gd);
}

void PauseStage::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "PauseStage::Shutdown\n";
	m_OBM.ShutdownGameSystem(gd);
}

void PauseStage::Unload(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "PauseStage::Unload\n";
	// m_OBM.UnloadStageData();
}
