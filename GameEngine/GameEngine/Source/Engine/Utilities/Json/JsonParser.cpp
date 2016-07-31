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
	//Json::Reader reader;
	//Json::Value root;
	//bool parsingRet = reader.parse(str, root);

	//if (!parsingRet)
	//{
	//	std::cout << "Failed to parse Json : " << reader.getFormattedErrorMessages();
	//	return;
	//}

	//std::cout << root["hasCar"] << " : " << root["age"] << std::endl << std::endl;

	//const Json::Value items = root["items"];
	//for (unsigned i = 0; i < items.size(); i++)
	//{
	//	std::cout << items[i].asString() << std::endl;
	//}
	

	//auto member = root.getMemberNames();

	//for (std::string s : member)
	//{
	//	std::cout << s << std::endl;
	//}
	//std::cout << std::endl;

	//for (std::string s : member)
	//{
	//	if (root[s].isString())
	//	{
	//		std::cout << root[s] << std::endl;
	//	}
	//}
	//std::cout << std::endl;

	//Json::Value friends = root["friends"];
	//for (auto it = friends.begin(); it != friends.end(); it++)
	//{
	//	if ((*it).isObject())
	//	{
	//		std::cout << (*it)["name"] << " : " << (*it)["age"] << std::endl;
	//	}
	//}

	//Json::Value a = Load(L"Resource/Data/Sample2.something");
	//
	//Json::StyledWriter writer;
	//str = writer.write(a);
	//std::cout << str << std::endl << std::endl;

	//std::cout << a.asString() << std::endl;
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
			if ((*it).isMember("ID") && (*it).isMember("Type"))
			{
				if (!strcmp((*it)["Type"].asCString(), "SPRITE"))
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

					//sprite->SetAnimation();

					//// Set physics
					//sprite->SetRigidBody();
					//sprite->GetRigidBody()->ActivateCollider();
					//sprite->GetRigidBody()->ActivateMove();
					//sprite->GetRigidBody()->SetAcceleration();
					//sprite->GetRigidBody()->SetForce();
					//sprite->GetRigidBody()->SetFriction();
					//sprite->GetRigidBody()->SetMass();
					//sprite->GetRigidBody()->SetScale();
					//sprite->GetRigidBody()->SetShape();

					//return sprite;
				}

				else if (!strcmp((*it)["Type"].asCString(), "TEXT"))
				{
					//Text* text = new Text((*it)["ID"].asInt(), obm);

					//return text;
				}

				else if (!strcmp((*it)["Type"].asCString(), "PARTICLE"))
				{
					//Emitter* emitter = new Emitter((*it)["ID"].asInt(), obm);

					//return emitter;
				}

			}
		}
	}
}