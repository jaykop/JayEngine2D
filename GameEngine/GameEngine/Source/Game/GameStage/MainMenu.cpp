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

#include "MainMenu.h"
#include "../BaseData/BaseEnigne.h"
#include "../GameLogic/SampleLogic.h"

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
	m_OBM.BindGameSystem(m_GSM);
	m_OBM.InitGameSystem();

	//Set sprites
	m_OBM.AddObject(new Sprite(0, &m_OBM));
	m_OBM.AddObject(new Sprite(1, &m_OBM));

	//Set positions
	m_OBM.GetGameObject<Sprite>(0)->SetPosition(vec3(-10, 10.f, 1.05f));
	m_OBM.GetGameObject<Sprite>(1)->SetPosition(vec3(-10, 0, 1.05f));
	m_OBM.GetGameObject<Sprite>(0)->SetScale(vec3(5, 5));
	m_OBM.GetGameObject<Sprite>(1)->SetScale(vec3(50, 5));

	//Set colors
	m_OBM.GetGameObject<Sprite>(0)->SetColor(vec4(1, 1, 1, 1));
	m_OBM.GetGameObject<Sprite>(1)->SetColor(vec4(0, 1, 1, 1));

	//Bind rigid body
	m_OBM.GetGameObject<Sprite>(0)->SetRigidBody(new RigidBody);
	m_OBM.GetGameObject<Sprite>(1)->SetRigidBody(new RigidBody);

	m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->SetFriction(.0005f);
	m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->SetScale(vec3(5.f, 5.f));
	m_OBM.GetGameObject<Sprite>(1)->GetRigidBody()->SetFriction(.0005f);
	m_OBM.GetGameObject<Sprite>(1)->GetRigidBody()->SetScale(vec3(50.f, 5.f));

	m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->SetShape(BOX);
	m_OBM.GetGameObject<Sprite>(1)->GetRigidBody()->SetShape(BOX);
	m_OBM.GetGameObject<Sprite>(1)->GetRigidBody()->ActivateMove(false);

	m_OBM.GetGameScene()->SetBackgroundColor(vec4(0, 0, 0, 1));

}

void MenuStage::Update(GameData& gd)
{	
	UNREFERENCED_PARAMETER(gd);
	//std::cout << "MenuStage::Update\n";

	BasicControl();
	SampleAnimation();

	//Update basic trunks
	m_OBM.UpdateGameSystem();
}

void MenuStage::Shutdown()
{
	std::cout << "MenuStage::Shutdown\n";

	//Cleare all Objects of the list
	m_OBM.ShutdownGameSystem();
	m_OBM.ClearObjectList();
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
}

void MenuStage::SampleAnimation(void)
{
	//Control White box with keyboard
	if (InputManager::GetInstance().KeyPressed(KEY_RIGHT))
		m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->SetForce(vec3(.5f, 0, 0));

	if (InputManager::GetInstance().KeyPressed(KEY_LEFT))
		m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->SetForce(vec3(-.5f, 0, 0));

	if (InputManager::GetInstance().KeyPressed(KEY_UP))
		m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->SetForce(vec3(0, .5f, 0));

	if (InputManager::GetInstance().KeyPressed(KEY_DOWN))
		m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->SetForce(vec3(0, -.5f, 0));

	if (InputManager::GetInstance().KeyTriggered(KEY_ENTER))
		m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->SetForce(vec3(Random::GetInstance().GetRandomFloat(-2.f, 2.f), -1));

	if (InputManager::GetInstance().KeyTriggered(KEY_SPACE))
		m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->ClearVelocity();

	//Show the mouse's position when mouse botton clicked
	if (InputManager::GetInstance().KeyTriggered(MOUSE_LBUTTON) ||
		InputManager::GetInstance().KeyTriggered(MOUSE_RBUTTON))
	{
		std::cout << InputManager::GetInstance().GetRawMousePosition() << "\n";
		std::cout << InputManager::GetInstance().GetOrthoPosition() << "\n";
		std::cout << InputManager::GetInstance().GetPerspPosition() << "\n";
	}
}