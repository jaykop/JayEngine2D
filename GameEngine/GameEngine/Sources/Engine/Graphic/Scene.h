#ifndef _SCENE_H_
#define _SCENE_H_

#include "../Apps/GLApplication.h"
#include "../Utilities/Math/MathUtils.h"

//Separate ortho and persp sprites into 2 lists. 
//#include <hash_map>

//Todo: Should I use this or not?
//typedef Vector3<GLfloat> GLvec3;
//typedef Vector4<GLfloat> GLvec4;
//typedef Matrix4x4<GLfloat> GLmat44;

class ObjectManager;
class Sprite;

//Graphic scene
class Scene
{
public:

	Scene();
	~Scene();
	void Init();
	void Draw(const ObjectManager& ObjM);
	void Shutdown();

	void SetBackgroundColor(const vec4& background);
	vec4 GetBackgroundColor(void) const;
 	void SetCamera(const vec4& camera);
	vec4 GetCamera(void) const;

private:

	// Private function
	void Pipeline(const Sprite& sprite);

	// Math info
	mat44 m_mvp;
	vec4  m_camera;
	vec4  m_bgColor;
	GLuint m_matrixID;

	// screen info
	int	m_width, m_height;
	float aspectRatio;
	float m_zNear, m_zFar, m_fovy;

	// Separate ortho and persp sprites into 2 lists.
	// 2 vector
	
};

#endif // _SCENE_H_