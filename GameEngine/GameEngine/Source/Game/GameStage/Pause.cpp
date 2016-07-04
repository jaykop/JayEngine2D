#include "../BaseData/BaseEnigne.h"
#include "Pause.h"

PauseStage::PauseStage(GameStateManager* gsm)
{
	m_GSM = gsm;
}

PauseStage::~PauseStage()
{

}

void PauseStage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "PauseStage::Init\n";

	std::cout << "[Instruction]\n"
		"Press P: Go back to Last stage\n ESC: Quit the App\n";

	std::cout << "You can control the White box with keyboard arrows!\n";
	
	m_OBM.BindGameSystem(m_GSM);
	m_OBM.InitGameSystem();
}

void PauseStage::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	//std::cout << "PauseStage::Update\n";

	if (InputManager::GetInstance().KeyTriggered(KEY_ESC))
		m_GSM->SetQuit(true);

	if (InputManager::GetInstance().KeyTriggered(KEY_P))
		m_GSM->Resume();

	m_OBM.UpdateGameSystem();
}

void PauseStage::Shutdown()
{
	std::cout << "PauseStage::Shutdown\n";
	m_OBM.ShutdownGameSystem();
}