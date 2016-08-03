/******************************************************************************/
/*!
\file   JsonParser.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/07/30(yy/mm/dd)

\description
Contains JsonParser's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _JSONPARSER_H_
#define _JSONPARSER_H_

#include "json/json.h"
#include "../Converter.h"

class Text;
class Sprite;
class Emitter;

class Scene;
class Object;
class GLManager;
class SoundManager;
class ObjectManager;

//! Json Parser class
class JsonParser{

public:
	JsonParser();
	~JsonParser();
	
	void write_sample(void);

	//! Save and load file containing information
	void Save(const wchar_t* dir, const Json::Value& contents);
	void Load(wchar_t* dir);

	int  CheckLoadedSounds(void);
	void InitAssetData(GLManager* GLM, SoundManager* SM);
	void InitLoadedData(ObjectManager* obm);
	const Json::Value& GetLoadedData(void) const;

private:

	//! Inner helper functions
	void LoadStage(Scene* scene);
	void LoadObjects(ObjectManager* obm);
	void LoadBasicObject(Json::Value::iterator& it, Sprite* sprite);
	void LoadLogics(Json::Value::iterator& it, Object* object);

	std::string str;
	Converter m_converter;
	Json::Value m_data;

	Text* new_text;
	Sprite* new_sprite;
	Emitter* new_emitter;

};

#endif