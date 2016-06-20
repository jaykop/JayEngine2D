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

Text::Text(void)
:m_position(vec3()), m_scale(vec3(1, 1, 0)), 
m_rotation(0), m_color(vec4(1, 1, 1, 1))
{}

Text::~Text(void)
{}

Text::font_data::font_data(void)
{
	SetFont();
}

int Text::font_data::Next_p2(int a)
{
	int rval = 1;
	while (rval < a) rval << 1;
	return rval;
}

void Text::font_data::SetFont(const char* fontDir, unsigned size)
{
	texture = new GLuint[256];
	this->height = float(size);
	
	FT_Library lib;
	if (FT_Init_FreeType(&lib))
		throw std::runtime_error("FT_Init_FreeType failed!");

	FT_Face face = 0;
	if (FT_New_Face(lib, fontDir, 0, &face))
		throw std::runtime_error("FT_New_Face failed (there is probably a problem with font file)");

	FT_Set_Char_Size(face, size << 6, size << 6, 96, 96);
	list_base = glGenLists(256);

	glGenTextures(256, (GLuint*)texture);
	for (unsigned char i = 0; i < 256; ++i)
		Make_dlist(face, i, list_base, (GLuint*)&texture);

	FT_Done_Face(face);
	FT_Done_FreeType(lib);
}

Text::font_data::~font_data(void)
{
	Clear();
}

void Text::font_data::Clear(void)
{
	glDeleteLists(list_base, 256);
	glDeleteTextures(256, (GLuint*)&texture);
	delete[] texture;
}

void Text::font_data::Make_dlist(FT_Face face, char ch, GLuint list_base, GLuint* tex_base)
{
	if (FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT))
		throw std::runtime_error("FT_Load_Glyph failed");

	FT_Glyph glyph;
	if (FT_Get_Glyph(face->glyph, &glyph))
		throw std::runtime_error("FT_Load_Glyph failed");

	FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
	FT_BitmapGlyph bitmap_glyph = FT_BitmapGlyph(glyph);
	FT_Bitmap& bitmap = bitmap_glyph->bitmap;

	int width = Next_p2(bitmap.width);
	int height = Next_p2(bitmap.rows);

	GLubyte* expanded_data = new GLubyte[2 * width * height];

}

//void Text::Print(const font_data &ft_font, float x, float y, const char* fmt)
//{
//	UNREFERENCED_PARAMETER(ft_font);
//	UNREFERENCED_PARAMETER(x);
//	UNREFERENCED_PARAMETER(y);
//	UNREFERENCED_PARAMETER(fmt);
//}

//void Text::Print(TCHAR* string)
//{
//	for (int index = 0; index < lstrlen(string); ++index)
//	{
//		FT_Load_Char(m_face, string[index], FT_LOAD_RENDER | FT_LOAD_NO_BITMAP);
//
//		m_width = m_face->glyph->bitmap.width;
//		m_height = m_face->glyph->bitmap.rows;
//
//		for (int y = 0; y < m_height; ++y)
//		{
//			for (int x = 0; x < m_width; ++x)
//			{
//				m_color = vec4(255 - m_face->glyph->bitmap.buffer[y * m_width + x],
//					255 - m_face->glyph->bitmap.buffer[y * m_width + x],
//					255 - m_face->glyph->bitmap.buffer[y * m_width + x],
//					255 - m_face->glyph->bitmap.buffer[y * m_width + x]);
//
//				if (m_color.x != 255 ||
//					m_color.y != 255 ||
//					m_color.z != 255 ||
//					m_color.w != 255)
//					SetPixelV(hdc, penx + x, y, RGB(m_color.x, m_color.y, m_color.z, m_color.w));
//			}
//		}
//	}
//}
//
//void Text::SetFont(FT_Library lib, const char* fontDir)
//{
//	
//}
//
//void Text::SetFontSize(HDC hdc, int width, int height)
//{
//	FT_Set_Char_Size(m_face, 128 * 64, 0, 
//		GetDeviceCaps(hdc, LOGPIXELSX), GetDeviceCaps(hdc, LOGPIXELSY));
//
//	m_width = width;
//	m_height = height;
//}