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

void MenuStage::Init()
{
	DEBUG_PRINT("MenuStage::Init\n");
	DEBUG_PRINT("[Instruction]\nPress 0: Main Menu\n"
		"Press 1: ST_LV1\nPress 2: ST_LV2\nPress 3: ST_LV3\nPress ESC: Quit the App\n");
	std::cout << "You can control the red box with keyboard arrows!\n";
	m_scene = new Scene;

	//Set sprites
	m_ObjM.AddObject("sample");

	//Init Animation variables
	scale = true;
	m_posx = m_posy = offset = degree = 0, m_scl = speed = 1.f;

	m_scene->Init();
}

void MenuStage::Update()
{	
	BasicControl();
	SampleAnimation();
	m_ObjM.GetGameObject(0)->SetColor(vec4(1,0,0,.5f));
	m_scene->Draw(m_ObjM);
}

void MenuStage::Shutdown()
{
	DEBUG_PRINT("MenuStage::Shutdown\n");
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
	
//	if (!test)
	if (InputManager::GetInstance().KeyTriggered(KEY_T))
	{
		std::cout << "test unlocked1" << "\n";
	//	test = true;
	}

	//if (test)
	if (InputManager::GetInstance().KeyTriggered(KEY_T))
		std::cout << "check this out1" << "\n";

	if (m_IM->KeyTriggered(KEY_R))
	{
		std::cout << "test unlocked2" << "\n";
		//	test = true;
	}

	//if (test)
	if (m_IM->KeyTriggered(KEY_R))
		std::cout << "check this out2" << "\n";

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

	//Rotate the box
	degree++;

	//Scale the box;
	if (scale)
	{
		offset = 0.01f;
		if (m_scl >= 2)
			scale = false;
	}

	else
	{
		offset = -0.01f;
		if (m_scl <= 1)
			scale = true;
	}

	//Scale the box
	m_scl += offset;

	m_scene->SetCamera(vec3(m_posx, m_posy, -80));

	//sample
	//m_ObjM.GetGameObject("Sample1")->SetColor(glm::vec4(1.f, 0.f, 0.f, 0.5f));
	//m_ObjM.GetGameObject(0)->SetScale(vec3(m_scl, m_scl, 0.f));
	//m_ObjM.GetGameObject(0)->SetPosition(vec3(20.f, 20.f, 0.f));
	//m_ObjM.GetGameObject("Sample2")->SetColor(glm::vec4(0.f, 1.f, 0.f, 0.5f));
	//m_ObjM.GetGameObject(1)->SetRotation(degree);
	//m_ObjM.GetGameObject(1)->SetPosition(vec3(-20.f, -20.f, 0.f));
	//m_ObjM.GetGameObject(2)->SetPosition(vec3(m_posx, m_posy, 0.f));
	//m_ObjM.GetGameObject("Sample3")->SetColor(glm::vec4(0.f, 0.f, 1.f, 0.5f));

}