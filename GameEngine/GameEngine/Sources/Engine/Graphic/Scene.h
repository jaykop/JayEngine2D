#ifndef _SCENE_H_
#define _SCENE_H_

#include "../Graphic/Texture.h"
#include "../Utilities/Math/MathUtils.h"

//Separate ortho and persp sprites into 2 lists. 
//#include <hash_map>

//Todo: Should I use this or not?
//typedef Vector3<GLfloat> GLvec3;
//typedef Vector4<GLfloat> GLvec4;
//typedef Matrix4x4<GLfloat> GLmat44;

class ObjectManager;
class Application;
class Sprite;

//Graphic scene
class Scene
{
public:

	Scene(Application* pApp);
	~Scene();
	void Init(const ObjectManager& ObjM);
	void Draw(const ObjectManager& ObjM);
	void Shutdown();

	void SetBackgroundColor(const vec4& background);
	vec4 GetBackgroundColor(void) const;
 	void SetCamera(const vec4& camera);
	vec4 GetCamera(void) const;

private:

	// Private function
	void Pipeline(const Sprite& sprite);

	// Reorder sprites by z orders
	void ReorderSprites(const ObjectManager* ObjM);
	bool reorder_sprites(const Sprite* a, const Sprite* b);

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

	Texture m_texture;
	GLuint m_texId;

	Application* m_pApp;

	std::vector<std::pair<int, Sprite*>> m_orthoList;	// Ortho sprites hashmap
	std::vector<std::pair<int, Sprite*>> m_perspList;	// Persp sprites hashmap

	// Todo: Separate ortho and persp sprites into 2 lists.
	// Todo: Set drawing order sprites' z value
	// 2 vector
	
};

#endif // _SCENE_H_