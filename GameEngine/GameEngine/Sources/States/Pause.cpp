#include "BaseStage/BaseEnigne.h"
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
}

void PauseStage::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "PauseStage::Update\n";

	//if (InputManager::GetInstance().KeyPressed(KEY_ESC))
	//	m_GSM->SetQuit(true);

	if (InputManager::GetInstance().KeyPressed(KEY_ESC))
		m_GSM->Resume();

}

void PauseStage::Shutdown()
{
	std::cout << "PauseStage::Shutdown\n";
}