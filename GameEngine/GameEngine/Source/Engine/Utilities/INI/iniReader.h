/******************************************************************************/
/*!
\file   iniReader.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/07/28(yy/mm/dd)

\description
Contains iniReader class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _INIREADER_H_
#define _INIREADER_H_

#include "../Math/MathUtils.h"

//! iniReader class
class iniReader
{
public:

	iniReader(const wchar_t* fileName);
	~iniReader();
	int ReadInt(wchar_t *section, wchar_t* key);
	float ReadFloat(wchar_t *section, wchar_t* key);
	bool ReadBool(wchar_t *section, wchar_t* key);
	wchar_t* ReadString(wchar_t *section, wchar_t* key);

	vec3 ReadVec3(wchar_t *section, wchar_t* key);
	vec4 ReadVec4(wchar_t *section, wchar_t* key);

private:

	wchar_t m_fileName[255];	// ini file name to read
	wchar_t* m_stringResult;	// temp string storage

};

#endif _INIREADER_H_