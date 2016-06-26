#include "../BaseData/BaseEnigne.h"
#include "LV1.h"

LV1Stage::LV1Stage(GameStateManager* gsm)
{
	m_GSM = gsm;
}

LV1Stage::~LV1Stage()
{

}

void LV1Stage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv1Stage::Init\n";
	std::cout << "Sound testing here.\n";

	//Init basic trunks
	m_ObjM.BindGameSystem(m_GSM);

	// Here objects to be init...

	m_ObjM.InitGameSystem();
}

void LV1Stage::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv1Stage::Update\n";

	m_ObjM.UpdateGameSystem();

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

	else if (InputManager::GetInstance().KeyTriggered(KEY_P))
		m_GSM->Pause();

	if (InputManager::GetInstance().KeyTriggered(KEY_SPACE))
		m_GSM->GetAppPtr()->GetSManager()->Play();

}

void LV1Stage::Shutdown()
{
	std::cout << "Lv1Stage::Shutdown\n";
	m_ObjM.ShutdownGameSystem();
}