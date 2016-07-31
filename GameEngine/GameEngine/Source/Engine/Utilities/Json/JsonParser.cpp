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
#include "../../Graphic/Text.h"
#include "../../Graphic/Particle.h"
#include "../../Physics/RigidBody.h"

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
	Json::Reader reader;
	Json::Value root;
	bool parsingRet = reader.parse(str, root);

	if (!parsingRet)
	{
		std::cout << "Failed to parse Json : " << reader.getFormattedErrorMessages();
		return;
	}

	std::cout << root["hasCar"] << " : " << root["age"] << std::endl << std::endl;

	const Json::Value items = root["items"];
	for (unsigned i = 0; i < items.size(); i++)
	{
		std::cout << items[i].asString() << std::endl;
	}
	

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

	Json::Value friends = root["friends"];
	for (auto it = friends.begin(); it != friends.end(); it++)
	{
		if ((*it).isObject())
		{
			std::cout << (*it)["name"] << " : " << (*it)["age"] << std::endl;
		}
	}

	Json::Value a = Load(L"Resource/Data/Sample2.something");
	
	Json::StyledWriter writer;
	str = writer.write(a);
	std::cout << str << std::endl << std::endl;

	//std::cout << a.asString() << std::endl;
}

void JsonParser::Save(const wchar_t* dir, const Json::Value& contents)
{
	std::ofstream save_dir;
	save_dir.open(dir);

	Json::StyledWriter writter;
	save_dir << writter.write(contents);
}

Json::Value JsonParser::Load(wchar_t* dir)
{
	std::ifstream load_dir(dir, std::ifstream::binary);
	Json::Value result;
	load_dir >> result;

	return result;
}

void JsonParser::LoadStage(wchar_t* dir, Scene* scene)
{
	Json::Reader reader;
	Json::Value Stage;
	
	Stage = Load(dir);

	Json::StyledWriter writer;
	str = writer.write(Stage);

	bool parsingRet = reader.parse(str, Stage);

	if (!parsingRet)
	{
		std::cout << "Failed to parse Json : " << reader.getFormattedErrorMessages();
		return;
	}

	// Check if there is stage info
	if (Stage["Stage"].isArray())
	{
		// Set backgroud's color
		if ((*Stage["Stage"].begin()).isMember("Background") &&
			(*Stage["Stage"].begin())["Background"].isArray() &&
			(*Stage["Stage"].begin())["Background"].size() == 4)
				scene->SetBackgroundColor(vec4(
				(*Stage["Stage"].begin())["Background"][0].asFloat(),
				(*Stage["Stage"].begin())["Background"][1].asFloat(),
				(*Stage["Stage"].begin())["Background"][2].asFloat(),
				(*Stage["Stage"].begin())["Background"][3].asFloat()));

		// Set camera's position
		if ((*Stage["Stage"].begin()).isMember("Camera") &&
			(*Stage["Stage"].begin())["Camera"].isArray() &&
			(*Stage["Stage"].begin())["Camera"].size() == 3)
				scene->SetCamera(vec3(
				(*Stage["Stage"].begin())["Camera"][0].asFloat(),
				(*Stage["Stage"].begin())["Camera"][1].asFloat(),
				(*Stage["Stage"].begin())["Camera"][2].asFloat()));
	}
}

Object* JsonParser::LoadObject(const Json::Value& loaded, ObjectManager* obm)
{
	if (loaded.isMember("ID") && loaded.isMember("Type"))
	{
		if (!strcmp(loaded["Type"].asCString(), "SPRITE"))
		{
			Sprite* sprite = new Sprite(loaded["ID"].asInt(), obm);

			//! Set transform
			if (loaded.isMember("Position") &&
				loaded["Position"].isArray() &&
				loaded["Position"].size() == 3 &&
				loaded["Position"][0].isDouble())
			{
				sprite->SetPosition(vec3(
					loaded["Position"][0].asFloat(), 
					loaded["Position"][1].asFloat(),
					loaded["Position"][2].asFloat()));
			}

			if (loaded.isMember("Scale") &&
				loaded["Scale"].isArray() &&
				loaded["Scale"].size() == 3 &&
				loaded["Scale"][0].isDouble())
			{
				sprite->SetScale(vec3(
					loaded["Scale"][0].asFloat(),
					loaded["Scale"][1].asFloat(),
					loaded["Scale"][2].asFloat()));
			}

			if (loaded.isMember("Rotation") &&
				loaded["Rotation"].isDouble())
				sprite->SetRotation(loaded["Scale"].asFloat());
			
			//! Set image(texture)
			if (loaded.isMember("Projection") &&
				loaded["Projection"].isString())
			{
				if (!strcmp(loaded["Projection"].asString().c_str(),
					"ORTHOGONAL"))
					sprite->SetProjectionType(ORTHOGONAL);

				else if (!strcmp(loaded["Projection"].asString().c_str(),
					"PERSPECTIVE"))
					sprite->SetProjectionType(PERSPECTIVE);
			}

			if (loaded.isMember("Color") &&
				loaded["Color"].isArray() &&
				loaded["Color"].size() == 3 &&
				loaded["Color"][0].isDouble())
			{
				sprite->SetColor(vec3(
					loaded["Color"][0].asFloat(),
					loaded["Color"][1].asFloat(),
					loaded["Color"][2].asFloat()));
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

			return sprite;
		}

		else if (!strcmp(loaded["Type"].asCString(), "TEXT"))
		{
			Text* text = new Text(loaded["ID"].asInt(), obm);

			return text;
		}

		else if (!strcmp(loaded["Type"].asCString(), "PARTICLE"))
		{
			Emitter* emitter = new Emitter(loaded["ID"].asInt(), obm);

			return emitter;
		}

	}

	return nullptr;
}