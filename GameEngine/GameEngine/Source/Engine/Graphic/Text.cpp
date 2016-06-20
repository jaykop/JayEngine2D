/******************************************************************************/
/*!
\file   Text.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Text's class and member functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Text.h"

void Text::Print(const font_data &ft_font, float x, float y, const char* fmt)
{
	UNREFERENCED_PARAMETER(ft_font);
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);
	UNREFERENCED_PARAMETER(fmt);
}

void Text::Print(TCHAR* string)
{
	for (int index = 0; index < lstrlen(string); ++index)
	{
		FT_Load_Char(m_face, string[index], FT_LOAD_RENDER | FT_LOAD_NO_BITMAP);

		m_width = m_face->glyph->bitmap.width;
		m_height = m_face->glyph->bitmap.rows;

		for (int y = 0; y < m_height; ++y)
		{
			for (int x = 0; x < m_width; ++x)
			{
				m_color = vec4(255 - m_face->glyph->bitmap.buffer[y * m_width + x],
					255 - m_face->glyph->bitmap.buffer[y * m_width + x],
					255 - m_face->glyph->bitmap.buffer[y * m_width + x],
					255 - m_face->glyph->bitmap.buffer[y * m_width + x]);

				if (m_color.x != 255 ||
					m_color.y != 255 ||
					m_color.z != 255 ||
					m_color.w != 255);
			}
		}
	}
}

void Text::SetFont(FT_Library lib, const char* fontDir)
{
	FT_New_Face(lib, fontDir, 0, &m_face);
}

void Text::SetFontSize(HDC hdc, int width, int height)
{
	FT_Set_Char_Size(m_face, 128 * 64, 0, 
		GetDeviceCaps(hdc, LOGPIXELSX), GetDeviceCaps(hdc, LOGPIXELSY));

	m_width = width;
	m_height = height;
}