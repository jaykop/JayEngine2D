/******************************************************************************/
/*!
\file   MainMenu.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains MainMenu's class functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "../BaseData/BaseEnigne.h"
#include "MainMenu.h"

/******************************************************************************/
/*!
\brief - MenuStage constructor

\param gsm - pointer to the gams state manager
*/
/******************************************************************************/
MenuStage::MenuStage(GameStateManager* gsm)
{
	m_GSM = gsm;
}

/******************************************************************************/
/*!
\brief - MenuStage destructor
*/
/******************************************************************************/
MenuStage::~MenuStage()
{

}

void MenuStage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "MenuStage::Init\n";
	std::cout << "[Instruction]\nPress P: Pause Stage\nPress 0: Main Menu\n"
		"Press 1: ST_LV1\nPress 2: ST_LV2\nPress 3: ST_LV3\nPress ESC: Quit the App\n";
	
	std::cout << "You can control the White box with keyboard arrows!\n";

	//Init basic trunks
	m_ObjM.BindGameSystem(m_GSM->GetAppPtr());
	m_ObjM.InitGameSystem();

	//Set sprites
	m_ObjM.AddObject(0);
	m_ObjM.AddObject(1);

	m_ObjM.AddObject(2);
	m_ObjM.AddObject(3);
	m_ObjM.AddObject(4);
	m_ObjM.AddObject(5);

	//Set positions
	m_ObjM.GetGameObject(0)->SetPosition(vec3(10, 10, 0.2f));
	m_ObjM.GetGameObject(1)->SetPosition(vec3(-10, -10, 0.1f));
	m_ObjM.GetGameObject(0)->SetRotation(Random::GetInstance().GetRandomFloat(0, 360));
	m_ObjM.GetGameObject(1)->SetRotation(Random::GetInstance().GetRandomFloat(0, 360));
	m_ObjM.GetGameObject(0)->SetScale(vec3(30, 30));
	m_ObjM.GetGameObject(1)->SetScale(vec3(30, 30));
	m_ObjM.GetGameObject(0)->SetSpriteShape(CIRCLE);
	m_ObjM.GetGameObject(1)->SetSpriteShape(CIRCLE);

	m_ObjM.GetGameObject(2)->SetPosition(vec3(20, 0));
	m_ObjM.GetGameObject(3)->SetPosition(vec3(-20, 0));
	m_ObjM.GetGameObject(4)->SetPosition(vec3(0, -20));
	m_ObjM.GetGameObject(5)->SetPosition(vec3(0, 20));

	m_ObjM.GetGameObject(2)->SetScale(vec3(1, 300));
	m_ObjM.GetGameObject(3)->SetScale(vec3(1, 300));
	m_ObjM.GetGameObject(4)->SetScale(vec3(300, 1));
	m_ObjM.GetGameObject(5)->SetScale(vec3(300, 1));

	//Set colors
	m_ObjM.GetGameObject(0)->SetColor(vec4(1, 1, 1, 1));
	m_ObjM.GetGameObject(1)->SetColor(vec4(0, 1, 1, 1));

	m_ObjM.GetGameObject(2)->SetColor(vec4(0, 0, 1, 1));
	m_ObjM.GetGameObject(3)->SetColor(vec4(1, 1, 0, 1));
	m_ObjM.GetGameObject(4)->SetColor(vec4(1, 0, 0, 1));
	m_ObjM.GetGameObject(5)->SetColor(vec4(0, 1, 0, 1));

	//Bind rigid body
	m_ObjM.GetGameObject(0)->BindRigidBody();
	m_ObjM.GetGameObject(1)->BindRigidBody();

	m_ObjM.GetGameObject(2)->BindRigidBody();
	m_ObjM.GetGameObject(3)->BindRigidBody();
	m_ObjM.GetGameObject(4)->BindRigidBody();
	m_ObjM.GetGameObject(5)->BindRigidBody();

	m_ObjM.GetGameObject(0)->GetRigidBody()->SetFriction(.0005f);
	m_ObjM.GetGameObject(0)->GetRigidBody()->SetScale(vec3(5.f, 5.f));
	m_ObjM.GetGameObject(1)->GetRigidBody()->SetFriction(.0005f);
	m_ObjM.GetGameObject(1)->GetRigidBody()->SetScale(vec3(5.f, 5.f));

	m_ObjM.GetGameObject(2)->GetRigidBody()->ActivateMove(false);
	m_ObjM.GetGameObject(3)->GetRigidBody()->ActivateMove(false);
	m_ObjM.GetGameObject(4)->GetRigidBody()->ActivateMove(false);
	m_ObjM.GetGameObject(5)->GetRigidBody()->ActivateMove(false);
}

void MenuStage::Update(GameData& gd)
{	
	UNREFERENCED_PARAMETER(gd);
	//std::cout << "MenuStage::Update\n";

	BasicControl();
	SampleAnimation();

	//Update basic trunks
	m_ObjM.UpdateGameSystem();
}

void MenuStage::Shutdown()
{
	std::cout << "MenuStage::Shutdown\n";

	//Cleare all Objects of the list
	m_ObjM.ClearObjectList();
	m_ObjM.ShutdownGameSystem();
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

	if (InputManager::GetInstance().KeyTriggered(KEY_P))
		m_GSM->Pause();

	else if (InputManager::GetInstance().KeyTriggered(KEY_TAB))
	{
		m_ObjM.GetGameObject(0)->GetTexture()->LoadTexture("Resources/Texture/test.png");
		m_ObjM.GetGameObject(1)->GetTexture()->LoadTexture("Resources/Texture/test.png");
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

	if (InputManager::GetInstance().KeyTriggered(KEY_ENTER))
	{
		m_ObjM.GetGameObject(0)->GetRigidBody()->SetForce(Random::GetInstance().GetRandomVector(-1.f, 1.f));
		m_ObjM.GetGameObject(1)->GetRigidBody()->SetForce(Random::GetInstance().GetRandomVector(-1.f, 1.f));
	}

	if (InputManager::GetInstance().KeyTriggered(KEY_SPACE))
	{
		m_ObjM.GetGameObject(0)->GetRigidBody()->ClearVelocity();
		m_ObjM.GetGameObject(1)->GetRigidBody()->ClearVelocity();
	}

	//Show the mouse's position when mouse botton clicked
	if (InputManager::GetInstance().KeyTriggered(MOUSE_LBUTTON) ||
		InputManager::GetInstance().KeyTriggered(MOUSE_RBUTTON))
		std::cout << InputManager::GetInstance().GetMousePosition() << "\n";
}