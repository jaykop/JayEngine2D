#include "LV2.h"
#include "../BaseData/BaseEnigne.h"
#include "../GameLogic/SampleLogic.h"

LV2Stage::LV2Stage(GameStateManager* gsm)
{
	m_GSM = gsm;
}

LV2Stage::~LV2Stage()
{

}

void LV2Stage::Load(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "LV2Stage::Load\n";
	
	// Bind game system
	m_OBM.BindGameSystem(m_GSM);

	// Load json data
	m_OBM.LoadStageData("Resource/Data/Sample.json");
}

void LV2Stage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv2Stage::Init\n";

	// Init game systems; 
	m_OBM.InitGameSystem(gd);

	// Testing ini...
	iniWritter writter("Resource/Data/Sample.ini");
	writter.WriteInt("Setting", "Age", 24);
	writter.WriteFloat("Setting", "Grade", 3.14159f);
	writter.WriteBool("Setting", "Marriage", false);
	writter.WriteString("Setting", "Name", "jaykop");
	writter.WriteVec3("Setting", "Position", vec3(10, 214, 43));
	writter.WriteVec4("Setting", "Color", vec4(63, 57, 14, 53));

	iniReader reader("Resource/Data/Sample.ini");
	int age = reader.ReadInt("Setting", "Age");
	float grade = reader.ReadFloat("Setting", "Grade");
	bool marriage = reader.ReadBool("Setting", "Marriage");
	char* name = reader.ReadString("Setting", "Name");
	vec3 position = reader.ReadVec3("Setting", "Position");
	vec4 color = reader.ReadVec4("Setting", "Color");

	std::cout << age << "\n" <<
		grade << "\n" <<
		marriage << "\n";
	std::cout << position << "\n";
	std::cout << color << "\n";
	std::wcout << name << "\n";

	//m_OBM.GetGameObject<Sprite>(0)->SetColor(vec4(0, 0, 1, 0));
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

	else if (InputManager::GetInstance().KeyTriggered(KEY_SPACE))
		m_OBM.GetGameObject<Sprite>(0)->RemoveLogic<SampleLogic>();

	m_OBM.UpdateGameSystem(gd);
}

void LV2Stage::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv2Stage::Shutdown\n";
	m_OBM.ShutdownGameSystem(gd);
	m_OBM.ClearObjectList();
}

void LV2Stage::Unload(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "LV2Stage::Unload\n";

	m_OBM.UnloadStageData();
}
