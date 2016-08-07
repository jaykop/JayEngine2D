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

//#include "GLManager.h"
#include "../Texture/Texture.h"
#include "../../App/Application.h"
#include "../../Utilities/Debug/Debug.h"

/******************************************************************************/
/*!
\brief - GLManager Constructor
*/
/******************************************************************************/
GLManager::GLManager(void)
:m_hdc(0), m_hglrc(0)
{
	//Set projection matrix
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
	ClearTextureMap();
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
\param window - window handle
\return bool
*/
/******************************************************************************/
bool GLManager::CheckGL(Application* pApp, HWND& window)
{
	//Get wnd DC
	m_hdc = GetDC(window);
	if (!m_hdc)
	{
		MessageBox(window, "Failed to get the wnd dc",
			"Device Context Error", MB_OK);

		SysShutdown();
		pApp->Quit();
	}

	//Select pixel format desc
	SetGLFormat();

	//Create the OpenGL rendering context
	m_hglrc = wglCreateContext(m_hdc);
	if (!m_hglrc)
	{
		MessageBox(window, "Failed to Create the OpenGL Rendering Context",
			"OpenGL Rendering Context Error", MB_OK);

		SysShutdown();
		pApp->Quit();
	}

	//Make the OpenGL Rendering context current rc
	if (!wglMakeCurrent(m_hdc, m_hglrc))
	{
		MessageBox(window, "Failed to make OpenGL Rendering Context current",
			"OpenGL Rendering Context Error", MB_OK);

		SysShutdown();
		pApp->Quit();
	}

	//Init GL info
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
\brief - Initialize GL and GLEW information
*/
/******************************************************************************/
void GLManager::InitGL(Application* pApp, HWND& window, int width, int height)
{
	//InitGL
	if (CheckGL(pApp, window))
	{
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			MessageBox(window, "Failed to initialize GLEW",
				"OpenGL GLEW Error", MB_OK);

			pApp->Quit();
		}

		else
		{
			// Init app's size
			Resize(width, height);
			glActiveTexture(GL_TEXTURE0);

			//The VAO
			GLuint VertexArrayID;
			glGenVertexArrays(1, &VertexArrayID);
			glBindVertexArray(VertexArrayID);

			//This will be our vertex buffer
			glGenBuffers(1, &m_vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertex_buffer_data), m_vertex_buffer_data, GL_STATIC_DRAW);

			//first attribute buffer : vertices
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glVertexAttribPointer(
				0,						// must be match the layout in the shader
				3,						// size : X+Y+Z => 3
				GL_FLOAT,				// type
				GL_FALSE,				// normalized
				5 * sizeof(GLfloat),	// stride
				(GLvoid*)0				// array buffer offset
				);

			// 2nd attribute buffer : UVs
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glVertexAttribPointer(
				1,								// attribute. No particular reason for 1, but must match the layout in the shader.
				2,								// size : U+V => 2
				GL_FLOAT,						// type
				GL_TRUE,						// normalized?
				5 * sizeof(GLfloat),			// stride
				(GLvoid*)(3 * sizeof(GLfloat))	// array buffer offset
				);

			//Call shader
			m_shader.LoadShaders("Resource/Shader/shader.vertex", "Resource/Shader/shader.fragment");

			//Use shader
			glUseProgram(m_shader.m_programID);

			// Normal uniforms
			m_uniform[TRANSFORM] = glGetUniformLocation(m_shader.m_programID, "MVP");	//Trasnform Matrix
			m_uniform[UV] = glGetUniformLocation(m_shader.m_programID, "Animation");	//UV
			m_uniform[COLOR] = glGetUniformLocation(m_shader.m_programID, "Color");		//Coloring
			m_uniform[TYPE] = glGetUniformLocation(m_shader.m_programID, "Type");	

			// Set "Texture" sampler to user Texture Unit 0
			m_uniform[TEXTURE] = glGetUniformLocation(m_shader.m_programID, "Texture");
			glUniform1i(m_uniform[TEXTURE], 0);
		}
	}
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
Shader GLManager::GetShader(void) const
{
	return m_shader;
}

/******************************************************************************/
/*!
\brief - Get m_uniform's index

\return m_uniform

*/
/******************************************************************************/
GLuint GLManager::GetUnifrom(UniformType type) const
{
	return m_uniform[type];
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

/******************************************************************************/
/*!
\brief - Initialize font from directory

\param fontDir - font's directory
*/
/******************************************************************************/
void GLManager::SetFont(const char* fontDir, unsigned fontSize)
{
	m_fontSize = fontSize;

	// FreeType
	FT_Library ft;
	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	// Load font as face
	//FT_Face face;
	if (FT_New_Face(ft, fontDir, 0, &m_face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	// Set size to load glyphs as
	FT_Set_Pixel_Sizes(m_face, 0, m_fontSize);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load first 128 characters of ASCII set
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			m_face->glyph->bitmap.width,
			m_face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			m_face->glyph->bitmap.buffer
			);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			vec2(static_cast<float>(m_face->glyph->bitmap.width), static_cast<float>(m_face->glyph->bitmap.rows)),
			vec2(static_cast<float>(m_face->glyph->bitmap_left), static_cast<float>(m_face->glyph->bitmap_top)),
			m_face->glyph->advance.x
		};
		m_chars.insert(std::pair<char, Character>(c, character));
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	// Destroy FreeType once we're finished
	FT_Done_Face(m_face);
	FT_Done_FreeType(ft);
}

/******************************************************************************/
/*!
\brief - Get chracters

\param m_chars - Ascii storage
*/
/******************************************************************************/
Characters GLManager::GetCharacters(void) const
{
	return m_chars;
}

/******************************************************************************/
/*!
\brief - Add texture to the map

\param key - map key
\param dir - directory of texture
*/
/******************************************************************************/
void GLManager::AddTexture(int key, const char* dir)
{
	//Find if there is existing stage 
	//If there is, assert
	DEBUG_ASSERT(m_textureList.find(key) == m_textureList.end(), "Error: Logic Duplication!");

	//Unless, make new builder
	m_textureList[key] = new Texture;
	m_textureList[key]->LoadTexture(dir);
}

/******************************************************************************/
/*!
\brief - Clear all texture map
*/
/******************************************************************************/
void GLManager::ClearTextureMap(void)
{
	for (auto it = m_textureList.begin();
		it != m_textureList.end(); ++it)
	{
		if ((*it).second)
		{
			delete (*it).second;
			(*it).second = 0;
		}
	}

	m_textureList.clear();
}

/******************************************************************************/
/*!
\brief - Get pointer to specific texture
\param key - map key
\return texture
*/
/******************************************************************************/
Texture* GLManager::GetTexture(int key)
{
	// If there is found one,
	// return it
	auto texture = m_textureList.find(key)->second;
	if (texture)
		return texture;

	// Unless, return 0
	return nullptr;
}

/******************************************************************************/
/*!
\brief - Get freetype face
\return m_face
*/
/******************************************************************************/
FT_Face& GLManager::GetFT_Face(void)
{
	return m_face;
}

/******************************************************************************/
/*!
\brief - Get freetype font size
\return m_fontSize
*/
/******************************************************************************/
unsigned GLManager::GetFontSize(void) const
{
	return m_fontSize;
}

///******************************************************************************/
///*!
//\brief - Set freetype font size
//\param fontSize
//*/
///******************************************************************************/
//void GLManager::SetFontSize(unsigned fontSize)
//{
//	m_fontSize = fontSize;
//}