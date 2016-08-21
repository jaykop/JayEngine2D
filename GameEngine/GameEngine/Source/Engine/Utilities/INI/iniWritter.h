/******************************************************************************/
/*!
\file   iniWritter.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/07/28(yy/mm/dd)

\description
Contains iniWritter class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _INIWRITTER_H_
#define _INIWRITTER_H_

#include "../Math/MathUtils.h"

//! iniWritter class
class iniWritter
{
public:
	
	//! Constuctor
	iniWritter(const char* fileName);

	//! Writting functions
	void WriteInt(char *section, char* key, int DefaultInt);
	void WriteFloat(char *section, char* key, float DefaultFloat);
	void WriteBool(char *section, char* key, bool DefaultBoolean);
	void WriteString(char *section, char* key, const char* DefaultString);

	void WriteVec3(char *section, char* key, const vec3& DefaultVec3);
	void WriteVec4(char *section, char* key, const vec4& DefaultVec4);

	// Todo: Delete this sample code later..
	// Writter sample function
	void WirteSample(void);

private:
	
	// ini file name to write
	char m_fileName[255];

};

#endif _INIWRITTER_H_