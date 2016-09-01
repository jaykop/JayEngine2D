/******************************************************************************/
/*!
\file   GLManager.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains GLManager's class and member functions

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

//#include "GLManager.h"
#include "../Texture/Texture.h"
#include "../../App/Application.h"
#include "../../Utilities/Debug/Debug.h"

GLuint	base;				// Base Display List For The Font Set

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
	m_info.m_zNear = 0.001f;
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
	m_chars.clear();	// Clear loaded font textures
	ClearTextureMap();  // Clear loaded textures

	// Destroy FreeType once we're finished
	FT_Done_Face(m_face);
	FT_Done_FreeType(m_ft);
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
	
	//Prevent the case height = 0
	if (height <= 0) height = 1;

	//Save the data
	m_info.m_width = static_cast<float>(width);
	m_info.m_height = static_cast<float>(height);

	//Get ratio
	GLdouble aspectRatio = (static_cast<GLdouble>(m_info.m_width) / static_cast<GLdouble>(m_info.m_height));

	//Temporary stuff
	glViewport(0, 0, GLsizei(m_info.m_width), GLsizei(m_info.m_height));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(m_info.m_fovy, aspectRatio, m_info.m_zNear, m_info.m_zFar);
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

			// MVP uniforms
			m_uniform[MODEL] = glGetUniformLocation(m_shader.m_programID, "Model");				//Model Matrix
			m_uniform[VIEWPORT] = glGetUniformLocation(m_shader.m_programID, "Viewport");		//Viewport Matrix
			m_uniform[PROJECTION] = glGetUniformLocation(m_shader.m_programID, "Projection");	//Projection Matrix

			// Normal uniforms
			m_uniform[UV] = glGetUniformLocation(m_shader.m_programID, "Animation");	//UV
			m_uniform[COLOR] = glGetUniformLocation(m_shader.m_programID, "Color");		//Coloring
			
			// Sub info
			m_uniform[TYPE] = glGetUniformLocation(m_shader.m_programID, "Type");	//Object Type
			m_uniform[TIME] = glGetUniformLocation(m_shader.m_programID, "Time");	//Engine time

			// Wave info
			m_uniform[WAVE_PHASE] = glGetUniformLocation(m_shader.m_programID, "WavePhase");	//Wave phase
			m_uniform[WAVE_TOGGLE] = glGetUniformLocation(m_shader.m_programID, "WaveToggle");	//Wave boolean
			m_uniform[WAVE_TYPE] = glGetUniformLocation(m_shader.m_programID, "WaveType");		//Wave boolean

			// Manipulation info
			m_uniform[INVERSE_TOGGLE] = glGetUniformLocation(m_shader.m_programID, "InverseToggle");	//Wave boolean

			// Sobel info
			m_uniform[SOBEL_TOGGLE] = glGetUniformLocation(m_shader.m_programID, "SobelToggle");	//Wave boolean
			m_uniform[SOBEL_AMOUNT] = glGetUniformLocation(m_shader.m_programID, "SobelAmount");	//Sobel Amount

			// Blur info
			m_uniform[BLUR_TOGGLE] = glGetUniformLocation(m_shader.m_programID, "BlurToggle");	//Blur boolean
			m_uniform[BLUR_AMOUNT] = glGetUniformLocation(m_shader.m_programID, "BlurAmount");	//Blur Amount

			// Light info
			m_uniform[LIGHT_DIFFUSE] = glGetUniformLocation(m_shader.m_programID, "LightDiff");		// Light Diffuse	
			m_uniform[LIGHT_RADIUS] = glGetUniformLocation(m_shader.m_programID, "LightRadius");	// Light Radius
			m_uniform[LIGHT_DISTANCE] = glGetUniformLocation(m_shader.m_programID, "LightDistance");// Light Distance

			// Emitter info
			m_uniform[EMITTER_TYPE] = glGetUniformLocation(m_shader.m_programID, "Emitter_Type");		// Light Diffuse	
			m_uniform[EMITTER_EXPLO] = glGetUniformLocation(m_shader.m_programID, "Emitter_Explo");	// Light Radius
			m_uniform[EMITTER_BOUND] = glGetUniformLocation(m_shader.m_programID, "Emitter_Bound");// Light Distance
			m_uniform[EMITTER_COLOR] = glGetUniformLocation(m_shader.m_programID, "Emitter_Color");		// Light Diffuse	
			m_uniform[EMITTER_EDGE] = glGetUniformLocation(m_shader.m_programID, "Emitter_EdgeColor");	// Light Radius
			m_uniform[EMITTER_SPD] = glGetUniformLocation(m_shader.m_programID, "Emitter_Spd");// Light Distance
			m_uniform[EMITTER_DIR] = glGetUniformLocation(m_shader.m_programID, "Emitter_Dir");		// Light Diffuse	

			// Particle info
			m_uniform[PARTICLE_SPD] = glGetUniformLocation(m_shader.m_programID, "Particle_Spd");		// Light Diffuse	
			m_uniform[PARTICLE_POS] = glGetUniformLocation(m_shader.m_programID, "Particle_Pos");	// Light Radius
			m_uniform[PARTICLE_VEL] = glGetUniformLocation(m_shader.m_programID, "Particle_Vel");// Light Distance
			m_uniform[PARTICLE_LIFE] = glGetUniformLocation(m_shader.m_programID, "Particle_Life");		// Light Diffuse	
			m_uniform[PARTICLE_FADE] = glGetUniformLocation(m_shader.m_programID, "Particle_Fade");	// Light Radius
			m_uniform[PARTICLE_ROT] = glGetUniformLocation(m_shader.m_programID, "Particle_Rot");// Light Distance
			m_uniform[EMITTER_RNDSCL] = glGetUniformLocation(m_shader.m_programID, "Emitter_RndScl");		// Light Diffuse	

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

	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&m_ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	// Load font as face
	//FT_Face face;
	if (FT_New_Face(m_ft, fontDir, 0, &m_face))
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
}

/******************************************************************************/
/*!
\brief - Get chracters

\param m_chars - Ascii storage
*/
/******************************************************************************/
Characters& GLManager::GetCharacters(void)
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
const FT_Face& GLManager::GetFT_Face(void) const
{
	return m_face;
}

