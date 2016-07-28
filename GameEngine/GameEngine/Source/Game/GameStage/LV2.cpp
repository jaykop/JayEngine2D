#include "../BaseData/BaseEnigne.h"
#include "LV2.h"

LV2Stage::LV2Stage(GameStateManager* gsm)
{
	m_GSM = gsm;
}

LV2Stage::~LV2Stage()
{

}

void LV2Stage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv2Stage::Init\n";

	iniWritter writter(L"Resource/Data/Sample.ini");
	writter.WriteInt(L"Setting", L"Age", 24);
	writter.WriteFloat(L"Setting", L"Grade", 3.14159f);
	writter.WriteBool(L"Setting", L"Marriage", false);
	writter.WriteString(L"Setting", L"Name", L"jaykop");

	iniReader reader(L"Resource/Data/Sample.ini");
	int age = reader.ReadInt(L"Setting", L"Age", 24);
	float grade = reader.ReadFloat(L"Setting", L"Grade", 3.14159f);
	bool marriage = reader.ReadBool(L"Setting", L"Marriage", false);
	wchar_t* name = reader.ReadString(L"Setting", L"Name", L"jaykop");

	std::cout << age << "\n" <<
		grade << "\n" <<
		marriage << "\n";
	std::wcout << name << "\n";
}

void LV2Stage::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	//std::cout << "Lv2Stage::Update\n";

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

void LV2Stage::Shutdown()
{
	std::cout << "Lv2Stage::Shutdown\n";
}