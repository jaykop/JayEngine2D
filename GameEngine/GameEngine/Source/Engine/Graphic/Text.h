/******************************************************************************/
/*!
\file   Text.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Text's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _FREETYPE_TEXT_H_
#define _FREETYPE_TEXT_H_

// Freetype headers
#include <ft2build.h>
#include <freetype.h>
#include <ftglyph.h>
#include <ftoutln.h>
#include <fttrigon.h>

// GL headers
#include <windows.h>                                     
#include "../Include/GL/gl.h"
#include "../Include/GL/glu.h"

// STL headers
#include <vector>
#include <string>
#include <stdexcept>

#pragma warning(disable: 4786)

#include "../Utilities/Math/MathUtils.h"

using namespace std;

struct font_data {
	float height;
	GLuint *texture;
	GLuint list_base;

	void init(const char* font_name, unsigned height);
	void clean(void);
};

class Text
{
public:

	void Print(TCHAR* string);
	void Print(const font_data &ft_font, float x, float y, const char* fmt);
	void SetFont(FT_Library lib, const char* fontDir
		 = "Resource/Font/Default.ttf");
	void SetFontSize(HDC hdc, int width, int height);

private:

	FT_Face m_face;
	int m_width, m_height;
	vec4 m_color;
};

#endif // _FREETYPE_TEXT_H_