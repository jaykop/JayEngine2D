#include "../BaseData/BaseEnigne.h"
#include "LV3.h"

LV3Stage::LV3Stage(GameStateManager* gsm)
{
	m_GSM = gsm;
}

LV3Stage::~LV3Stage()
{

}

void LV3Stage::Load(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "LV3Stage::Load\n";

	//Bind basic systems
	m_OBM.BindGameSystem(m_GSM);

	// Load json data
	m_OBM.LoadStageData("Resource/Data/LV3.json");
}

void LV3Stage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv3Stage::Init\n";

	// Init game systems; 
	m_OBM.InitGameSystem(gd);
}

void LV3Stage::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv3Stage::Update\n";

	// Update basic systems
	m_OBM.UpdateGameSystem(gd);
}

void LV3Stage::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv3Stage::Shutdown\n";

	// Shutdown basic systems
	m_OBM.ShutdownGameSystem(gd);

	// Cleare all Objects of the list
	m_OBM.ClearObjectList();
}

void LV3Stage::Unload(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "LV3Stage::Unload\n";

	// Unload stage data
	m_OBM.UnloadStageData();
}
