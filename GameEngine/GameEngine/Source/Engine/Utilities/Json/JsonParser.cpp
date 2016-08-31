/******************************************************************************/
/*!
\file   JsonParser.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/07/30(yy/mm/dd)

\description
Contains JsonParser's class and member function

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

#include <fstream>
#include <iostream>

//#include "JsonParser.h"
#include "../../Graphic/Scene/Scene.h"
#include "../../Graphic/Light/Light.h"
#include "../../Graphic/Light/Darkness.h"
#include "../../Graphic/Particle/Particle.h"
#include "../../Physics/RigidBody/RigidBody.h"
#include "../../Logic/GameLogic/GameLogic.h"
#include "../../Logic/LogicFactory/LogicFactory.h"
#include "../../Sound/SoundManager/SoundManager.h"

/******************************************************************************/
/*!
\brief - JsonParser Constructor
*/
/******************************************************************************/
JsonParser::JsonParser()
:new_text(0), new_emitter(0), new_sprite(0)
{}

/******************************************************************************/
/*!
\brief - JsonParser Destructor
*/
/******************************************************************************/
JsonParser::~JsonParser()
{}

/******************************************************************************/
/*!
\brief - Get loaded data
\return m_data
*/
/******************************************************************************/
const Json::Value& JsonParser::GetLoadedData(void) const
{
	return m_data;
}

/******************************************************************************/
/*!
\brief - Save data as json file
\param dir - directory to save json file
\param contents - json vaule
*/
/******************************************************************************/
void JsonParser::Save(const char* dir, const Json::Value& contents)
{
	std::ofstream save_dir;
	save_dir.open(dir);

	Json::StyledWriter writter;
	save_dir << writter.write(contents);
}

/******************************************************************************/
/*!
\brief - Load data from json file
\param dir - directory to load json file
*/
/******************************************************************************/
void JsonParser::Load(char* dir)
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

/******************************************************************************/
/*!
\brief - Init asset data to use in engine
\param GLM - Pointer to gl manager
\param SM - Pointer to sound manager
*/
/******************************************************************************/
void JsonParser::InitAssetData(GLManager* GLM, SoundManager* SM)
{
	// Load font
	if (m_data.isMember("Font"))
	{
		for (auto it = m_data["Font"].begin();
			it != m_data["Font"].end(); ++it)
		{
			if ((*it).isMember("size") &&
				(*it)["size"].isInt() &&
				(*it).isMember("directory") &&
				(*it)["directory"].isString())
				GLM->SetFont((*it)["directory"].asCString(), (*it)["size"].asUInt());
		}
	}

	// Alarm Error
	else
		std::cerr << "Cannot load font file!\n";

	// Load textures
	if (m_data.isMember("Texture"))
	{
		for (auto it = m_data["Texture"].begin();
			it != m_data["Texture"].end(); ++it)
		{
			if ((*it).isMember("key") &&
				(*it)["key"].isInt() &&
				(*it).isMember("directory") &&
				(*it)["directory"].isString())
					GLM->AddTexture((*it)["key"].asInt(), (*it)["directory"].asCString());
		}
	}

	// Alarm Error
	else
		std::cerr << "Cannot load texture files!\n";

	// Load Sound
	if (m_data.isMember("Sound"))
	{
		for (auto it = m_data["Sound"].begin();
			it != m_data["Sound"].end(); ++it)
		{
			if ((*it).isMember("key") &&
				(*it)["key"].isInt() &&
				(*it).isMember("directory") &&
				(*it)["directory"].isString())
					SM->AddSound((*it)["key"].asInt(), (*it)["directory"].asCString());
		}
	}

	// Alarm Error
	else
		std::cerr << "Cannot load sound files!\n";
}

/******************************************************************************/
/*!
\brief - Count how many sounds to be loaded.
		 This is to init fmod properly.
\return quantity
*/
/******************************************************************************/
int JsonParser::CheckLoadedSounds(void)
{
	int quantity = 0;
	if (m_data.isMember("Sound"))
	{
		for (auto it = m_data["Sound"].begin();
			it != m_data["Sound"].end(); ++it)
		{
			if ((*it).isMember("key") &&
				(*it)["key"].isInt() &&
				(*it).isMember("directory") &&
				(*it)["directory"].isString())
					++quantity;
		}
	}

	return quantity;
}

