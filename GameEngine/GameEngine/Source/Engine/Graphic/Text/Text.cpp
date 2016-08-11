/******************************************************************************/
/*!
\file   Text.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/20(yy/mm/dd)

\description
Contains Text's class and member functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Text.h"
#include "../GLManager/GLManager.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../StateManager/GameStateManager/GameStateManager.h"

/******************************************************************************/
/*!
\brief - Sprite's Constructor
*/
/******************************************************************************/
Text::Text(const int id, ObjectManager* obm)
:Sprite(id, obm)
{
	// Get ft data from gl manager
	m_data.m_face = GetOBM()->GetGSM()->GetGLManager()->GetFT_Face();
	m_data.m_ftlib = GetOBM()->GetGSM()->GetGLManager()->GetFT_Lib();
	m_data.m_chars = GetOBM()->GetGSM()->GetGLManager()->GetCharacters();
	m_data.m_fontSize = GetOBM()->GetGSM()->GetGLManager()->GetFontSize();

	//SetID(id);
	SetType(TEXT);
	//SetObjectManager(obm); 
	SetProjectionType(ORTHOGONAL);
	SetScale(vec3(1.f, 1.f, 1.f));
	SetColor(vec4(0.f, 0.0f, 0.0f, 1.f));
}
/******************************************************************************/
/*!
\brief - Text's Copy Constructor
*/
/******************************************************************************/
Text::Text(Text& text)
:Sprite(text)
{
	//m_fontSize = text.m_fontSize;
	m_text.assign(text.m_text);
}

/******************************************************************************/
/*!
\brief - Text's Destructor
*/
/******************************************************************************/
Text::~Text(void)
{
	ClearLogicList();
	m_data.m_chars.clear();
}

/******************************************************************************/
/*!
\brief - Set text
\param text
*/
/******************************************************************************/
void Text::SetText(const char* text, ...)
{
	va_list ap;

	if (text == NULL)
		m_text.assign(0);

	else {
		va_start(ap, text);
		vsprintf_s(m_textStorage, text, ap);
		va_end(ap);

		m_text = m_textStorage;
	}
}

/******************************************************************************/
/*!
\brief - Get text
\return m_text
*/
/******************************************************************************/
const std::string& Text::GetText(void) const
{
	return m_text;
}

/******************************************************************************/
/*!
\brief - Set text font size
\param size
*/
/******************************************************************************/
void Text::SetFontSize(int size)
{
	m_data.m_chars.clear();

	FT_Set_Pixel_Sizes(m_data.m_face, 0, size);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load first 128 characters of ASCII set
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(m_data.m_face, c, FT_LOAD_RENDER))
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
			m_data.m_face->glyph->bitmap.width,
			m_data.m_face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			m_data.m_face->glyph->bitmap.buffer
			);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			vec2(static_cast<float>(m_data.m_face->glyph->bitmap.width),
			static_cast<float>(m_data.m_face->glyph->bitmap.rows)),
			vec2(static_cast<float>(m_data.m_face->glyph->bitmap_left),
			static_cast<float>(m_data.m_face->glyph->bitmap_top)),
			m_data.m_face->glyph->advance.x
		};
		m_data.m_chars.insert(std::pair<char, Character>(c, character));
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	m_data.m_fontSize = size;
}

/******************************************************************************/
/*!
\brief - Get text font size
\return fontSize
*/
/******************************************************************************/
unsigned Text::GetFontSize(void)
{
	return m_data.m_fontSize;
}

FontData& Text::GetFontData(void)
{
	return m_data;
}

void Text::SetFontData(const FT_Face& face, const FT_Library& lib)
{
	m_data.m_face = face;
	m_data.m_ftlib = lib;
}