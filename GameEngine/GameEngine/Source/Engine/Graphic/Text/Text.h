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

//! Text class
class Text : public Sprite
{
public:

	//! Constructor and destructor
	Text(const int id = 0, ObjectManager* obm = 0);
	Text(Text& text);
	virtual ~Text(void);

	//! Font functions
	void SetText(const char* text);
	const std::string& GetText(void) const;

	//void SetFontSize(int size);
	//int GetFontSize(void);

private:

	std::string m_text;
};

#endif // _FREETYPE_TEXT_H_