/******************************************************************************/
/*!
\brief - Init Loaded Data on game stage
\parma obm 
*/
/******************************************************************************/
void JsonParser::InitLoadedData(ObjectManager* obm)
{
	// Load stage and objects
	LoadStage(obm->GetGameScene());
	LoadObjects(obm);
}

/******************************************************************************/
/*!
\brief - Init scene info from json file
\parma scene
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief - Init object info from json file
\parma obm
*/
/******************************************************************************/
void JsonParser::LoadObjects(ObjectManager* obm)
{
	// Check if there is proper object info
	if (m_data["Object"].isArray())
	{
		// Loop for all objects in the stage
		for (auto it = m_data["Object"].begin();
			it != m_data["Object"].end(); 
			++it)
		{
			// Check type and id
			if ((*it).isMember("Type") &&
				(*it).isMember("ID") && 
				(*it)["ID"].isInt())
			{
				// Now set basic info by its type
				int id = (*it)["ID"].asInt();

				// Sprite case or Object case
				if (!strcmp((*it)["Type"].asCString(), "SPRITE"))
				{
					obm->AddObject(new Sprite(id, obm));
					LoadBasicObject(it, obm->GetGameObject<Sprite>(id));
				}

				// Darkness case
				else if (!strcmp((*it)["Type"].asCString(), "DARKNESS"))
				{
					obm->AddObject(new Darkness(id, obm));
					LoadBasicObject(it, obm->GetGameObject<Darkness>(id));
				}

				// Light case
				else if (!strcmp((*it)["Type"].asCString(), "LIGHT"))
				{
					auto new_Light = new Light(id, obm);

					if ((*it).isMember("Diffuse") &&
						(*it)["Diffuse"].isArray() &&
						(*it)["Diffuse"].size() == 3 &&
						(*it)["Diffuse"][0].isNumeric())
					{
						new_Light->SetDiffuse(vec3(
							(*it)["Diffuse"][0].asFloat(),
							(*it)["Diffuse"][1].asFloat(),
							(*it)["Diffuse"][2].asFloat()));
					}

					if ((*it).isMember("Distance") &&
						(*it)["Distance"].isNumeric())
						new_Light->SetDistance((*it)["Distance"].asFloat());

					if ((*it).isMember("Radius") &&
						(*it)["Radius"].isNumeric())
						new_Light->SetRadius((*it)["Radius"].asFloat());
					
					LoadBasicObject(it, new_Light);
					obm->AddObject(new_Light);
				}

				// Text case
				else if (!strcmp((*it)["Type"].asCString(), "TEXT"))
				{
					auto new_Text = new Text(id, obm);
					
					if ((*it).isMember("Text") &&
						(*it)["Text"].isString())
						new_Text->SetText((*it)["Text"].asCString());

					if ((*it).isMember("FontSize") &&
						(*it)["FontSize"].isInt())
						new_Text->SetFontSize((*it)["FontSize"].asUInt());

					LoadBasicObject(it, new_Text);
					obm->AddObject(new_Text);
				}

				// Particle(Emitter) case
				else if (!strcmp((*it)["Type"].asCString(), "PARTICLE"))
				{
					auto new_Emitter = new Emitter(id, obm);

					if ((*it).isMember("Quantity") &&
						(*it)["Quantity"].isNumeric())
						new_Emitter->SetNumOfParticle((*it)["Quantity"].asInt());

					if ((*it).isMember("Projection") &&
						(*it)["Projection"].isString())
					{
						if (!strcmp((*it)["Projection"].asCString(),
							"ORTHOGONAL"))
							new_Emitter->SetProjectionType(ORTHOGONAL);

						else if (!strcmp((*it)["Projection"].asCString(),
							"PERSPECTIVE"))
							new_Emitter->SetProjectionType(PERSPECTIVE);
					}

					if ((*it).isMember("Scale") &&
						(*it)["Scale"].isArray() &&
						(*it)["Scale"].size() == 3 &&
						(*it)["Scale"][0].isNumeric())
					{
						new_Emitter->SetScale(vec3(
							(*it)["Scale"][0].asFloat(),
							(*it)["Scale"][1].asFloat(),
							(*it)["Scale"][2].asFloat()));
					}

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

						new_Emitter->SetColors(centre, edge);

					}

					if ((*it).isMember("Spin") &&
						(*it)["Spin"].isBool())
						new_Emitter->ActivateRotate((*it)["Spin"].asBool());

					if ((*it).isMember("Mode") &&
						(*it)["Mode"].isString())
					{
						if (!strcmp((*it)["Mode"].asCString(), "NORMAL"))
							new_Emitter->SetMode(NORMAL);
						else if (!strcmp((*it)["Mode"].asCString(), "FIRE"))
							new_Emitter->SetMode(FIRE);
						else if (!strcmp((*it)["Mode"].asCString(), "EXPLOSION"))
							new_Emitter->SetMode(EXPLOSION);
						else if (!strcmp((*it)["Mode"].asCString(), "SNOW"))
						{
							new_Emitter->SetMode(SNOW);
							if ((*it).isMember("SnowStart") &&
								(*it)["SnowStart"].isArray() &&
								(*it)["SnowStart"].size() == 3 &&
								(*it)["SnowStart"][0].isNumeric() &&
								(*it).isMember("SnowEnd") &&
								(*it)["SnowEnd"].isArray() &&
								(*it)["SnowEnd"].size() == 3 &&
								(*it)["SnowEnd"][0].isNumeric())
							{
								new_Emitter->SetSnowBoundary(
									vec3((*it)["SnowStart"][0].asFloat(), (*it)["SnowStart"][1].asFloat(), (*it)["SnowStart"][2].asFloat()),
									vec3((*it)["SnowEnd"][0].asFloat(), (*it)["SnowEnd"][1].asFloat(), (*it)["SnowEnd"][2].asFloat()));
							}
						}
					}

					if((*it).isMember("Direction") &&
						(*it)["Direction"].isArray() &&
						(*it)["Direction"].size() == 3 &&
						(*it)["Direction"][0].isNumeric())
						new_Emitter->SetDirection(vec3(
							(*it)["Direction"][0].asFloat(),
							(*it)["Direction"][1].asFloat(),
							(*it)["Direction"][2].asFloat()));

					if ((*it).isMember("RandomScale") &&
						(*it)["RandomScale"].isBool())
					{
						bool randomScaleToggle = (*it)["RandomScale"].asBool();
						new_Emitter->ActivateRandomScale(
							randomScaleToggle);

						if (randomScaleToggle &&
							(*it).isMember("RandomRange") &&
							(*it)["RandomRange"].isArray() &&
							(*it)["RandomRange"].size() == 2 &&
							(*it)["RandomRange"][0].isNumeric())
							new_Emitter->SetRandomScaleRange(vec2(
							(*it)["RandomRange"][0].asFloat(),
							(*it)["RandomRange"][1].asFloat()));
					}

					if ((*it).isMember("Speed") &&
						(*it)["Speed"].isNumeric())
						new_Emitter->SetSpeed((*it)["Speed"].asFloat());

					if ((*it).isMember("Range") &&
						(*it)["Range"].isNumeric())
						new_Emitter->SetBoundary((*it)["Range"].asFloat());

					LoadBasicObject(it, new_Emitter);
					obm->AddObject(new_Emitter);
				}	

				// Load logics
				if ((*it).isMember("Logic"))
					LoadLogics(it, obm->GetGameObject<Object>(id));

				// Load effects
				if ((*it).isMember("Effect"))
					LoadEffects(it, obm->GetGameObject<Sprite>(id));
			}
		}
	}
}

