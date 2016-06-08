#include "BaseStage/BaseEnigne.h"
#include "MainMenu.h"

MenuStage::MenuStage(GameStateManager* gsm, InputManager* im)
{
	m_GSM = gsm;
	m_IM = im;
}

MenuStage::~MenuStage()
{

}

void MenuStage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "MenuStage::Init\n";
	std::cout << "[Instruction]\nPress 0: Main Menu\n"
		"Press 1: ST_LV1\nPress 2: ST_LV2\nPress 3: ST_LV3\nPress ESC: Quit the App\n";
	
	std::cout << "You can control the red box with keyboard arrows!\n";
	
	//New scene
	m_scene = new Scene;

	//Set sprites
	m_ObjM.AddObject("sample");

	//Init Animation variables
	scale = true;
	m_posx = m_posy = offset = degree = 0, m_scl = speed = 1.f;

	m_scene->Init();
}

void MenuStage::Update(GameData& gd)
{	
	UNREFERENCED_PARAMETER(gd);
	//std::cout << "MenuStage::Update\n";

	BasicControl();
	SampleAnimation();
	m_ObjM.GetGameObject(0)->SetColor(vec4(1,0,0,.5f));
	m_scene->Draw(m_ObjM);
}

void MenuStage::Shutdown()
{
	std::cout << "MenuStage::Shutdown\n";

	m_ObjM.ClearObjectList();

	//This does nothing
	m_scene->Shutdown();

	delete m_scene;
}

void MenuStage::BasicControl(void)
{
	static bool test = false;

	if (InputManager::GetInstance().KeyTriggered(KEY_ESC))
		m_GSM->SetQuit(true);

	else if (InputManager::GetInstance().KeyTriggered(KEY_1))
		m_GSM->SetNextStage(ST_LV1);

	else if (InputManager::GetInstance().KeyPressed(KEY_2))
		m_GSM->SetNextStage(ST_LV2);

	else if (InputManager::GetInstance().KeyTriggered(KEY_3))
		m_GSM->SetNextStage(ST_LV3);

	else if (InputManager::GetInstance().KeyTriggered(KEY_0))
		m_GSM->SetNextStage(ST_MENU);
}

void MenuStage::SampleAnimation(void)
{
	//Control Redbox with keyboard
	if (InputManager::GetInstance().KeyPressed(KEY_RIGHT))
		m_posx += speed;

	if (InputManager::GetInstance().KeyPressed(KEY_LEFT))
		m_posx -= speed;

	if (InputManager::GetInstance().KeyPressed(KEY_UP))
		m_posy += speed;

	if (InputManager::GetInstance().KeyPressed(KEY_DOWN))
		m_posy -= speed;

	m_scene->SetCamera(vec3(m_posx, m_posy, -80));
}