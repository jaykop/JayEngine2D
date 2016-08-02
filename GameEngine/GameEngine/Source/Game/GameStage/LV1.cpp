#include "../BaseData/BaseEnigne.h"
#include "LV1.h"

LV1Stage::LV1Stage(GameStateManager* gsm)
{
	m_GSM = gsm;
}

LV1Stage::~LV1Stage()
{

}

void LV1Stage::Load(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "LV1Stage::Load\n";

	//Bind basic systems
	m_OBM.BindGameSystem(m_GSM);
}

void LV1Stage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv1Stage::Init\n";
	std::cout << "Sound testing here.\n";

	// Here objects to be init...

	m_OBM.InitGameSystem(gd);
}

void LV1Stage::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	//std::cout << "Lv1Stage::Update\n";

	static float volume = 0.5f;

	m_OBM.UpdateGameSystem(gd);

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
		m_OBM.GetGameSound()->SetMasterVolume(volume);
	}

	if (InputManager::GetInstance().KeyTriggered(KEY_DOWN))
	{
		volume -= 0.1f;
		if (volume < 0) volume = 0;
		m_OBM.GetGameSound()->SetMasterVolume(volume);
	}

	if (InputManager::GetInstance().KeyTriggered(KEY_A))
		m_OBM.GetGameSound()->PlayBGM(SE_1);

	if (InputManager::GetInstance().KeyTriggered(KEY_S))
		m_OBM.GetGameSound()->StopBGM();

	if (InputManager::GetInstance().KeyTriggered(KEY_Z))
		m_OBM.GetGameSound()->PlaySE(SE_2);

	if (InputManager::GetInstance().KeyTriggered(KEY_X))
		m_OBM.GetGameSound()->StopSE();

	if (InputManager::GetInstance().KeyTriggered(KEY_SPACE))
		m_OBM.GetGameSound()->SetMasterMuteToggle(true);

	if (InputManager::GetInstance().KeyTriggered(KEY_ENTER))
		m_OBM.GetGameSound()->SetMasterMuteToggle(false);

}

void LV1Stage::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv1Stage::Shutdown\n";
	m_OBM.ShutdownGameSystem(gd);
}

void LV1Stage::Unload(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "LV1Stage::Unload\n";
}
