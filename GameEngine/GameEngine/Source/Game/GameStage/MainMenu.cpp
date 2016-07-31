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

void MenuStage::Load(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "MenuStage::Load\n";

	//Bind basic systems
	m_OBM.BindGameSystem(m_GSM);
}

void MenuStage::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "MenuStage::Init\n";
	std::cout << "[Instruction]\nPress P: Pause Stage\nPress 0: Main Menu\n"
		"Press 1: ST_LV1\nPress 2: ST_LV2\nPress 3: ST_LV3\nPress ESC: Quit the App\n";

	m_OBM.AddObject(new Sprite(0, &m_OBM));
	m_OBM.GetGameObject<Sprite>(0)->GetTexture()->LoadTexture("Resource/Texture/Phantom.png");

	m_OBM.AddObject(new Text(50, &m_OBM));
	m_OBM.GetGameObject<Text>(50)->SetText(L"Text test...");
	m_OBM.GetGameObject<Text>(50)->SetScale(vec3(1, 1));
	m_OBM.GetGameObject<Text>(50)->SetColor(vec4(1, 1, 1, 1));

	m_OBM.AddObject(new Emitter(60, &m_OBM));
	m_OBM.GetGameObject<Emitter>(60)->GetTexture()->LoadTexture("Resource/Texture/particle.png");
	m_OBM.GetGameObject<Emitter>(60)->SetNumOfParticle(100);
	m_OBM.GetGameObject<Emitter>(60)->SetScale(vec3(2.f, 2.f));
	m_OBM.GetGameObject<Emitter>(60)->SetDirection(vec3(1.f, 0.f));
	m_OBM.GetGameObject<Emitter>(60)->SetSpeed(1.f);
	m_OBM.GetGameObject<Emitter>(60)->SetBoundary(5.f);
	m_OBM.GetGameObject<Emitter>(60)->SetColors(vec3(1,1,1), vec3(0,0,1));
	//m_OBM.GetGameObject<Text>(50)->SetPosition(vec3(0, 0, 0));

	//Set walls and small sprites
	offset = 0;
	//SetSamllSprites();
	//SetWallSprites();

	//m_OBM.AddObject(new Sprite(0, &m_OBM));
	//m_OBM.AddObject(new Sprite(1, &m_OBM));
	//m_OBM.GetGameObject<Sprite>(0)->SetRigidBody();
	//m_OBM.GetGameObject<Sprite>(1)->SetRigidBody();
	//m_OBM.GetGameObject<Sprite>(0)->SetPosition(vec3(0, 0));
	//m_OBM.GetGameObject<Sprite>(1)->SetPosition(vec3(10, 10));


	//float radius = 10;//Random::GetInstance().GetRandomFloat(10, 15);
	////m_OBM.GetGameObject<Sprite>(0)->SetScale(vec3(radius, radius));
	//m_OBM.GetGameObject<Sprite>(0)->SetScale(vec3(5, 10));
	//m_OBM.GetGameObject<Sprite>(1)->SetScale(vec3(radius, radius));
	////m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->SetShape(BALL);
	////m_OBM.GetGameObject<Sprite>(0)->GetTexture()->
	////	LoadTexture("Resource/Texture/circle.png");
	//m_OBM.GetGameObject<Sprite>(1)->GetRigidBody()->SetShape(BALL);
	//m_OBM.GetGameObject<Sprite>(1)->GetTexture()->
	//	LoadTexture("Resource/Texture/circle.png");
	//m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->SetScale(
	//	m_OBM.GetGameObject<Sprite>(0)->GetScale());
	//m_OBM.GetGameObject<Sprite>(1)->GetRigidBody()->SetScale(
	//	m_OBM.GetGameObject<Sprite>(1)->GetScale());

	//

	//m_OBM.GetGameObject<Sprite>(0)->SetRotation(
	//	Random::GetInstance().GetRandomFloat(-180, 180));

	//////Bind rigid body
	////m_OBM.GetGameObject<Sprite>(index)->GetRigidBody()->SetShape(BOX);
	////m_OBM.GetGameObject<Sprite>(index)->GetRigidBody()->SetScale(
	////	m_OBM.GetGameObject<Sprite>(index)->GetScale());

	//m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->SetMass(
	//	(m_OBM.GetGameObject<Sprite>(0)->GetScale().x *
	//	m_OBM.GetGameObject<Sprite>(0)->GetScale().y) / 50);
	//m_OBM.GetGameObject<Sprite>(1)->GetRigidBody()->SetMass(
	//	(m_OBM.GetGameObject<Sprite>(1)->GetScale().x *
	//	m_OBM.GetGameObject<Sprite>(1)->GetScale().y) / 50);

	//m_OBM.GetGameObject<Sprite>(1)->GetRigidBody()->ActivateMove(false);

	m_OBM.InitGameSystem();
	//m_OBM.GetGameScene()->SetBackgroundColor(vec4(1, 1, 1, 1));
	m_OBM.GetGameScene()->SetCamera(vec4(0, 0, 80, 0));
}

