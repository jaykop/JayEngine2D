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

#include <string>
#include "../Sprite/Sprite.h"

class ObjectManager;

//! FontData struct
struct FontData{
	FT_Face m_face;
	FT_Library m_ftlib;
	Characters m_chars;
	unsigned m_fontSize;
};

//! Text class
class Text : public Sprite
{
public:

	//! Constructor and destructor
	Text(const int id = 0, ObjectManager* obm = 0);
	Text(Text& text);
	virtual ~Text(void);

	//! Text functions
	void SetText(const char* text);
	const std::string& GetText(void) const;

	//! Font size functions 
	void SetFontSize(int size);
	unsigned GetFontSize(void);

	//! Font data functions
	FontData& GetFontData(void);
	void SetFontData(const FT_Face& face, const FT_Library& lib);

private:

	std::string m_text;
	FontData m_data;
};

#endif // _FREETYPE_TEXT_H_