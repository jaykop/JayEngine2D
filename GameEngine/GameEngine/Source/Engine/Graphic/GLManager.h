/******************************************************************************/
/*!
\file   GLManager.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains GLManager's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _GLManager_H_
#define _GLManager_H_

// Basic GL
#pragma comment(lib,"opengl32.lib")
#include "../../../Include/GL/glew.h"
#include "../../../Include//GL/wglew.h"
#include <windows.h>
#include "../../../Include/GL/gl.h"
#include "../../../Include/GL/glu.h"

// Freetype lib
#include <ft2build.h>
#include FT_FREETYPE_H

// Others...
#include <map>
#include "Shader.hpp"
#include "../Utilities/Math/MathUtils.h"

//! vectext buffer information
static const GLfloat m_vertex_buffer_data[] =
{
//		X		Y		Z		U		V
	 -.5f,	 -.5f,	  0.f,	  0.f,	  0.f,	
	 -.5f,	  .5f,	  0.f,	  0.f,	  1.f,	
	  .5f,	  .5f,	  0.f,	  1.f,	  1.f,	 
	  .5f,	 -.5f,	  0.f,	  1.f,	  0.f
};

class Shader;

//! projection info to use in scene class
struct ProjectionInfo
{
	float  m_fovy, m_zNear, m_zFar;
	float  m_width, m_height;
};

///! Holds all state information relevant to a character as loaded using FreeType
struct Character {
	GLuint TextureID; // ID handle of the glyph texture
	vec2 Size;		  // Size of glyph
	vec2 Bearing;	  // Offset from baseline to left/top of glyph
	GLuint Advance;   // Horizontal offset to advance to next glyph
};

//! type definition for list
typedef std::map<wchar_t, Character> Characters;

//! GLManager to manage base GL info
class GLManager
{

public:
	
	GLManager(void);
	~GLManager(void);

	//Settor functions
	void SysShutdown(void);
	void SetGLFormat(void);
	
	//Init GL info
	bool InitGL(void);
	void Resize(int width, int height);
	
	void CheckGL(HWND& window);
	void OpenGLInit(HWND& window, int width, int height);
	
	void SetFont(const char* fontDir);

	//Gettor for GL info
	HDC  GetHDC(void) const;
	Shader GetShader(void) const;
	GLuint GetMatrixID(void) const;
	GLuint GetVertexBuffer(void) const;
	GLuint GetVertexAttrib(void) const;
	Characters GetCharacters(void) const;
	ProjectionInfo GetProjectionInfo(void) const;

	//Single tone pattern
	static GLManager& GetInstance(void)
	{
		static GLManager gl_app;
		return gl_app;
	}

private:

	// Basic info
	HDC    m_hdc;
	HGLRC  m_hglrc;
	int    m_indexPixelFormat;

	// Scene info
	Shader m_shader;
	GLuint m_texId;
	GLuint m_matrixId;
	GLuint m_vertexBuffer;
	GLuint m_vertexAttrib;
	ProjectionInfo m_info;

	// Ascii storage
	Characters m_chars;
	
};

#endif // _GLManager_H_