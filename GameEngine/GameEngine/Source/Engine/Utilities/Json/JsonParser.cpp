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

#include "JsonParser.h"
#include "../../Graphic/Scene.h"
#include "../../Graphic/Particle.h"
#include "../../Physics/RigidBody.h"
#include "../../ObjectManager/ObjectManager.h"

JsonParser::JsonParser()
{}
JsonParser::~JsonParser()
{}

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

void JsonParser::read_sample(void)
{

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
	load_dir >> m_loadedData;

	// Convert to string
	Json::StyledWriter writer;
	str = writer.write(m_loadedData);

	// Parser checker
	Json::Reader reader;
	bool parsingRet = reader.parse(str, m_loadedData);
	if (!parsingRet)
		std::cout << "Failed to parse Json : " << reader.getFormattedErrorMessages();
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
	if (m_loadedData["Stage"].isArray())
	{
		// Set backgroud's color
		if ((*m_loadedData["Stage"].begin()).isMember("Background") &&
			(*m_loadedData["Stage"].begin())["Background"].isArray() &&
			(*m_loadedData["Stage"].begin())["Background"].size() == 4 && 
			(*m_loadedData["Stage"].begin())["Background"][0].isNumeric())
				scene->SetBackgroundColor(vec4(
				(*m_loadedData["Stage"].begin())["Background"][0].asFloat(),
				(*m_loadedData["Stage"].begin())["Background"][1].asFloat(),
				(*m_loadedData["Stage"].begin())["Background"][2].asFloat(),
				(*m_loadedData["Stage"].begin())["Background"][3].asFloat()));

		// Set camera's position
		if ((*m_loadedData["Stage"].begin()).isMember("Camera") &&
			(*m_loadedData["Stage"].begin())["Camera"].isArray() &&
			(*m_loadedData["Stage"].begin())["Camera"].size() == 4 &&
			(*m_loadedData["Stage"].begin())["Camera"][0].isNumeric())
				scene->SetCamera(vec4(
				(*m_loadedData["Stage"].begin())["Camera"][0].asFloat(),
				(*m_loadedData["Stage"].begin())["Camera"][1].asFloat(),
				(*m_loadedData["Stage"].begin())["Camera"][2].asFloat(),
				(*m_loadedData["Stage"].begin())["Camera"][3].asFloat()));
	}
}

