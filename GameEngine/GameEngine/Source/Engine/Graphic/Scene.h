/******************************************************************************/
/*!
\file   Scene.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Scene's class and member
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>
#include <hash_map>
#include "../Graphic/Texture.h"
#include "../Graphic/Text.h"
#include "../Utilities/Math/MathUtils.h"

//Todo: Should I use this or not?
//typedef Vector3<GLfloat> GLvec3;
//typedef Vector4<GLfloat> GLvec4;
//typedef Matrix4x4<GLfloat> GLmat44;

class Text;
class Sprite;
class Application;
class ObjectManager;

///! Holds all state information relevant to a character as loaded using FreeType
struct Character {
	GLuint TextureID; // ID handle of the glyph texture
	vec2 Size;		  // Size of glyph
	vec2 Bearing;	  // Offset from baseline to left/top of glyph
	GLuint Advance;   // Horizontal offset to advance to next glyph
};

//! type definition for list
typedef std::map<wchar_t, Character> Characters;
typedef std::hash_map<int, Sprite*> ObjectList;
typedef std::vector<Sprite*> DrawList;

//! Scene class
class Scene
{
public:

	Scene(Application* pApp);
	~Scene();
	void Init(const ObjectList& objList);
	void Draw(const ObjectList& objList);
	void Shutdown(const ObjectList& objList);

	void SetBackgroundColor(const vec4& background);
	vec4 GetBackgroundColor(void) const;
 	void SetCamera(const vec4& camera);
	vec4 GetCamera(void) const;

	void AddSprite(Sprite* sprite);
	void DeleteSprite(const int id);

private:

	// Private function
	void SetFont(const char* fontDir);
	void Pipeline(const Sprite* sprite);

	// Reorder sprites by z orders
	void ReorderSprites(void);

	void DrawSprites(Sprite* sprite);
	void DrawTexts(Text* text);

	// Math info
	mat44 m_mvp;
	vec4  m_camera;
	vec4  m_bgColor;
	GLuint m_matrixID;

	// screen info
	int	m_width, m_height;
	float aspectRatio;
	float m_zNear, m_zFar, m_fovy;
	float m_radius;

	// Texture info
	Texture m_texture;
	GLuint m_texId;

	// To get GL manager
	Application* m_pApp;

	// Ordered List 
	// Depends on Z order and projection type
	DrawList m_DrawList;
	
	// Shader index
	int shader_index;
	Characters m_chars;
};

#endif // _SCENE_H_