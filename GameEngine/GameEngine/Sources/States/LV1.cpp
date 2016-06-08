#include "BaseStage/BaseEnigne.h"
#include "LV1.h"

LV1Stage::LV1Stage(GameStateManager* gsm, InputManager* im)
{
	m_GSM = gsm;
	m_IM = im;
}

LV1Stage::~LV1Stage()
{

}

void LV1Stage::Init()
{
	DEBUG_PRINT("Lv1Stage::Init\n");

	//Obsever Pattern Test
	/*CS = new ConcreteSubject();
	o1 = new ConcreteObserverA(CS);
	o2 = new ConcreteObserverB(CS);

	CS->SetStatus(10, 20, 30);
	CS->notify();

*/

}

void LV1Stage::Update()
{
	//DEBUG_PRINT("Lv1Stage::Update\n");
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
}

void LV1Stage::Shutdown()
{
	DEBUG_PRINT("Lv1Stage::Shutdown\n");
}