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
	m_ObjM.BindGameSystem(m_GSM);
	m_ObjM.InitGameSystem();

	//Set sprites
	m_ObjM.AddObject(0, SPRITE);
	m_ObjM.AddObject(1, SPRITE);

	//Set positions
	m_ObjM.GetSprite(0)->SetPosition(vec3(-10, 10.f, 1.05f));
	m_ObjM.GetSprite(1)->SetPosition(vec3(-10, 0, 1.05f));
	m_ObjM.GetSprite(0)->SetScale(vec3(5, 5));
	m_ObjM.GetSprite(1)->SetScale(vec3(50, 5));

	//Set colors
	m_ObjM.GetSprite(0)->SetColor(vec4(1, 1, 1, 1));
	m_ObjM.GetSprite(1)->SetColor(vec4(0, 1, 1, 1));

	//Bind rigid body
	m_ObjM.GetSprite(0)->BindRigidBody();
	m_ObjM.GetSprite(1)->BindRigidBody();

	m_ObjM.GetSprite(0)->GetRigidBody()->SetFriction(.0005f);
	m_ObjM.GetSprite(0)->GetRigidBody()->SetScale(vec3(5.f, 5.f));
	m_ObjM.GetSprite(1)->GetRigidBody()->SetFriction(.0005f);
	m_ObjM.GetSprite(1)->GetRigidBody()->SetScale(vec3(50.f, 5.f));

	//m_ObjM.GetSprite(0)->GetTexture()->LoadTexture("Resource/Texture/circle.png");
	// m_ObjM.GetSprite(1)->GetTexture()->LoadTexture("Resource/Texture/circle.png");
	m_ObjM.GetSprite(0)->GetRigidBody()->SetShape(BOX);
	m_ObjM.GetSprite(1)->GetRigidBody()->SetShape(BOX);
	m_ObjM.GetSprite(1)->GetRigidBody()->ActivateMove(false);

	m_ObjM.GetGameScene()->SetBackgroundColor(vec4(0, 0, 0, 1));

	// math function checker
	std::cout << Math::DistanceOfPointSegment(vec3(-2,1), vec3(-1, 0), vec3(1, 0)) << "\n";

	vec3 a(0, -1);
	vec3 b(-1, -1);
	vec3 c(1, -1);

	std::cout << a.Reflection((b - c).Rotation(90)) << "\n";
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
	m_ObjM.ShutdownGameSystem();
	m_ObjM.ClearObjectList();
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
		m_ObjM.GetSprite(0)->GetRigidBody()->SetForce(vec3(.5f, 0, 0));

	if (InputManager::GetInstance().KeyPressed(KEY_LEFT))
		m_ObjM.GetSprite(0)->GetRigidBody()->SetForce(vec3(-.5f, 0, 0));

	if (InputManager::GetInstance().KeyPressed(KEY_UP))
		m_ObjM.GetSprite(0)->GetRigidBody()->SetForce(vec3(0, .5f, 0));

	if (InputManager::GetInstance().KeyPressed(KEY_DOWN))
		m_ObjM.GetSprite(0)->GetRigidBody()->SetForce(vec3(0, -.5f, 0));

	if (InputManager::GetInstance().KeyTriggered(KEY_ENTER))
	{
		m_ObjM.GetSprite(0)->GetRigidBody()->SetForce(vec3(Random::GetInstance().GetRandomFloat(-2.f, 2.f), -1));
	//	m_ObjM.GetSprite(1)->GetRigidBody()->SetForce(Random::GetInstance().GetRandomVector(-1.f, 1.f));
	}

	if (InputManager::GetInstance().KeyTriggered(KEY_SPACE))
	{
		m_ObjM.GetSprite(0)->GetRigidBody()->ClearVelocity();
		m_ObjM.GetSprite(1)->GetRigidBody()->ClearVelocity();
	}

	//Show the mouse's position when mouse botton clicked
	if (InputManager::GetInstance().KeyTriggered(MOUSE_LBUTTON) ||
		InputManager::GetInstance().KeyTriggered(MOUSE_RBUTTON))
	{
		std::cout << InputManager::GetInstance().GetRawMousePosition() << "\n";
		std::cout << InputManager::GetInstance().GetOrthoPosition() << "\n";
		std::cout << InputManager::GetInstance().GetPerspPosition() << "\n";
	}
}