/******************************************************************************/
/*!
\brief - Init basic sprite info from json file
\parma it - iterator from json value
\param sprite - pointer to sprite to set
*/
/******************************************************************************/
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
	if (sprite->GetType() != PARTICLE &&
		(*it).isMember("Projection") &&
		(*it)["Projection"].isString())
	{
		if (!strcmp((*it)["Projection"].asCString(),
			"ORTHOGONAL"))
			sprite->SetProjectionType(ORTHOGONAL);

		else if (!strcmp((*it)["Projection"].asCString(),
			"PERSPECTIVE"))
			sprite->SetProjectionType(PERSPECTIVE);
	}

	if (sprite->GetType() != TEXT &&
		(*it).isMember("Texture") &&
		(*it)["Texture"].isInt())
		sprite->SetTexture(sprite->GetOBM()->GetGSM()->GetGLManager()->GetTexture((*it)["Texture"].asInt()));

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

		//! Body collider toggle
		if ((*it).isMember("Response") &&
			(*it)["Response"].isBool())
			sprite->GetRigidBody()
			->ActivateResponse((*it)["Response"].asBool());

		//! Body accel
		if ((*it).isMember("Acce") &&
			(*it)["Acce"].isNumeric())
			sprite->GetRigidBody()
			->SetAcceleration((*it)["Acce"].asFloat());

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
			{
				sprite->GetRigidBody()
					->SetShape(BALL);
				sprite->SetTexture(sprite->GetOBM()->GetGSM()->GetGLManager()->GetTexture(1));
			}

			else if (!strcmp("BOX", (*it)["Shape"].asCString()))
				sprite->GetRigidBody()
				->SetShape(BOX);
		}
	}
}

