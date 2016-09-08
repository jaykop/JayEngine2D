/******************************************************************************/
/*!
\file   Scene.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Scene's class and member

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>
#include <unordered_map>
#include "../Texture/Texture.h"

class Text;
class Light;
class Sprite;
class Emitter;
class Particle;
class ObjectManager;
class GameStateManager;

typedef std::unordered_map<int, Sprite*> ObjectList;
typedef std::vector<Sprite*> DrawList;

//! Scene class
class Scene
{
public:

	Scene(GameStateManager* gsm);
	~Scene();

	void Init(const ObjectList& objList);
	void Update(const ObjectList& objList, float dt);
	void Shutdown(const ObjectList& objList);

	void SetBackgroundColor(const vec4& background);
	vec4 GetBackgroundColor(void) const;
 	void SetCamera(const vec4& camera);
	vec4 GetCamera(void) const;

	void AddSprite(Sprite* sprite);
	void RemoveSprite(const int id);

	// Set mouse position
	void GetPerspPosition(void);
	void GetOrthoPosition(void);

private:

	// Private functions
	// Manage transform and animation info
	void Pipeline(Sprite* sprite, float dt);

	// Reorder sprites by z orders
	void ReorderSprites(void);

	// Draw sprites
	void DrawTexts(Text* text);
	void DrawLights(Light* light);
	void DrawSprites(Sprite* sprite);
	void DrawParticle(Emitter* emitter, float dt);

	void UpdateParticle(Particle* particle);
	void RenderParticle(Particle* particle);
	void RefreshParticle(Particle* particle);

	GLuint  instancedVBO;
	GLint location;
	GLint location2;
	GLint location3;

	// Math(by sprites) info
	vec4  m_camera;
	vec4  m_bgColor;
	vec2  m_phase;
	mat44 m_animation;
	
	// Screen info
	GLfloat m_width, m_height;
	GLfloat aspectRatio;
	GLfloat m_zNear, m_zFar, m_fovy;
	float m_radius;

	// Darkness toggle
	bool m_darkness;
	float m_maxlightZ;

	// To get GSM
	GameStateManager* m_GSM;

	// Ordered List 
	DrawList m_DrawList;
};

#endif // _SCENE_H_