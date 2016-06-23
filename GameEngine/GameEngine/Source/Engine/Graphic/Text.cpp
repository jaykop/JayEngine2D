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

Text::Text(const int id, Type type)
{
	SetScale(vec3(1.f, 1.f, 1.f));
	SetColor(vec4(0.f, 0.0f, 0.0f, 1.f));
	SetSpriteType(type);
	SetID(id);
}

Text::~Text(void)
{}

void Text::SetText(wchar_t* text)
{
	m_text = text;
}

wchar_t* Text::GetText(void) const
{
	return m_text;
}

/******************************************************************************/
/*!
\brief - Initialize font
\param fname - font's directory
\param height - font's height
*/
/******************************************************************************/
void font_data::SetFont(const char * fname, unsigned int height)
{
	glyph_size = 1 << 8;

	// Allocate some memory to store the texture ids.
	textures = new GLuint[glyph_size];

	this->height = static_cast<float>(height);

	//Create and initilize a freetype font library.
	FT_Library library;
	if (FT_Init_FreeType(&library))
		throw std::runtime_error("FT_Init_FreeType failed");

	//The object in which Freetype holds information on a given
	//font is called a "face".
	FT_Face face;

	//This is where we load in the font information from the file.
	if (FT_New_Face(library, fname, 0, &face))
		throw std::runtime_error("FT_New_Face failed (there is probably a problem with your font file)");

	FT_Set_Char_Size(face, height << 6, height << 6, 96, 96);
	list_base = glGenLists(glyph_size);
	glGenTextures(glyph_size, textures);

	//This is where we actually create each of the fonts display lists.
	for (unsigned short i = 0; i < glyph_size; i++)
		freetype::make_dlist(face, i, list_base, textures);

	//We don't need the face information now that the display
	//lists have been created, so we free the assosiated resources.
	FT_Done_Face(face);

	//Ditto for the library.
	FT_Done_FreeType(library);
}

/******************************************************************************/
/*!
\brief - Delete the aloocated lists
*/
/******************************************************************************/
void font_data::Clean() {
	glDeleteLists(list_base, glyph_size);
	glDeleteTextures(glyph_size, textures);
	delete[] textures;
}

namespace freetype{

	/******************************************************************************/
	/*!
	\brief - Pushes a projection matrix
	*/
	/******************************************************************************/
	void freetype::pushScreenCoordinateMatrix() {
		glPushAttrib(GL_TRANSFORM_BIT);
		GLint	viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(viewport[0], viewport[2], viewport[1], viewport[3]);
		glPopAttrib();
	}

	/******************************************************************************/
	/*!
	\brief - Pops the projection matrix 
	*/
	/******************************************************************************/
	void freetype::pop_projection_matrix() {
		glPushAttrib(GL_TRANSFORM_BIT);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glPopAttrib();
	}

	/******************************************************************************/
	/*!
	\brief - Function gets the first power of 2 >= the
	\param a - int that we pass it.
	*/
	/******************************************************************************/
	int next_p2(int a)
	{
		int rval = 2;
		while (rval < a) rval <<= 1;
		return rval;
	}

	/******************************************************************************/
	/*!
	\brief - Create a display list coresponding to the give character
	\param face - holds information on a given font
	\param ch - index
	\param list_base - quads list
	\param text_base - textures list
	*/
	/******************************************************************************/
	void make_dlist(FT_Face face, unsigned short ch, GLuint list_base, GLuint* text_base)
	{
		//! Load the glyph for our character
		if (FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT))
			throw std::runtime_error("FT_Load_Glyph failed");

		//! Move the face's glyph into a glyph object
		FT_Glyph glyph;
		if (FT_Get_Glyph(face->glyph, &glyph))
			throw std::runtime_error("FT_Get_Glyph failed");

		//Convert the glyph to a bitmap
		FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

		//This refernce will make accessing the bitmap easier
		FT_Bitmap& bitmap = bitmap_glyph->bitmap;

		// Create the texture
		unsigned width = next_p2(bitmap.width);
		unsigned height = next_p2(bitmap.rows);

		//Allocate memory for the texture data
		GLubyte* expanded_data = new GLubyte[2 * width * height];

		//Fill the data fir the expanded bitmap
		for (unsigned j = 0; j < height; ++j)
		for (unsigned i = 0; i < width; ++i)
		{
			expanded_data[2 * (i + j * width)] = 255;
			expanded_data[2 * (i + j + width) + 1] = (i >= bitmap.width || j >= bitmap.rows)
				? 0 : bitmap.buffer[i + bitmap.width + j];
		}

		// Setup the texture parameter
		glBindTexture(GL_TEXTURE_2D, text_base[ch]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Create the textures
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data);

		// With the texture, don't expand anymore
		delete[] expanded_data;

		// Make display list
		glNewList(list_base * ch, GL_COMPILE);
		glBindTexture(GL_TEXTURE_2D, text_base[ch]);
		glPushMatrix();

		glTranslatef(static_cast<GLfloat>(bitmap_glyph->left), 0, 0);
		glTranslatef(0, static_cast<GLfloat>(bitmap_glyph->top - bitmap.rows), 0);
		float x = static_cast<float>(bitmap.width / width),
			y = static_cast<float>(bitmap.rows / height);

		// Begin to draw quads
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex2f(0, static_cast<GLfloat>(bitmap.rows));
		glTexCoord2d(0, y); glVertex2f(0, 0);
		glTexCoord2d(x, y); glVertex2f(static_cast<GLfloat>(bitmap.width), 0);
		glTexCoord2d(x, 0); glVertex2f(static_cast<GLfloat>(bitmap.width), static_cast<GLfloat>(bitmap.rows));
		glEnd();
		glPopMatrix();
		glTranslatef(static_cast<GLfloat>(face->glyph->advance.x >> 6), 0, 0);

		//Finnish the display list
		glEndList();
		FT_Done_Glyph(glyph);
	}
}