#include "DemoLogic_LV1.h"
#include "../BaseData/BaseEnigne.h"

GameLogic* DemoLogic_LV1Builder::BuildLogic(Object* Owner) const
{
	return new DemoLogic_LV1(Owner);
}

DemoLogic_LV1::DemoLogic_LV1(Object* owner)
: m_Owner(owner), m_OBM(owner->GetOBM()), m_GSM(owner->GetOBM()->GetGSM())
{}

void DemoLogic_LV1::Load(const Json::Value& data)
{
	UNREFERENCED_PARAMETER(data);
	std::cout << "DemoLogic_LV1 Load\n";
}

void DemoLogic_LV1::Init(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "DemoLogic_LV1 Inited\n";

	qunatity = 10;

	SetSamllSprites();
	SetWallSprites();
}

void DemoLogic_LV1::Update(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "DemoLogic_LV1 Update\n";

	BasicControl();
	PhysicsTest();
}

void DemoLogic_LV1::Shutdown(GameData& gd)
{
	UNREFERENCED_PARAMETER(gd);
	std::cout << "DemoLogic_LV1 Shutdown\n";
}

void DemoLogic_LV1::Unload(void)
{
	std::cout << "DemoLogic_LV1 Unload\n";
}

void DemoLogic_LV1::BasicControl(void)
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

void DemoLogic_LV1::PhysicsTest(void)
{
	if (InputManager::GetInstance().KeyPressed(KEY_DOWN))
		m_OBM->GetGameObject<Sprite>(0)->GetRigidBody()->SetForce(vec3(0,-1));

	else if (InputManager::GetInstance().KeyPressed(KEY_UP))
		m_OBM->GetGameObject<Sprite>(0)->GetRigidBody()->SetForce(vec3(0,1));

	else if (InputManager::GetInstance().KeyPressed(KEY_LEFT))
		m_OBM->GetGameObject<Sprite>(0)->GetRigidBody()->SetForce(vec3(-1,0));

	else if (InputManager::GetInstance().KeyPressed(KEY_RIGHT))
		m_OBM->GetGameObject<Sprite>(0)->GetRigidBody()->SetForce(vec3(1,0));

	if (InputManager::GetInstance().KeyTriggered(KEY_ENTER))
	for (int index = 0; index < qunatity; ++index)
		m_OBM->GetGameObject<Sprite>(index)->GetRigidBody()->SetForce(
		vec3(Random::GetInstance().GetRandomFloat(-1.f, 1.f),
		Random::GetInstance().GetRandomFloat(-1.f, 1.f)));

	if (InputManager::GetInstance().KeyTriggered(KEY_SPACE))
	for (int index = 0; index < qunatity; ++index)
		m_OBM->GetGameObject<Sprite>(index)->GetRigidBody()->ClearVelocity();

	//Show the mouse's position when mouse botton clicked
	if (InputManager::GetInstance().KeyTriggered(MOUSE_LEFT) ||
		InputManager::GetInstance().KeyTriggered(MOUSE_RIGHT))
	{
		std::cout << InputManager::GetInstance().GetRawMousePosition() << "\n";
		std::cout << InputManager::GetInstance().GetOrthoPosition() << "\n";
		std::cout << InputManager::GetInstance().GetPerspPosition() << "\n";
	}

	//// Collided with Opponent
	//if (m_OBM->GetGameObject<Sprite>(0)->GetRigidBody()->IsCollided())
	//{
	//	std::cout << "Sprite0's colliding?: " << m_OBM->GetGameObject<Sprite>(0)->GetRigidBody()->IsCollided() << "\n";
	//	std::cout << "Sprite0's colliding opponent?: " << m_OBM->GetGameObject<Sprite>(0)->GetRigidBody()->GetCollisionWith() << "\n";
	//	std::cout << "Sprite0's colliding with Sprite101?(Sprite info): " << m_OBM->GetGameObject<Sprite>(0)->GetRigidBody()->IsCollisionWith(
	//		m_OBM->GetGameObject<Sprite>(101)) << "\n";

	//	std::cout << "Sprite0's colliding with Sprite101?(World info): " << m_OBM->GetGameWorld()->GetCollisionRelation(
	//		m_OBM->GetGameObject<Sprite>(0),
	//		m_OBM->GetGameObject<Sprite>(101)) << "\n";
	//}
}