void MenuStage::Update(GameData& gd)
{	
	UNREFERENCED_PARAMETER(gd);
	//std::cout << "MenuStage::Update\n";

	BasicControl();
	PhysicsTest();

	//Update basic trunks
	m_OBM.UpdateGameSystem();
}

void MenuStage::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
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

void MenuStage::PhysicsTest(void)
{
	if (InputManager::GetInstance().KeyPressed(KEY_DOWN))
		m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->SetForce(vec3(0,-1));

	else if (InputManager::GetInstance().KeyPressed(KEY_UP))
		m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->SetForce(vec3(0,1));

	else if (InputManager::GetInstance().KeyPressed(KEY_LEFT))
		m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->SetForce(vec3(-1,0));

	else if (InputManager::GetInstance().KeyPressed(KEY_RIGHT))
		m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->SetForce(vec3(1,0));

	if (InputManager::GetInstance().KeyTriggered(KEY_ENTER))
	for (int index = 0; index < offset; ++index)
		m_OBM.GetGameObject<Sprite>(index)->GetRigidBody()->SetForce(
		vec3(Random::GetInstance().GetRandomFloat(-1.f, 1.f),
		Random::GetInstance().GetRandomFloat(-1.f, 1.f)));

	if (InputManager::GetInstance().KeyTriggered(KEY_SPACE))
	for (int index = 0; index < offset; ++index)
		m_OBM.GetGameObject<Sprite>(index)->GetRigidBody()->ClearVelocity();

	//Show the mouse's position when mouse botton clicked
	if (InputManager::GetInstance().KeyTriggered(MOUSE_LBUTTON) ||
		InputManager::GetInstance().KeyTriggered(MOUSE_RBUTTON))
	{
		std::cout << InputManager::GetInstance().GetRawMousePosition() << "\n";
		std::cout << InputManager::GetInstance().GetOrthoPosition() << "\n";
		std::cout << InputManager::GetInstance().GetPerspPosition() << "\n";
	}

	//// Collided with Opponent
	//if (m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->IsCollided())
	//{
	//	std::cout << "Sprite0's colliding?: " << m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->IsCollided() << "\n";
	//	std::cout << "Sprite0's colliding opponent?: " << m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->GetCollisionWith() << "\n";
	//	std::cout << "Sprite0's colliding with Sprite101?(Sprite info): " << m_OBM.GetGameObject<Sprite>(0)->GetRigidBody()->IsCollisionWith(
	//		m_OBM.GetGameObject<Sprite>(101)) << "\n";

	//	std::cout << "Sprite0's colliding with Sprite101?(World info): " << m_OBM.GetGameWorld()->GetCollisionRelation(
	//		m_OBM.GetGameObject<Sprite>(0),
	//		m_OBM.GetGameObject<Sprite>(101)) << "\n";
	//}
}

