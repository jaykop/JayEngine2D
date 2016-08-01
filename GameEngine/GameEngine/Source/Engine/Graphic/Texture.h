/******************************************************************************/
/*!
\file   Texture.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Texture's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../Graphic/GLManager.h"

//! Texture class to load png image
class Texture{

public:
	Texture(void);
	~Texture(void);
	Texture(const Texture& texture);

	// Manage texture info
	void LoadTexture(const char* imagePath);
	GLuint GetTexId(void) const;
	bool IsLoaded(void) const;

private:

	//Texture id
	GLuint m_texID;
	bool m_loded;

};

#endif // _TEXTURE_H_