void DemoLogic_LV1::SetSamllSprites(void)
{
	for (int index = 0; index < qunatity; ++index)
	{
		// Set sprite's basic info
		m_OBM->AddObject(new Sprite(index, m_OBM));
		m_OBM->GetGameObject<Sprite>(index)->SetRigidBody();
		m_OBM->GetGameObject<Sprite>(index)->SetPosition(vec3(
			Random::GetInstance().GetRandomFloat(-30, 30),
			Random::GetInstance().GetRandomFloat(-30, 30)));

		float color_r = Random::GetInstance().GetRandomFloat(0.f, 1.f);
		float color_g = Random::GetInstance().GetRandomFloat(0.f, 1.f);
		float color_b = Random::GetInstance().GetRandomFloat(0.f, 1.f);
		m_OBM->GetGameObject<Sprite>(index)->SetColor(vec4(
			color_r, color_g, color_b, 1.f));

		if (Random::GetInstance().GetRandomInt(0, 10) < 5)
		{
			float radius = Random::GetInstance().GetRandomFloat(5, 10);
			m_OBM->GetGameObject<Sprite>(index)->SetScale(vec3(radius, radius));
			m_OBM->GetGameObject<Sprite>(index)->GetRigidBody()->SetShape(BALL);
			m_OBM->GetGameObject<Sprite>(index)->SetTexture(m_GSM->GetGLManager()->GetTexture(1));
			m_OBM->GetGameObject<Sprite>(index)->GetRigidBody()->SetScale(
				m_OBM->GetGameObject<Sprite>(index)->GetScale());
		}

		else
		{
			m_OBM->GetGameObject<Sprite>(index)->SetScale(vec3(
				Random::GetInstance().GetRandomFloat(5, 10),
				Random::GetInstance().GetRandomFloat(5, 10)));

			m_OBM->GetGameObject<Sprite>(index)->SetRotation(
				Random::GetInstance().GetRandomFloat(0, 360));

			//Bind rigid body
			m_OBM->GetGameObject<Sprite>(index)->GetRigidBody()->SetShape(BOX);
			m_OBM->GetGameObject<Sprite>(index)->GetRigidBody()->SetScale(
				m_OBM->GetGameObject<Sprite>(index)->GetScale());
		}

		m_OBM->GetGameObject<Sprite>(index)->GetRigidBody()->SetMass(
			(m_OBM->GetGameObject<Sprite>(index)->GetScale().x *
			m_OBM->GetGameObject<Sprite>(index)->GetScale().y) / 50);
		m_OBM->GetGameObject<Sprite>(index)->GetRigidBody()->SetFriction(0.0005f);
	}
}

void DemoLogic_LV1::SetWallSprites(void)
{
	for (int index = 101; index < 105; ++index)
	{
		m_OBM->AddObject(new Sprite(index, m_OBM));

		//Bind rigid body
		m_OBM->GetGameObject<Sprite>(index)->SetRigidBody();
		m_OBM->GetGameObject<Sprite>(index)->GetRigidBody()->SetShape(BOX);
		m_OBM->GetGameObject<Sprite>(index)->GetRigidBody()->ActivateMove(false);

		m_OBM->GetGameObject<Sprite>(index)->GetRigidBody()->SetMass(
			(m_OBM->GetGameObject<Sprite>(index)->GetScale().x *
			m_OBM->GetGameObject<Sprite>(index)->GetScale().y) / 50);
	}

	//Set positions and scale
	m_OBM->GetGameObject<Sprite>(101)->SetPosition(vec3(-50, 0, 0));
	m_OBM->GetGameObject<Sprite>(102)->SetPosition(vec3(50, 0, 0));
	m_OBM->GetGameObject<Sprite>(103)->SetPosition(vec3(0, -40.f, 0));
	m_OBM->GetGameObject<Sprite>(104)->SetPosition(vec3(0, 40.f, 0));

	// Set sprits's scale
	m_OBM->GetGameObject<Sprite>(101)->SetScale(vec3(1, 200));
	m_OBM->GetGameObject<Sprite>(102)->SetScale(vec3(1, 200));
	m_OBM->GetGameObject<Sprite>(103)->SetScale(vec3(200, 1));
	m_OBM->GetGameObject<Sprite>(104)->SetScale(vec3(200, 1));

	//Set colors
	m_OBM->GetGameObject<Sprite>(101)->SetColor(vec4(1, 0, 0, 1));
	m_OBM->GetGameObject<Sprite>(102)->SetColor(vec4(0, 1, 0, 1));
	m_OBM->GetGameObject<Sprite>(103)->SetColor(vec4(0, 0, 1, 1));
	m_OBM->GetGameObject<Sprite>(104)->SetColor(vec4(.5f, .5f, .5f, 1));

	// Set body's scale
	m_OBM->GetGameObject<Sprite>(101)->GetRigidBody()->SetScale(vec3(1, 200));
	m_OBM->GetGameObject<Sprite>(102)->GetRigidBody()->SetScale(vec3(1, 200));
	m_OBM->GetGameObject<Sprite>(103)->GetRigidBody()->SetScale(vec3(200, 1));
	m_OBM->GetGameObject<Sprite>(104)->GetRigidBody()->SetScale(vec3(200, 1));
}