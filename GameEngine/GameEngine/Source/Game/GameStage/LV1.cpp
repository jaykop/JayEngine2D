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
	//std::cout << "Lv1Stage::Update\n";

	static float volume = 0.5f;

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

	if (InputManager::GetInstance().KeyTriggered(KEY_UP))
	{
		volume += 0.1f;
		if (volume > 1) volume = 1;
		m_ObjM.GetGameSound()->SetMasterVolume(volume);
	}

	if (InputManager::GetInstance().KeyTriggered(KEY_DOWN))
	{
		volume -= 0.1f;
		if (volume < 0) volume = 0;
		m_ObjM.GetGameSound()->SetMasterVolume(volume);
	}

	if (InputManager::GetInstance().KeyTriggered(KEY_A))
		m_ObjM.GetGameSound()->PlayBGM(SE_1);

	if (InputManager::GetInstance().KeyTriggered(KEY_S))
		m_ObjM.GetGameSound()->StopBGM();

	if (InputManager::GetInstance().KeyTriggered(KEY_Z))
		m_ObjM.GetGameSound()->PlaySE(SE_2);

	if (InputManager::GetInstance().KeyTriggered(KEY_X))
		m_ObjM.GetGameSound()->StopSE();

	if (InputManager::GetInstance().KeyTriggered(KEY_SPACE))
		m_ObjM.GetGameSound()->SetMasterMuteToggle(true);

	if (InputManager::GetInstance().KeyTriggered(KEY_ENTER))
		m_ObjM.GetGameSound()->SetMasterMuteToggle(false);

}

void LV1Stage::Shutdown()
{
	std::cout << "Lv1Stage::Shutdown\n";
	m_ObjM.ShutdownGameSystem();
}