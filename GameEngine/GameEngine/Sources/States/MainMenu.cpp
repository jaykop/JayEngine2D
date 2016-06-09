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
	
	//New scene(for graphic)
	m_scene = new Scene;

	//New world(for physics)
	m_world = new World;

	//Set sprites
	m_ObjM.AddObject("sample1");
	m_ObjM.AddObject("sample2");
	m_ObjM.AddObject("sample3");
	m_ObjM.AddObject("sample4");
	m_ObjM.AddObject("sample5");

	m_ObjM.GetGameObject(0)->SetPosition(vec3(0, 0));
	m_ObjM.GetGameObject(1)->SetPosition(vec3(-10, 0));
	m_ObjM.GetGameObject(2)->SetPosition(vec3(0, 10));
	m_ObjM.GetGameObject(3)->SetPosition(vec3(0, -10));
	m_ObjM.GetGameObject(4)->SetPosition(vec3(10, 0));

	m_ObjM.GetGameObject(0)->SetColor(vec4(1, 1, 1, 1));
	m_ObjM.GetGameObject(1)->SetColor(vec4(0, 0, 1, 1));
	m_ObjM.GetGameObject(2)->SetColor(vec4(1, 0, 0, 1));
	m_ObjM.GetGameObject(3)->SetColor(vec4(0, 1, 0, 1));
	m_ObjM.GetGameObject(4)->SetColor(vec4(1, 1, 0, 1));

	m_ObjM.GetGameObject(0)->BindRigidBody();
	//m_ObjM.GetGameObject(1)->BindRigidBody();
	m_ObjM.GetGameObject(2)->BindRigidBody();
	//m_ObjM.GetGameObject(3)->BindRigidBody();
	m_ObjM.GetGameObject(4)->BindRigidBody();

	//Init Animation variables
	m_posx = m_posy = 0.f;
	speed = 1.f;

	m_scene->Init();
}

void MenuStage::Update(GameData& gd)
{	
	UNREFERENCED_PARAMETER(gd);
	//std::cout << "MenuStage::Update\n";

	BasicControl();
	SampleAnimation();
	
	m_world->Update(m_ObjM);
	m_scene->Draw(m_ObjM);
}

void MenuStage::Shutdown()
{
	std::cout << "MenuStage::Shutdown\n";

	m_ObjM.ClearObjectList();

	//This does nothing
	m_scene->Shutdown();

	delete m_scene;
	delete m_world;
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
	m_posx = m_ObjM.GetGameObject(0)->GetPosition().x;
	m_posy = m_ObjM.GetGameObject(0)->GetPosition().y;

	//Control Redbox with keyboard
	if (InputManager::GetInstance().KeyPressed(KEY_RIGHT))
		m_posx += speed;

	if (InputManager::GetInstance().KeyPressed(KEY_LEFT))
		m_posx -= speed;

	if (InputManager::GetInstance().KeyPressed(KEY_UP))
		m_posy += speed;

	if (InputManager::GetInstance().KeyPressed(KEY_DOWN))
		m_posy -= speed;

	m_ObjM.GetGameObject(0)->SetPosition(vec3(m_posx, m_posy, 0));

	if (InputManager::GetInstance().KeyTriggered(KEY_K))
		std::cout << "???" << "\n";

	if (InputManager::GetInstance().KeyTriggered(KEY_K))
		std::cout << "!!!" << "\n";
}