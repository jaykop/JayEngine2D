#include "LV2.h"
#include "../BaseData/BaseEnigne.h"

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
	
	m_OBM.BindGameSystem(m_GSM);
}

void LV2Stage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv2Stage::Init\n";

	// Testing ini...
	iniWritter writter(L"Resource/Data/Sample.ini");
	writter.WriteInt(L"Setting", L"Age", 24);
	writter.WriteFloat(L"Setting", L"Grade", 3.14159f);
	writter.WriteBool(L"Setting", L"Marriage", false);
	writter.WriteString(L"Setting", L"Name", L"jaykop");
	writter.WriteVec3(L"Setting", L"Position", vec3(10, 214, 43));
	writter.WriteVec4(L"Setting", L"Color", vec4(63, 57, 14, 53));

	iniReader reader(L"Resource/Data/Sample.ini");
	int age = reader.ReadInt(L"Setting", L"Age");
	float grade = reader.ReadFloat(L"Setting", L"Grade");
	bool marriage = reader.ReadBool(L"Setting", L"Marriage");
	wchar_t* name = reader.ReadString(L"Setting", L"Name");
	vec3 position = reader.ReadVec3(L"Setting", L"Position");
	vec4 color = reader.ReadVec4(L"Setting", L"Color");

	std::cout << age << "\n" <<
		grade << "\n" <<
		marriage << "\n";
	std::cout << position << "\n";
	std::cout << color << "\n";
	std::wcout << name << "\n";

	// Testing json...
	m_testParser.write_sample();
	m_testParser.read_sample();

	m_OBM.InitGameSystem();
	m_testParser.LoadStage(L"Resource/Data/Sample.json", m_OBM.GetGameScene());
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

	m_OBM.UpdateGameSystem();
}

void LV2Stage::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv2Stage::Shutdown\n";
	m_OBM.ShutdownGameSystem();
}

void LV2Stage::Unload(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "LV2Stage::Unload\n";
	//delete m_Loader;
}

void LV2Stage::LoadObjects(const wchar_t* fileName)
{
	UNREFERENCED_PARAMETER(fileName);

	//m_Loader = new iniReader(L"Resource/Data/LV2.ini");

	//// Basic sprite info
	//m_Loader->ReadInt(L"Object", L"ID");
	//m_Loader->ReadVec3(L"Object", L"Position");
	//m_Loader->ReadVec3(L"Object", L"Scale");
	//m_Loader->ReadFloat(L"Object", L"Rotation");
	//m_Loader->ReadVec4(L"Object", L"Color");
	//m_Loader->ReadInt(L"Object", L"Type");
	//m_Loader->ReadInt(L"Object", L"Projection");

	// Basic body info...

	// Basic text info...

	// Basic emitter info...

}