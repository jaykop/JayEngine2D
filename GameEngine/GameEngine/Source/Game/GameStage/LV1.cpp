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

	// Load json data
	m_OBM.LoadStageData("Resource/Data/LV1.json");
}

void LV1Stage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv1Stage::Init\n";

	// Init basic systems
	m_OBM.InitGameSystem(gd);
}

void LV1Stage::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv1Stage::Update\n";	

	// Update basic systems
	m_OBM.UpdateGameSystem(gd);
}

void LV1Stage::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "Lv1Stage::Shutdown\n";

	// Shutdown basic systems
	m_OBM.ShutdownGameSystem(gd);

	// Cleare all Objects of the list
	m_OBM.ClearObjectList();
}

void LV1Stage::Unload(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "LV1Stage::Unload\n";

	// Unload stage data
	m_OBM.UnloadStageData();
}