/******************************************************************************/
/*!
\brief - Get freetype face
\return m_face
*/
/******************************************************************************/
const FT_Library& GLManager::GetFT_Lib(void) const
{
	return m_ft;
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

/******************************************************************************/
/*!
\brief - Set freetype font size
\param fontSize
*/
/******************************************************************************/
void GLManager::SetFontSize(unsigned fontSize)
{
	m_fontSize = fontSize;
}

//GLvoid GLManager::BuildFont(GLvoid)								// Build Our Bitmap Font
//{
//	HFONT	font;										// Windows Font ID
//	HFONT	oldfont;									// Used For Good House Keeping
//
//	base = glGenLists(96);								// Storage For 96 Characters
//
//	font = CreateFont(-24,							// Height Of Font
//		0,								// Width Of Font
//		0,								// Angle Of Escapement
//		0,								// Orientation Angle
//		FW_BOLD,						// Font Weight
//		FALSE,							// Italic
//		FALSE,							// Underline
//		FALSE,							// Strikeout
//		ANSI_CHARSET,					// Character Set Identifier
//		OUT_TT_PRECIS,					// Output Precision
//		CLIP_DEFAULT_PRECIS,			// Clipping Precision
//		ANTIALIASED_QUALITY,			// Output Quality
//		FF_DONTCARE | DEFAULT_PITCH,		// Family And Pitch
//		L"Times New Roman");					// Font Name
//
//	oldfont = (HFONT)SelectObject(m_hdc, font);           // Selects The Font We Want
//	wglUseFontBitmaps(m_hdc, 32, 96, base);				// Builds 96 Characters Starting At Character 32
//	SelectObject(m_hdc, oldfont);							// Selects The Font We Want
//	DeleteObject(font);									// Delete The Font
//}
//
//GLvoid GLManager::KillFont(GLvoid)									// Delete The Font List
//{
//	glDeleteLists(base, 96);							// Delete All 96 Characters
//}
//
//GLvoid GLManager::glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
//{
//	glLoadIdentity();									// Reset The Current Modelview Matrix
//	glTranslatef(0.0f, 0.0f, -1.0f);						// Move One Unit Into The Screen
//
//	// Blue Text
//	glColor3ub(0, 0, 0xff);
//
//	// Position The WGL Text On The Screen
//	glRasterPos2f(-0.40f, 0.35f);
//
//	// Here We Print Some Text Using Our FreeType Font
//	// The only really important command is the actual print() call,
//	// but for the sake of making the results a bit more interesting
//	// I have put in some code to rotate and scale the text.
//
//	// Red text
//	glColor3ub(0xff, 0, 0);
//
//	glPushMatrix();
//	glLoadIdentity();
//	glRotatef(0, 0, 0, 1);
//	glScalef(1, 1, 1);
//	glTranslatef(-180, 0, 0);
//
//	char		text[256];								// Holds Our String
//	va_list		ap;										// Pointer To List Of Arguments
//
//	if (fmt == NULL)									// If There's No Text
//		return;											// Do Nothing
//
//	va_start(ap, fmt);									// Parses The String For Variables
//	vsprintf_s(text, fmt, ap);						// And Converts Symbols To Actual Numbers
//	va_end(ap);											// Results Are Stored In Text
//
//	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
//	glListBase(base - 32);								// Sets The Base Character to 32
//	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
//	glPopAttrib();										// Pops The Display List Bits
//	glPopMatrix();
//}