void MenuStage::SetSamllSprites(void)
{
	for (int index = 0; index < offset; ++index)
	{
		// Set sprite's basic info
		m_OBM.AddObject(new Sprite(index, &m_OBM));
		m_OBM.GetGameObject<Sprite>(index)->SetRigidBody();
		m_OBM.GetGameObject<Sprite>(index)->SetPosition(vec3(
			Random::GetInstance().GetRandomFloat(-50, 50),
			Random::GetInstance().GetRandomFloat(-30, 30)));

		float color_r = Random::GetInstance().GetRandomFloat(1, 1.f);
		float color_g = Random::GetInstance().GetRandomFloat(1, 1.f);
		float color_b = Random::GetInstance().GetRandomFloat(1, 1.f);
		m_OBM.GetGameObject<Sprite>(index)->SetColor(vec4(
			color_r, color_g, color_b, 1.f));

		if (!m_OBM.GetGameObject<Sprite>(index)->GetID())
		{
			float radius = Random::GetInstance().GetRandomFloat(10, 15);
			m_OBM.GetGameObject<Sprite>(index)->SetScale(vec3(radius, radius));
			m_OBM.GetGameObject<Sprite>(index)->GetRigidBody()->SetShape(BALL);
			m_OBM.GetGameObject<Sprite>(index)->GetTexture()->
				LoadTexture("Resource/Texture/circle.png");
			m_OBM.GetGameObject<Sprite>(index)->GetRigidBody()->SetScale(
				m_OBM.GetGameObject<Sprite>(index)->GetScale());
		}

		else
		{
			m_OBM.GetGameObject<Sprite>(index)->SetScale(vec3(
				Random::GetInstance().GetRandomFloat(11, 15),
				Random::GetInstance().GetRandomFloat(11, 15)));

			m_OBM.GetGameObject<Sprite>(index)->SetRotation(
				Random::GetInstance().GetRandomFloat(0, 360));

			//Bind rigid body
			m_OBM.GetGameObject<Sprite>(index)->GetRigidBody()->SetShape(BOX);
			m_OBM.GetGameObject<Sprite>(index)->GetRigidBody()->SetScale(
				m_OBM.GetGameObject<Sprite>(index)->GetScale());

			//m_OBM.GetGameObject<Sprite>(index)->GetRigidBody()->ActivateMove(false);
		}

		m_OBM.GetGameObject<Sprite>(index)->GetRigidBody()->SetMass(
			(m_OBM.GetGameObject<Sprite>(index)->GetScale().x *
			m_OBM.GetGameObject<Sprite>(index)->GetScale().y) / 50);
		m_OBM.GetGameObject<Sprite>(index)->GetRigidBody()->SetFriction(0.0005f);
	}
}

void MenuStage::SetWallSprites(void)
{
	for (int index = 101; index < 105; ++index)
	{
		m_OBM.AddObject(new Sprite(index, &m_OBM));

		//Bind rigid body
		m_OBM.GetGameObject<Sprite>(index)->SetRigidBody();
		m_OBM.GetGameObject<Sprite>(index)->GetRigidBody()->SetShape(BOX);
		m_OBM.GetGameObject<Sprite>(index)->GetRigidBody()->ActivateMove(false);

		m_OBM.GetGameObject<Sprite>(index)->GetRigidBody()->SetMass(
			(m_OBM.GetGameObject<Sprite>(index)->GetScale().x *
			m_OBM.GetGameObject<Sprite>(index)->GetScale().y) / 50);
	}

	//Set positions and scale
	m_OBM.GetGameObject<Sprite>(101)->SetPosition(vec3(-70, 0, 0));
	m_OBM.GetGameObject<Sprite>(102)->SetPosition(vec3(70, 0, 0));
	m_OBM.GetGameObject<Sprite>(103)->SetPosition(vec3(0, -40.f, 0));
	m_OBM.GetGameObject<Sprite>(104)->SetPosition(vec3(0, 40.f, 0));

	// Set sprits's scale
	m_OBM.GetGameObject<Sprite>(101)->SetScale(vec3(1, 200));
	m_OBM.GetGameObject<Sprite>(102)->SetScale(vec3(1, 200));
	m_OBM.GetGameObject<Sprite>(103)->SetScale(vec3(200, 1));
	m_OBM.GetGameObject<Sprite>(104)->SetScale(vec3(200, 1));

	//Set colors
	m_OBM.GetGameObject<Sprite>(101)->SetColor(vec4(1, 0, 0, 1));
	m_OBM.GetGameObject<Sprite>(102)->SetColor(vec4(0, 1, 0, 1));
	m_OBM.GetGameObject<Sprite>(103)->SetColor(vec4(0, 0, 1, 1));
	m_OBM.GetGameObject<Sprite>(104)->SetColor(vec4(.5f, .5f, .5f, 1));

	// Set body's scale
	m_OBM.GetGameObject<Sprite>(101)->GetRigidBody()->SetScale(vec3(1, 200));
	m_OBM.GetGameObject<Sprite>(102)->GetRigidBody()->SetScale(vec3(1, 200));
	m_OBM.GetGameObject<Sprite>(103)->GetRigidBody()->SetScale(vec3(200, 1));
	m_OBM.GetGameObject<Sprite>(104)->GetRigidBody()->SetScale(vec3(200, 1));
}

void MenuStage::Unload(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "MenuStage::Unload\n";
}

void MenuStage::LoadObjects(const wchar_t* fileName)
{

}