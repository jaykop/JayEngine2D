/******************************************************************************/
/*!
\file   Shader.hpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Shader's class and members
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _SHADER_HPP
#define _SHADER_HPP

//! Shader class
class Shader{
public:

	Shader();
	~Shader();

	// Load shader
	void LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

	GLuint m_programID;

private:

};

#endif