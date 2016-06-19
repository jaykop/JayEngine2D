/******************************************************************************/
/*!
\file   Texture.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Texture's class member functions
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include <vector>
#include <iostream>
#include "Texture.h"
#include "LodePNG\lodepng.h"

/******************************************************************************/
/*!
\brief - Texture constructor

*/
/******************************************************************************/
Texture::Texture(void)
{
	
}

/******************************************************************************/
/*!
\brief - Texture destructor

*/
/******************************************************************************/
Texture::~Texture(void)
{

}

/******************************************************************************/
/*!
\brief - Load PNG fomrat image

\param imagePath - Directory of image to load

*/
/******************************************************************************/
void Texture::LoadTexture(const char* imagePath)
{
	unsigned width, height;
	std::vector<unsigned char> image;

	unsigned error = lodepng::decode(image, width, height, imagePath);
	if (error) std::cerr << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
	
	glGenTextures(1, &m_texID);
	glBindTexture(GL_TEXTURE_2D, m_texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

}

/******************************************************************************/
/*!
\brief - Get texture id

\return m_texID 

*/
/******************************************************************************/
GLuint Texture::GetTexId(void) const
{
	return m_texID;
}
