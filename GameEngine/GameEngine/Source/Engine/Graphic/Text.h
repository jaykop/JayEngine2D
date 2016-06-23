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

// STL headers
#include <vector>
#include <string>
#include <stdexcept>

#pragma warning(disable: 4786)

// GL headers
#include <map>
#include "Sprite.h"

//This holds all of the information related to any
//freetype font that we want to create.  
struct font_data {

	int glyph_size;		///< Font's size
	float height;		///< Holds the height of the font.
	GLuint * textures;	///< Holds the texture id's 
	GLuint list_base;	///< Holds the first display list id

	//The init function will create a font of
	//of the height h from the file fname.
	void SetFont(const char * fname, unsigned int height);

	//Free all the resources assosiated with the font.
	void Clean();
};

namespace freetype{

	int next_p2(int a);
	void make_dlist(FT_Face face, unsigned short ch, GLuint list_base, GLuint* text_base);
	void pushScreenCoordinateMatrix(void);
	void pop_projection_matrix(void);

	static font_data m_font;
}

//! Text class
class Text : public Sprite
{
public:

	//! Constructor and destructor
	Text(const int id = 0, Type type = TEXT);
	~Text(void);

	//! Font functions
	virtual void SetText(wchar_t* text);
	virtual wchar_t* GetText(void) const;

private:

	wchar_t* m_text;
	float m_fontSize;

};

#endif // _FREETYPE_TEXT_H_