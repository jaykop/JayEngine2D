/******************************************************************************/
/*!
\file   GLManager.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains GLManager's class and member functions
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "GLManager.h"
#include "../App/Application.h"

/******************************************************************************/
/*!
\brief - GLManager Constructor
*/
/******************************************************************************/
GLManager::GLManager(void)
{
	//Set projection matrix
	m_hdc = 0;
	m_hglrc = 0;
	m_info.m_width = 0;
	m_info.m_height = 0;
	m_info.m_zNear = 0.1f;
	m_info.m_zFar = 100.f;
	m_info.m_fovy = 45.f;
}

/******************************************************************************/
/*!
\brief - GLManager Destructor
*/
/******************************************************************************/
GLManager::~GLManager(void)
{
	// Nothing here
}

/******************************************************************************/
/*!
\brief - Resize the projection screen

\param width - Screen's width
\param height - Screen's height
*/
/******************************************************************************/
void GLManager::Resize(int width, int height)
{
	//Resize screen size

	//Save the data
	m_info.m_width = static_cast<float>(width);
	m_info.m_height = static_cast<float>(height);

	//Prevent the case height = 0
	if (m_info.m_height <= 0) m_info.m_height = 1;

	//Get ratio
	float aspectRatio = (m_info.m_width / m_info.m_height);

	//Temporary stuff
	glViewport(0, 0, GLsizei(m_info.m_width), GLsizei(m_info.m_height));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspectRatio, 0.1f, 100.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/******************************************************************************/
/*!
\brief - Shutdown app when gl is not properly loaded
*/
/******************************************************************************/
void GLManager::SysShutdown(void)
{
	//release current device context
	wglMakeCurrent(m_hdc, NULL);

	//delete rendering context
	wglDeleteContext(m_hglrc);

	//make sure the window will be destroyed
	PostQuitMessage(0);
}

/******************************************************************************/
/*!
\brief - Set GL's pixel format
*/
/******************************************************************************/
void GLManager::SetGLFormat(void)
{
	//number of available format
	m_indexPixelFormat = 0;
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		32,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		16,
		0, 0, 0, 0, 0, 0, 0
	};

	//Choose the closest pixel format abailable
	m_indexPixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	
	//Set the pixel format for the provided window DC
	SetPixelFormat(m_hdc, m_indexPixelFormat, &pfd);
}

/******************************************************************************/
/*!
\brief - Check if gl is either not properly loaded or not
*/
/******************************************************************************/
void GLManager::CheckGL(HWND& window)
{
	//Get wnd DC
	m_hdc = GetDC(window);
	if (!m_hdc)
	{
		MessageBox(window, L"Failed to get the wnd dc",
			L"Device Context Error", MB_OK);

		SysShutdown();
	}

	//Select pixel format desc
	SetGLFormat();

	//Create the OpenGL rendering context
	m_hglrc = wglCreateContext(m_hdc);
	if (!m_hglrc)
	{
		MessageBox(window, L"Failed to Create the OpenGL Rendering Context",
			L"OpenGL Rendering Context Error", MB_OK);

		SysShutdown();
	}

	//Make the OpenGL Rendering context current rc
	if (!wglMakeCurrent(m_hdc, m_hglrc))
	{
		MessageBox(window, L"Failed to make OpenGL Rendering Context current",
			L"OpenGL Rendering Context Error", MB_OK);

		SysShutdown();
	}
}

/******************************************************************************/
/*!
\brief - Initialize GL information

\return true
*/
/******************************************************************************/
bool GLManager::InitGL(void)
{
	//InitGL
	glShadeModel(GL_SMOOTH);
	glShadeModel(GL_LINE_SMOOTH_HINT);
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);

	return true;
}

/******************************************************************************/
/*!
\brief - Initialize GLEW information
*/
/******************************************************************************/
void GLManager::OpenGLInit(HWND& window, int width, int height)
{
	CheckGL(window);

	//InitGL
	if (InitGL())
	{
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			MessageBox(window, L"Failed to initialize GLEW",
				L"OpenGL GLEW Error", MB_OK);
		}
	}

	Resize(width, height);

	//The VAO
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//This will be our vertex buffer
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertex_buffer_data), m_vertex_buffer_data, GL_STATIC_DRAW);

	//Call shader
	m_shader[0].LoadShaders("Resource/Shader/shader.vertex", "Resource/Shader/shader.fragment");
	m_shader[1].LoadShaders("Resource/Shader/text.vertex", "Resource/Shader/text.fragment");

	//Use shader
	glUseProgram(m_shader[0].m_programID);
	//glUseProgram(m_shader[1].m_programID);

}

/******************************************************************************/
/*!
\brief - Get device context handle

\return m_hdc 

*/
/******************************************************************************/
HDC GLManager::GetHDC(void) const
{
	return m_hdc;
}

/******************************************************************************/
/*!
\brief - Get projectionInfo

\return m_info - initialized projection information

*/
/******************************************************************************/
ProjectionInfo GLManager::GetProjectionInfo(void) const
{
	return m_info;
}

/******************************************************************************/
/*!
\brief - Get shader

\return m_shader

*/
/******************************************************************************/
Shader GLManager::GetShader(const int id) const
{
	return m_shader[id];
}

/******************************************************************************/
/*!
\brief - Get matrix's ID

\return m_matrixId

*/
/******************************************************************************/
GLuint GLManager::GetMatrixID(void) const
{
	return m_matrixId;
}

/******************************************************************************/
/*!
\brief - Get vertex buffer

\return m_vertexBuffer

*/
/******************************************************************************/
GLuint GLManager::GetVertexBuffer(void) const
{
	return m_vertexBuffer;
}

/******************************************************************************/
/*!
\brief - Get vertex attribute

\return m_vertexAttrib

*/
/******************************************************************************/
GLuint GLManager::GetVertexAttrib(void) const
{
	return m_vertexAttrib;
}