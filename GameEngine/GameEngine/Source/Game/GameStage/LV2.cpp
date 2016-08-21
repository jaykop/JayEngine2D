#include "LV2.h"
#include "../BaseData/BaseEnigne.h"
#include "../GameLogic/DemoLogic_LV2.h"

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
	m_OBM.LoadStageData("Resource/Data/LV2.json");
}

void LV2Stage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv2Stage::Init\n";

	// Init game systems; 
	m_OBM.InitGameSystem(gd);
}

void LV2Stage::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv2Stage::Update\n";

	// Update basic systems
	m_OBM.UpdateGameSystem(gd);
}

void LV2Stage::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv2Stage::Shutdown\n";

	// Shutdown basic systems
	m_OBM.ShutdownGameSystem(gd);

	// Cleare all Objects of the list
	m_OBM.ClearObjectList();
}

void LV2Stage::Unload(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "LV2Stage::Unload\n";

	// Unload stage data
	m_OBM.UnloadStageData();
}