/******************************************************************************/
/*!
\brief - Init logic to object
\parma it - iterator from json value
\param Object - pointer to Object to set
*/
/******************************************************************************/
void JsonParser::LoadLogics(Json::Value::iterator& it, Object* object)
{
	for (auto logic = (*it)["Logic"].begin();
		logic != (*it)["Logic"].end(); ++logic)
	{
		if ((*logic).isMember("key"))
		{
			GameLogic* newLogic = LogicFactory::CreateLogic((*logic)["key"].asInt(), object);
			if (newLogic)
			{
				if ((*logic).isMember("values"))
				{
					newLogic->Load((*logic)["values"]);
					object->AddLogic(newLogic);
				}
			}
			else std::cerr << "Error: Cannot make new logic" << (*logic)["key"].asInt() << std::endl;
		}
	}
}

/******************************************************************************/
/*!
\brief - Init effects to sprite
\parma it - iterator from json value
\param Object - pointer to Object to set
*/
/******************************************************************************/
void JsonParser::LoadEffects(Json::Value::iterator& it, Sprite* sprite)
{
	for (auto effect = (*it)["Effect"].begin();
		effect != (*it)["Effect"].end(); ++effect)
	{
		if ((*effect).isMember("type") &&
			(*effect)["type"].isString())
		{
			if (!strcmp((*effect)["type"].asCString(), "WAVE"))
			{
				sprite->AddEffect(WAVE);
				if ((*effect).isMember("values"))
				{
					auto value = (*effect)["values"];
					if (value.isMember("Toggle") &&
						value["Toggle"].isNumeric())
						sprite->GetEffect(WAVE)->ActivateWaveToggle(value["Toggle"].asBool());

					if (value.isMember("Phase") &&
						value["Phase"].isArray() &&
						value["Phase"].size() == 2 &&
						value["Phase"][0].isNumeric())
					{
						sprite->GetEffect(WAVE)->SetWavePhase(vec2(
							value["Phase"][0].asFloat(),
							value["Phase"][1].asFloat()));
					}
				}
			}

			else if (!strcmp((*effect)["type"].asCString(), "BLUR"))
			{
				sprite->AddEffect(BLUR);

				//Todo: Other effect..
				if ((*effect).isMember("values"))
				{
					auto value = (*effect)["values"];
					if (value.isMember("Toggle") &&
						value["Toggle"].isNumeric())
						sprite->GetEffect(BLUR)->ActivateBlurToggle(value["Toggle"].asBool());

					if (value.isMember("Amount") &&
						value["Amount"].isNumeric())
						sprite->GetEffect(BLUR)->SetBlurAmount(value["Amount"].asFloat());
					
				}
			}

			else if (!strcmp((*effect)["type"].asCString(), "SOBEL"))
			{
				sprite->AddEffect(SOBEL);
				sprite->GetEffect(SOBEL)->ActivateSobelToggle(true);

				//Todo: Other effect..
				if ((*effect).isMember("values"))
				{
					auto value = (*effect)["values"];
					if (value.isMember("Toggle") &&
						value["Toggle"].isNumeric())
						sprite->GetEffect(SOBEL)->ActivateSobelToggle(value["Toggle"].asBool());

					if (value.isMember("Amount") &&
						value["Amount"].isNumeric())
						sprite->GetEffect(SOBEL)->SetSobelAmount(value["Amount"].asFloat());
				}
			}

			else if (!strcmp((*effect)["type"].asCString(), "MANIPULATION"))
			{
				sprite->AddEffect(MANIPULATION);
				sprite->GetEffect(MANIPULATION)->ActivateManipToggle(true);

				//Todo: Other effect..
				if ((*effect).isMember("values"))
				{
					auto value = (*effect)["values"];
				}
			}

			else std::cerr << "Error: Cannot make new effect" << (*effect)["type"].asCString() << std::endl;
		}
	}
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
	Save("Resource/Data/Sample2.something", root);
}