/******************************************************************************/
/*!
\file   JsonParser.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/07/30(yy/mm/dd)

\description
Contains JsonParser's class and member function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include <fstream>
#include <iostream>

//#include "JsonParser.h"
#include "../../Graphic/Scene.h"
#include "../../Graphic/Particle.h"
#include "../../Physics/RigidBody.h"
#include "../../Logic/GameLogic.h"
#include "../../Logic/LogicFactory.h"
#include "../../Sound/SoundManager.h"
#include "../../ObjectManager/ObjectManager.h"

JsonParser::JsonParser()
:new_text(0), new_emitter(0), new_sprite(0)
{}

JsonParser::~JsonParser()
{}

const Json::Value& JsonParser::GetLoadedData(void) const
{
	return m_data;
}

void JsonParser::write_sample(void)
{
	Json::Value root;
	root["id"] = "Luna";
	root["name"] = "Silver";
	root["age"] = 19;
	root["hasCar"] = false;

	Json::Value items;
	items.append("nootbook");
	items.append("ipadmini2");
	items.append("iphone5s");
	root["items"] = items;

	Json::Value friends;
	Json::Value tom;
	tom["name"] = "Tom";
	tom["age"] = 21;
	Json::Value jane;
	jane["name"] = "jane";
	jane["age"] = 23;
	friends.append(tom);
	friends.append(jane);
	root["friends"] = friends;

	Json::StyledWriter writer;
	str = writer.write(root);
	std::cout << str << std::endl << std::endl;

	// This will remove usless new line '\n'
	Save(L"Resource/Data/Sample2.something", root);
}

void JsonParser::Save(const wchar_t* dir, const Json::Value& contents)
{
	std::ofstream save_dir;
	save_dir.open(dir);

	Json::StyledWriter writter;
	save_dir << writter.write(contents);
}

void JsonParser::Load(wchar_t* dir)
{
	// Load json data to input file stream
	std::ifstream load_dir(dir, std::ifstream::binary);

	// Move to json data
	load_dir >> m_data;

	// Convert to string
	Json::StyledWriter writer;
	str = writer.write(m_data);

	// Parser checker
	Json::Reader reader;
	bool parsingRet = reader.parse(str, m_data);
	if (!parsingRet)
		std::cout << "Failed to parse Json : " << reader.getFormattedErrorMessages();
}

void JsonParser::InitAssetData(GLManager* GLM, SoundManager* SM)
{
	if (m_data.isMember("Font") &&
		m_data["Font"].isString())
			GLM->SetFont(m_data["Font"].asCString());
	
	else
		std::cerr << "Cannot load font file!\n";

	if (m_data.isMember("Texture"))
	{
		for (auto it = m_data["Texture"].begin();
			it != m_data["Texture"].end(); ++it)
		{
			if ((*it).isMember("name") &&
				(*it)["name"].isString() &&
				(*it).isMember("directory") &&
				(*it)["directory"].isString())
					GLM->AddTexture((*it)["name"].asCString(), (*it)["directory"].asCString());
		}
	}

	else
		std::cerr << "Cannot load texture files!\n";

	if (m_data.isMember("Sound"))
	{
		for (auto it = m_data["Sound"].begin();
			it != m_data["Sound"].end(); ++it)
		{
			//SM->Load((*it).asCString(), );
		}
	}

	else
		std::cerr << "Cannot load sound files!\n";
}

void JsonParser::InitLoadedData(ObjectManager* obm)
{
	// Load stage and objects
	LoadStage(obm->GetGameScene());
	LoadObjects(obm);
}

void JsonParser::LoadStage(Scene* scene)
{
	// Check if there is proper stage info
	if (m_data["Stage"].isArray())
	{
		// Set backgroud's color
		if ((*m_data["Stage"].begin()).isMember("Background") &&
			(*m_data["Stage"].begin())["Background"].isArray() &&
			(*m_data["Stage"].begin())["Background"].size() == 4 && 
			(*m_data["Stage"].begin())["Background"][0].isNumeric())
				scene->SetBackgroundColor(vec4(
				(*m_data["Stage"].begin())["Background"][0].asFloat(),
				(*m_data["Stage"].begin())["Background"][1].asFloat(),
				(*m_data["Stage"].begin())["Background"][2].asFloat(),
				(*m_data["Stage"].begin())["Background"][3].asFloat()));

		// Set camera's position
		if ((*m_data["Stage"].begin()).isMember("Camera") &&
			(*m_data["Stage"].begin())["Camera"].isArray() &&
			(*m_data["Stage"].begin())["Camera"].size() == 4 &&
			(*m_data["Stage"].begin())["Camera"][0].isNumeric())
				scene->SetCamera(vec4(
				(*m_data["Stage"].begin())["Camera"][0].asFloat(),
				(*m_data["Stage"].begin())["Camera"][1].asFloat(),
				(*m_data["Stage"].begin())["Camera"][2].asFloat(),
				(*m_data["Stage"].begin())["Camera"][3].asFloat()));
	}
}

void JsonParser::LoadObjects(ObjectManager* obm)
{
	// Check if there is proper object info
	if (m_data["Object"].isArray())
	{
		for (auto it = m_data["Object"].begin();
			it != m_data["Object"].end(); 
			++it)
		{
			if ((*it).isMember("Type") &&
				(*it).isMember("ID") && 
				(*it)["ID"].isInt())
			{
				int id = (*it)["ID"].asInt();

				if (!strcmp((*it)["Type"].asCString(), "SPRITE"))
				{
					obm->AddObject(new Sprite(id, obm));
					LoadBasicObject(it, obm->GetGameObject<Sprite>(id));
				}

				else if (!strcmp((*it)["Type"].asCString(), "TEXT"))
				{
					obm->AddObject(new Text(id, obm));
					LoadBasicObject(it, obm->GetGameObject<Sprite>(id));
					
					if ((*it).isMember("Text") &&
						(*it)["Text"].isString())
						obm->GetGameObject<Text>(id)->
						SetText(m_converter.ConverCtoWC(
						(*it)["Text"].asCString()));
				}

				else if (!strcmp((*it)["Type"].asCString(), "PARTICLE"))
				{
					obm->AddObject(new Emitter(id, obm));
					LoadBasicObject(it, obm->GetGameObject<Sprite>(id));

					if ((*it).isMember("CenterColor") &&
						(*it)["CenterColor"].isArray() &&
						(*it)["CenterColor"].size() == 3 &&
						(*it)["CenterColor"][0].isNumeric() &&
						(*it).isMember("EdgeColor") &&
						(*it)["EdgeColor"].isArray() &&
						(*it)["EdgeColor"].size() == 3 &&
						(*it)["EdgeColor"][0].isNumeric())
					{
						vec3 centre(
							(*it)["CenterColor"][0].asFloat(),
							(*it)["CenterColor"][1].asFloat(),
							(*it)["CenterColor"][2].asFloat());

						vec3 edge(
							(*it)["EdgeColor"][0].asFloat(),
							(*it)["EdgeColor"][1].asFloat(),
							(*it)["EdgeColor"][2].asFloat());

						obm->GetGameObject<Emitter>(id)->SetColors(centre, edge);
					}

					if ((*it).isMember("Mode") &&
						(*it)["Mode"].isString())
					{
						// Todo: Preparing...
						//obm->GetGameObject<Emitter>(id)->SetMode();
					}

					if ((*it).isMember("Quantity") &&
						(*it)["Quantity"].isNumeric())
						obm->GetGameObject<Emitter>(id)->SetNumOfParticle((*it)["Quantity"].asInt());

					if((*it).isMember("Direction") &&
						(*it)["Direction"].isArray() &&
						(*it)["Direction"].size() == 3 &&
						(*it)["Direction"][0].isNumeric())
						obm->GetGameObject<Emitter>(id)->SetDirection(vec3(
							(*it)["Direction"][0].asFloat(),
							(*it)["Direction"][1].asFloat(),
							(*it)["Direction"][2].asFloat()));

					if ((*it).isMember("Speed") &&
						(*it)["Speed"].isNumeric())
						obm->GetGameObject<Emitter>(id)->SetSpeed((*it)["Speed"].asFloat());

					if ((*it).isMember("Range") &&
						(*it)["Range"].isNumeric())
						obm->GetGameObject<Emitter>(id)->SetBoundary((*it)["Range"].asFloat());
				}	

				if ((*it).isMember("Logic"))
					LoadLogics(it, obm->GetGameObject<Sprite>(id));
			}
		}
	}
}

void JsonParser::LoadBasicObject(Json::Value::iterator& it, Sprite* sprite)
{
	//! Set transform
	if ((*it).isMember("Position") &&
		(*it)["Position"].isArray() &&
		(*it)["Position"].size() == 3 &&
		(*it)["Position"][0].isNumeric())
	{
		sprite->SetPosition(vec3(
			(*it)["Position"][0].asFloat(),
			(*it)["Position"][1].asFloat(),
			(*it)["Position"][2].asFloat()));
	}

	if (sprite->GetType() != PARTICLE &&
		(*it).isMember("Scale") &&
		(*it)["Scale"].isArray() &&
		(*it)["Scale"].size() == 3 &&
		(*it)["Scale"][0].isNumeric())
	{
		sprite->SetScale(vec3(
			(*it)["Scale"][0].asFloat(),
			(*it)["Scale"][1].asFloat(),
			(*it)["Scale"][2].asFloat()));
	}

	if ((*it).isMember("Rotation") &&
		(*it)["Rotation"].isNumeric())
		sprite->SetRotation((*it)["Rotation"].asFloat());

	//! Set image(texture)
	if ((*it).isMember("Projection") &&
		(*it)["Projection"].isString())
	{
		if (!strcmp((*it)["Projection"].asCString(),
			"ORTHOGONAL"))
			sprite->SetProjectionType(ORTHOGONAL);

		else if (!strcmp((*it)["Projection"].asCString(),
			"PERSPECTIVE"))
			sprite->SetProjectionType(PERSPECTIVE);
	}

	if (sprite->GetType() != PARTICLE &&
		(*it).isMember("Color") &&
		(*it)["Color"].isArray() &&
		(*it)["Color"].size() == 4 &&
		(*it)["Color"][0].isNumeric())
	{
		sprite->SetColor(vec4(
			(*it)["Color"][0].asFloat(),
			(*it)["Color"][1].asFloat(),
			(*it)["Color"][2].asFloat(),
			(*it)["Color"][3].asFloat()));
	}

	if ((*it).isMember("Animation") &&
		(*it)["Animation"].isArray() &&
		(*it)["Animation"].size() == 2 &&
		(*it)["Animation"][0].isNumeric())
	{
		sprite->SetAnimation(
			(*it)["Animation"][0].asInt(),
			(*it)["Animation"][1].asFloat());
	}

	//! Set physics
	if ((*it).isMember("Body") &&
		(*it)["Body"].isBool())
		sprite->SetRigidBody();

	//! Body settor
	if ((*it)["Body"].asBool())
	{
		//! Body collider toggle
		if ((*it).isMember("Collider") &&
			(*it)["Collider"].isBool())
			sprite->GetRigidBody()
			->ActivateCollider((*it)["Collider"].asBool());

		//! Body move toggle
		if ((*it).isMember("Move") &&
			(*it)["Move"].isBool())
			sprite->GetRigidBody()
			->ActivateMove((*it)["Move"].asBool());

		//! Body accel
		if ((*it).isMember("Accel") &&
			(*it)["Accel"].isNumeric())
			sprite->GetRigidBody()
			->SetAcceleration((*it)["Accel"].asFloat());

		//! Body force
		if ((*it).isMember("Force") &&
			(*it)["Force"].isArray() &&
			(*it)["Force"].size() == 3 &&
			(*it)["Force"][0].isNumeric())
		{
			sprite
				->GetRigidBody()->SetForce(vec3(
				(*it)["Force"][0].asFloat(),
				(*it)["Force"][1].asFloat(),
				(*it)["Force"][2].asFloat()));
		}

		//! Body scale
		if ((*it).isMember("BodyScale") &&
			(*it)["BodyScale"].isArray() &&
			(*it)["BodyScale"].size() == 3 &&
			(*it)["BodyScale"][0].isNumeric())
		{
			sprite->GetRigidBody()
				->SetScale(vec3(
				(*it)["BodyScale"][0].asFloat(),
				(*it)["BodyScale"][1].asFloat(),
				(*it)["BodyScale"][2].asFloat()));
		}

		//! Body mass
		if ((*it).isMember("Mass") &&
			(*it)["Mass"].isNumeric())
			sprite->GetRigidBody()
			->SetMass((*it)["Mass"].asFloat());

		//! Body Friction
		if ((*it).isMember("Friction") &&
			(*it)["Friction"].isNumeric())
			sprite->GetRigidBody()
			->SetFriction((*it)["Friction"].asFloat());

		//! Body mass
		if ((*it).isMember("Friction") &&
			(*it)["Friction"].isNumeric())
			sprite->GetRigidBody()
			->SetFriction((*it)["Friction"].asFloat());

		//! Body shape
		if ((*it).isMember("Shape") &&
			(*it)["Shape"].isString())
		{
			if (!strcmp("BALL", (*it)["Shape"].asCString()))
				sprite->GetRigidBody()
				->SetShape(BALL);

			else if (!strcmp("BOX", (*it)["Shape"].asCString()))
				sprite->GetRigidBody()
				->SetShape(BOX);
		}
	}
}

void JsonParser::LoadLogics(Json::Value::iterator& it, Object* object)
{
	if ((*it).isMember("Logic"))
	{
		for (auto logic = (*it)["Logic"].begin();
			logic != (*it)["Logic"].end(); ++logic)
		{
			if ((*logic).isMember("name"))
			{
				GameLogic* newLogic = LogicFactory::CreateLogic((*logic)["name"].asCString(), object);
				if (newLogic)
				{
					if ((*logic).isMember("values"))
					{
						newLogic->Load((*logic)["values"]);
						object->AddLogic(newLogic);
					}
				}
				else std::cerr << "Error: Cannot make new logic" << (*logic)["name"].asCString() << std::endl;
			}
		}
	}
}
