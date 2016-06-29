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

class Text;
class Sprite;
class Particle;
class ObjectManager;
class GameStateManager;

typedef std::hash_map<int, Sprite*> ObjectList;
typedef std::vector<Sprite*> DrawList;

//! Scene class
class Scene
{
public:

	Scene(GameStateManager* gsm);
	~Scene();

	void Init(const ObjectList& objList);
	void Update(const ObjectList& objList);
	void Shutdown(const ObjectList& objList);

	void SetBackgroundColor(const vec4& background);
	vec4 GetBackgroundColor(void) const;
 	void SetCamera(const vec4& camera);
	vec4 GetCamera(void) const;

	void AddSprite(Sprite* sprite);
	void DeleteSprite(const int id);

private:

	// Private functions

	// Manage transform and animation info
	void Pipeline(Sprite* sprite);

	// Reorder sprites by z orders
	void ReorderSprites(void);

	// Draw sprites
	void DrawTexts(Text* text);
	void DrawSprites(Sprite* sprite);
	void DrawParticle(Particle* particle);

	// Set mouse position
	void GetPerspPosition(void);
	void GetOrthoPosition(void);

	// Math(by sprites) info
	mat44 m_mvp;	
	vec4  m_camera;
	vec4  m_bgColor;
	mat44 m_animation;
	
	// Screen info
	int	m_width, m_height;
	float aspectRatio;
	float m_zNear, m_zFar, m_fovy;
	float m_radius;

	// To get GSM
	GameStateManager* m_GSM;

	// Ordered List 
	DrawList m_DrawList;
};

#endif // _SCENE_H_