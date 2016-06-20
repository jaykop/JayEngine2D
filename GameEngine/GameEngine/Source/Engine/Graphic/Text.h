/******************************************************************************/
/*!
\file   Text.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/20(yy/mm/dd)

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

class Text
{
public:

	Text();
	~Text(void);


	struct font_data {
		float  height;
		GLuint *texture;	//Texture *texture;
		GLuint list_base;

		font_data(void);
		~font_data(void);

		void Make_dlist(FT_Face face, char ch, GLuint list_base, GLuint* tex_base);
		void SetFont(const char* fontDir
			= "Resource/Font/Default.ttf", unsigned size = 36);

		int Next_p2(int a);
		void Clear(void);
	};

	//void Print(TCHAR* string);
	//void Print(const font_data &ft_font, float x, float y, const char* fmt);

	//void SetFontSize(HDC hdc, int width, int height);

private:

	vec3 m_scale;
	vec4 m_color;
	vec3 m_position;
	float m_rotation;
	float m_fontSize;

	FT_Face m_face;
	font_data m_font;
};

#endif // _FREETYPE_TEXT_H_