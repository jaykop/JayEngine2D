/******************************************************************************/
/*!
\file   JsonParser.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/07/30(yy/mm/dd)

\description
Contains JsonParser's class and members

All codes are written by Jaykop Jeong...
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
	void Save(const char* dir, const Json::Value& contents);
	void Load(char* dir);

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
	void LoadEffects(Json::Value::iterator& it, Sprite* sprite);

	std::string str;
	Converter m_converter;
	Json::Value m_data;

	Text* new_text;
	Sprite* new_sprite;
	Emitter* new_emitter;

};

#endif