#ifndef _GLAPPLICATION_H_
#define _GLAPPLICATION_H_

#pragma comment(lib,"opengl32.lib")

#include "../../../Includes/GL/glew.h"
#include "../../../Includes//GL/wglew.h"
#include <windows.h>

#include "../../../Includes/GL/gl.h"
#include "../../../Includes/GL/glu.h"

#include "../Graphic/Shader.hpp"

class Shader;

struct ProjectionInfo
{
	float  m_fovy, m_zNear, m_zFar;
	float  m_width, m_height;
};

class GLApplication
{

public:
	
	GLApplication(void);
	~GLApplication(void);

	void SysShutdown(void);
	void SetGLFormat(void);
	
	bool InitGL(void);
	void Resize(int width, int height);
	
	void CheckGL(HWND& window);
	void OpenGLInit(HWND& window, int width, int height);
	
	HDC  GetHDC(void) const;
	Shader GetShader(void) const;
	GLuint GetMatrixID(void) const;
	GLuint GetVertexBuffer(void) const;
	ProjectionInfo GetProjectionInfo(void) const;

	static GLApplication& GetInstance(void)
	{
		static GLApplication gl_app;
		return gl_app;
	}

private:

	HDC    m_hdc;
	HGLRC  m_hglrc;
	int    m_indexPixelFormat;
	Shader m_shader;
	GLuint m_matrixID;
	GLuint m_vertexBuffer;
	ProjectionInfo m_info;
	
};

#endif // _GLAPPLICATION_H_