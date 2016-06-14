#include "../BaseData/BaseEnigne.h"
#include "MainMenu.h"

MenuStage::MenuStage(GameStateManager* gsm)
{
	m_GSM = gsm;
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
	
	std::cout << "You can control the White box with keyboard arrows!\n";
	
	//New scene(for graphic)
	m_scene = new Scene;

	//New world(for physics)
	m_world = new World;

	//Set sprites
	m_ObjM.AddObject(0);
	m_ObjM.AddObject(1);
	//m_ObjM.AddObject(2);
	//m_ObjM.AddObject(3);
	//m_ObjM.AddObject(4);

	//Set positions
	m_ObjM.GetGameObject(0)->SetPosition(vec3(0, 20));
	//m_ObjM.GetGameObject(0)->SetRotation(45);
	m_ObjM.GetGameObject(1)->SetPosition(vec3(0, 0));
	//m_ObjM.GetGameObject(1)->SetRotation(45);
	//m_ObjM.GetGameObject(2)->SetPosition(vec3(0, 20));
	//m_ObjM.GetGameObject(2)->SetRotation(45);
	//m_ObjM.GetGameObject(3)->SetPosition(vec3(0, -20));
	//m_ObjM.GetGameObject(3)->SetRotation(45);
	//m_ObjM.GetGameObject(4)->SetPosition(vec3(20, 0));
	//m_ObjM.GetGameObject(4)->SetRotation(45);

	m_ObjM.GetGameObject(0)->SetScale(vec3(15, 15));
	m_ObjM.GetGameObject(1)->SetScale(vec3(60, 15));
	//m_ObjM.GetGameObject(2)->SetScale(vec3(800, 1));
	//m_ObjM.GetGameObject(3)->SetScale(vec3(800, 1));
	//m_ObjM.GetGameObject(4)->SetScale(vec3(1, 600));

	//Set colors
	m_ObjM.GetGameObject(0)->SetColor(vec4(1, 1, 1, 1));
	m_ObjM.GetGameObject(1)->SetColor(vec4(0, 0, 1, 1));
	//m_ObjM.GetGameObject(2)->SetColor(vec4(1, 0, 0, 1));
	//m_ObjM.GetGameObject(3)->SetColor(vec4(0, 1, 0, 1));
	//m_ObjM.GetGameObject(4)->SetColor(vec4(1, 1, 0, 1));

	//Bind rigid body
	m_ObjM.GetGameObject(0)->BindRigidBody();
	m_ObjM.GetGameObject(1)->BindRigidBody();
	//m_ObjM.GetGameObject(2)->BindRigidBody();
	//m_ObjM.GetGameObject(3)->BindRigidBody();
	//m_ObjM.GetGameObject(4)->BindRigidBody();

	m_ObjM.GetGameObject(0)->GetRigidBody()->SetFriction(.0005f);
	m_ObjM.GetGameObject(1)->GetRigidBody()->ActivateMove(false);
	//m_ObjM.GetGameObject(2)->GetRigidBody()->ActivateMove(false);
	//m_ObjM.GetGameObject(3)->GetRigidBody()->ActivateMove(false);
	//m_ObjM.GetGameObject(4)->GetRigidBody()->ActivateMove(false);

	//Init basic trunks
	m_scene->Init();
	m_world->Init();

	vec3 a(1, 1, 0);
	vec3 b(-1, 1, 0);

	std::cout << b.Reflection(a) << "\n";
}

void MenuStage::Update(GameData& gd)
{	
	UNREFERENCED_PARAMETER(gd);
	//std::cout << "MenuStage::Update\n";

	BasicControl();
	SampleAnimation();
	
	//Update basic trunks
	m_world->Update(m_ObjM);
	m_scene->Draw(m_ObjM);

}

void MenuStage::Shutdown()
{
	std::cout << "MenuStage::Shutdown\n";

	//Cleare all Objects of the list
	m_ObjM.ClearObjectList();

	//Shutdown basic trunks
	m_scene->Shutdown();
	m_world->Shutdown();

	//Delete dynamic scene and world
	delete m_scene;
	delete m_world;
	m_scene = 0;
	m_world = 0;
}

void MenuStage::BasicControl(void)
{
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

	else if (InputManager::GetInstance().KeyTriggered(KEY_R))
		m_GSM->Restart(true);

	else if (InputManager::GetInstance().KeyTriggered(KEY_P))
	{
		//m_GSM->Pause();
		
		//Random checker
		std::cout << Random::GetInstance().GetRandomFloat() << "\n";
		std::cout << Random::GetInstance().GetRandomInt() << "\n";
		std::cout << Random::GetInstance().GetRandomVector() << "\n";
	}

	else if (InputManager::GetInstance().KeyTriggered(KEY_TAB))
	{
		std::cout << m_GSM->GetResolution().width << "\n";
		std::cout << m_GSM->GetResolution().height << "\n";

		m_GSM->SetFullScreen(true);
	}
}

void MenuStage::SampleAnimation(void)
{
	//Control White box with keyboard
	if (InputManager::GetInstance().KeyPressed(KEY_RIGHT))
		m_ObjM.GetGameObject(0)->GetRigidBody()->SetForce(vec3(.5f, 0, 0));

	if (InputManager::GetInstance().KeyPressed(KEY_LEFT))
		m_ObjM.GetGameObject(0)->GetRigidBody()->SetForce(vec3(-.5f, 0, 0));

	if (InputManager::GetInstance().KeyPressed(KEY_UP))
		m_ObjM.GetGameObject(0)->GetRigidBody()->SetForce(vec3(0, .5f, 0));

	if (InputManager::GetInstance().KeyPressed(KEY_DOWN))
		m_ObjM.GetGameObject(0)->GetRigidBody()->SetForce(vec3(0, -.5f, 0));

	if (InputManager::GetInstance().KeyPressed(KEY_SPACE))
		m_ObjM.GetGameObject(0)->GetRigidBody()->ClearVelocity();

	//Show the mouse's position when mouse botton clicked
	if (InputManager::GetInstance().KeyTriggered(MOUSE_LBUTTON) ||
		InputManager::GetInstance().KeyTriggered(MOUSE_RBUTTON))
		std::cout << InputManager::GetInstance().GetMousePosition() << "\n";
}