void JsonParser::LoadObjects(ObjectManager* obm)
{
	// Check if there is proper object info
	if (m_loadedData["Object"].isArray())
	{
		for (auto it = m_loadedData["Object"].begin();
			it != m_loadedData["Object"].end(); 
			++it)
		{
			if ((*it).isMember("Type") &&
				(*it).isMember("ID") && 
				(*it)["ID"].isInt())
			{
				int id = (*it)["ID"].asInt();
				obm->AddObject(new Sprite(id, obm));

				//! Set transform
				if ((*it).isMember("Position") &&
					(*it)["Position"].isArray() &&
					(*it)["Position"].size() == 3 &&
					(*it)["Position"][0].isNumeric())
				{
					obm->GetGameObject<Sprite>(id)->SetPosition(vec3(
						(*it)["Position"][0].asFloat(),
						(*it)["Position"][1].asFloat(),
						(*it)["Position"][2].asFloat()));
				}

				if ((*it).isMember("Scale") &&
					(*it)["Scale"].isArray() &&
					(*it)["Scale"].size() == 3 &&
					(*it)["Scale"][0].isNumeric())
				{
					obm->GetGameObject<Sprite>(id)->SetScale(vec3(
						(*it)["Scale"][0].asFloat(),
						(*it)["Scale"][1].asFloat(),
						(*it)["Scale"][2].asFloat()));
				}

				if ((*it).isMember("Rotation") &&
					(*it)["Rotation"].isNumeric())
					obm->GetGameObject<Sprite>(id)->SetRotation((*it)["Rotation"].asFloat());

				//! Set image(texture)
				if ((*it).isMember("Projection") &&
					(*it)["Projection"].isString())
				{
					if (!strcmp((*it)["Projection"].asString().c_str(),
						"ORTHOGONAL"))
						obm->GetGameObject<Sprite>(id)->SetProjectionType(ORTHOGONAL);

					else if (!strcmp((*it)["Projection"].asString().c_str(),
						"PERSPECTIVE"))
						obm->GetGameObject<Sprite>(id)->SetProjectionType(PERSPECTIVE);
				}

				if ((*it).isMember("Color") &&
					(*it)["Color"].isArray() &&
					(*it)["Color"].size() == 4 &&
					(*it)["Color"][0].isNumeric())
				{
					obm->GetGameObject<Sprite>(id)->SetColor(vec4(
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
					obm->GetGameObject<Sprite>(id)->SetAnimation(
						(*it)["Animation"][0].asInt(),
						(*it)["Animation"][1].asFloat());
				}

				//! Set physics
				if ((*it).isMember("Body") &&
					(*it)["Body"].isBool())
					obm->GetGameObject<Sprite>(id)->SetRigidBody();

				//! Body settor
				if ((*it)["Body"].asBool())
				{
					//! Body collider toggle
					if ((*it).isMember("Collider") &&
						(*it)["Collider"].isBool())
						obm->GetGameObject<Sprite>(id)->GetRigidBody()
						->ActivateCollider((*it)["Collider"].asBool());

					//! Body move toggle
					if ((*it).isMember("Move") &&
						(*it)["Move"].isBool())
						obm->GetGameObject<Sprite>(id)->GetRigidBody()
						->ActivateMove((*it)["Move"].asBool());

					//! Body accel
					if ((*it).isMember("Accel") &&
						(*it)["Accel"].isNumeric())
						obm->GetGameObject<Sprite>(id)->GetRigidBody()
						->SetAcceleration((*it)["Accel"].asFloat());

					//! Body force
					if ((*it).isMember("Force") &&
						(*it)["Force"].isArray() &&
						(*it)["Force"].size() == 3 &&
						(*it)["Force"][0].isNumeric())
					{
						obm->GetGameObject<Sprite>(id)
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
						obm->GetGameObject<Sprite>(id)->GetRigidBody()
							->SetScale(vec3(
							(*it)["BodyScale"][0].asFloat(),
							(*it)["BodyScale"][1].asFloat(),
							(*it)["BodyScale"][2].asFloat()));
					}

					//! Body accel
					if ((*it).isMember("Accel") &&
						(*it)["Accel"].isNumeric())
						obm->GetGameObject<Sprite>(id)->GetRigidBody()
						->SetAcceleration((*it)["Accel"].asFloat());

					//! Body mass
					if ((*it).isMember("Mass") &&
						(*it)["Mass"].isNumeric())
						obm->GetGameObject<Sprite>(id)->GetRigidBody()
						->SetMass((*it)["Mass"].asFloat());

					//! Body mass
					if ((*it).isMember("Friction") &&
						(*it)["Friction"].isNumeric())
						obm->GetGameObject<Sprite>(id)->GetRigidBody()
						->SetFriction((*it)["Friction"].asFloat());

					//! Body mass
					if ((*it).isMember("Friction") &&
						(*it)["Friction"].isNumeric())
						obm->GetGameObject<Sprite>(id)->GetRigidBody()
						->SetFriction((*it)["Friction"].asFloat());

					//! Body shape
					if ((*it).isMember("Shape") &&
						(*it)["Shape"].isString())
					{
						if (!strcmp("BALL", (*it)["Shape"].asString().c_str()))
							obm->GetGameObject<Sprite>(id)->GetRigidBody()
							->SetShape(BALL);

						else if (!strcmp("BOX", (*it)["Shape"].asString().c_str()))
							obm->GetGameObject<Sprite>(id)->GetRigidBody()
							->SetShape(BOX);

					}
				}

				if (!strcmp((*it)["Type"].asCString(), "SPRITE"))
					continue;

				else if (!strcmp((*it)["Type"].asCString(), "TEXT"))
				{
					Text* text = static_cast<Text*>(
						obm->GetGameObject<Sprite>(id)); 
					//new Text((*it)["ID"].asInt(), obm);
					
					if ((*it).isMember("Text") &&
						(*it)["Text"].isString())
						text->SetText(m_converter.ConverCtoWC(
						(*it)["Text"].asString().c_str()));
				}

				else if (!strcmp((*it)["Type"].asCString(), "PARTICLE"))
				{
					Emitter* emitter = static_cast<Emitter*>(
						obm->GetGameObject<Sprite>(id));

					if((*it).isMember("EmitterScale") &&
						(*it)["EmitterScale"].isArray() &&
						(*it)["EmitterScale"].size() == 3 &&
						(*it)["EmitterScale"][0].isNumeric())
						emitter->SetScale(vec3(
							(*it)["EmitterScale"][0].asFloat(),
							(*it)["EmitterScale"][1].asFloat(),
							(*it)["EmitterScale"][2].asFloat()));
					
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

						emitter->SetColors(centre, edge);
					}

					if ((*it).isMember("Mode") &&
						(*it)["Mode"].isString())
					{
						// Todo: Preparing...
						//emitter->SetMode();
					}

					if ((*it).isMember("Quantity") &&
						(*it)["Quantity"].isNumeric())
						emitter->SetNumOfParticle((*it)["Quantity"].asInt());

					if((*it).isMember("Direction") &&
						(*it)["Direction"].isArray() &&
						(*it)["Direction"].size() == 3 &&
						(*it)["Direction"][0].isNumeric())
						emitter->SetDirection(vec3(
							(*it)["Direction"][0].asFloat(),
							(*it)["Direction"][1].asFloat(),
							(*it)["Direction"][2].asFloat()));

					if ((*it).isMember("Speed") &&
						(*it)["Speed"].isNumeric())
						emitter->SetSpeed((*it)["Speed"].asFloat());

					if ((*it).isMember("Range") &&
						(*it)["Range"].isNumeric())
						emitter->SetBoundary((*it)["Range"].asFloat());
					
					//new Emitter((*it)["ID"].asInt(), obm);
				}	
			}
		}
	}
}