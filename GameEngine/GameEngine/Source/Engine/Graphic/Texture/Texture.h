/******************************************************************************/
/*!
\file   Texture.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Texture's class and members

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../GLManager/GLManager.h"

//! Texture class to load png image
class Texture{

public:
	Texture(void);
	~Texture(void);
	Texture(const Texture& texture);

	// Manage texture info
	void LoadTexture(const char* imagePath);
	GLuint GetTexId(void) const;

private:

	//Texture id
	GLuint m_texID;

};

#endif // _TEXTURE_H_