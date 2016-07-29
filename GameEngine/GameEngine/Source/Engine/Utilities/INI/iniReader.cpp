/******************************************************************************/
/*!
\file   iniReader.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/07/28(yy/mm/dd)

\description
Contains iniReader member function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include <iostream>
#include <Windows.h>
#include "iniReader.h"

/******************************************************************************/
/*!
\brief - iniReader Constructor
\param fileName - fileName to write
*/
/******************************************************************************/
iniReader::iniReader(const wchar_t* fileName)
{
	// Get file name
	wmemset(m_fileName, 0x00, 255);
	wmemcpy(m_fileName, fileName, wcslen(fileName));
}

/******************************************************************************/
/*!
\brief - iniReader Destructor
*/
/******************************************************************************/
iniReader::~iniReader()
{
	// Delete temp dynamic new
	delete [] m_stringResult;
}

/******************************************************************************/
/*!
\brief - Read int to ini file
\param section
\param key
\param DefaultInt - int to read
\return iResult
*/
/******************************************************************************/
int iniReader::ReadInt(wchar_t *section, wchar_t* key)
{
	int DefaultInt = 0;
	int iResult = GetPrivateProfileInt(section, key, DefaultInt, m_fileName);
	return iResult;
}

/******************************************************************************/
/*!
\brief - Read float to ini file
\param section
\param key
\param DefaultFloat - float to read
\return fltResult
*/
/******************************************************************************/
float iniReader::ReadFloat(wchar_t *section, wchar_t* key)
{
	float DefaultFloat = 0.f;
	wchar_t Result[255];
	wchar_t Default[255];
	wsprintf(Default, L"%f", DefaultFloat);
	GetPrivateProfileString(section, key, Default, Result, 255, m_fileName);
	float fltResult = wcstof(Result, NULL);
	return fltResult;
}

/******************************************************************************/
/*!
\brief - Read bool to ini file
\param section
\param key
\param DefaultBoolean - bool to read
\return bolResult
*/
/******************************************************************************/
bool iniReader::ReadBool(wchar_t *section, wchar_t* key)
{
	bool DefaultBoolean = false;
	wchar_t Result[255];
	wchar_t Default[255];
	wsprintf(Default, L"%s", DefaultBoolean ? L"True" : L"False");
	GetPrivateProfileString(section, key, Default, Result, 255, m_fileName);
	bool bolResult = (wcscmp(Result, L"True") == 0 ||
		wcscmp(Result, L"true") == 0) ? true : false;
	return bolResult;
}

/******************************************************************************/
/*!
\brief - Read string to ini file
\param section
\param key
\param DefaultString - string to read
\return m_stringResult
*/
/******************************************************************************/
wchar_t* iniReader::ReadString(wchar_t *section, wchar_t* key)
{
	const wchar_t* DefaultString = L"";
	m_stringResult = new wchar_t[255];
	memset(m_stringResult, 0x00, 255);
	 GetPrivateProfileString(section, key, 
		 DefaultString, m_stringResult, 255, m_fileName);
	 return m_stringResult;
}

/******************************************************************************/
/*!
\brief - Read vec3 to ini file
\param section
\param key
\param DefaultBoolean - vec3 to read
*/
/******************************************************************************/
vec3 iniReader::ReadVec3(wchar_t *section, wchar_t* key)
{
	vec3 vec3Result;
	const vec3 DefaultVec3;
	wchar_t Result[2][255];
	wchar_t Default[255];

	wsprintf(Default, L"%f", DefaultVec3);
	GetPrivateProfileString(section, key, Default, Result[0], 255, m_fileName);
	for (int index = 0, fill = 0; index < sizeof(Result[0]) || fill < 3; ++index)
	{
		wchar_t pt[2] = { Result[0][index], '\0' };

		if (!wcscmp(pt, L" "))
		{
			wcscpy_s(Result[1], (Result[0] + index + 1));
			if (fill == 0) vec3Result.x = wcstof(Result[1], NULL);
			else if (fill == 1) vec3Result.y = wcstof(Result[1], NULL);
			else if (fill == 2) vec3Result.z = wcstof(Result[1], NULL);
			++fill;
		}
	}

	return vec3Result;
}

/******************************************************************************/
/*!
\brief - Read vec4 to ini file
\param section
\param key
\param DefaultBoolean - vec4 to read
*/
/******************************************************************************/
vec4 iniReader::ReadVec4(wchar_t *section, wchar_t* key)
{
	vec4 vec4Result;
	const vec4 DefaultVec4;
	wchar_t Result[2][255];
	wchar_t Default[255];

	wsprintf(Default, L"%f", DefaultVec4);
	GetPrivateProfileString(section, key, Default, Result[0], 255, m_fileName);
	
	for (int index = 0, fill = 0; index < sizeof(Result[0]) && fill < 4; ++index)
	{
		wchar_t pt[2] = { Result[0][index], '\0' };

		if (!wcscmp(pt, L" "))
		{
			wcscpy_s(Result[1], (Result[0] + index + 1));
			if (fill == 0)
				vec4Result.x = wcstof(Result[1], NULL);
			else if (fill == 1) 
				vec4Result.y = wcstof(Result[1], NULL);
			else if (fill == 2) 
				vec4Result.z = wcstof(Result[1], NULL);
			else if (fill == 3) 
				vec4Result.w = wcstof(Result[1], NULL);
			++fill;
		}
	}

	return vec4Result;
}