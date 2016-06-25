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

class ObjectManager;

//! Text class
class Text : public Sprite
{
public:

	//! Constructor and destructor
	Text(const int id = 0, Type type = TEXT, ObjectManager* obm = 0);
	virtual ~Text(void);

	//! Font functions
	void SetText(const wchar_t* text);
	const std::wstring& GetText(void) const;

private:

	std::wstring m_text;
	float m_fontSize;

};

#endif // _FREETYPE_TEXT_H_