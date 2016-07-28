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

#include "iniReader.h"
#include <iostream>
#include <Windows.h>

iniReader::iniReader(const wchar_t* fileName)
{
	// Get file name
	wmemset(m_fileName, 0x00, 255);
	wmemcpy(m_fileName, fileName, wcslen(fileName));
}

iniReader::~iniReader()
{
	delete[] m_stringResulet;
}

int iniReader::ReadInt(wchar_t *section, wchar_t* key, int DefaultInt)
{
	int iResult = GetPrivateProfileInt(section, key, DefaultInt, m_fileName);
	return iResult;
}

float iniReader::ReadFloat(wchar_t *section, wchar_t* key, float DefaultFloat)
{
	wchar_t Result[255];
	wchar_t Default[255];
	wsprintf(Default, L"%f", DefaultFloat);
	GetPrivateProfileString(section, key, Default, Result, 255, m_fileName);
	float fltResult = wcstof(Result, NULL);
	return fltResult;
}

bool iniReader::ReadBool(wchar_t *section, wchar_t* key, bool DefaultBoolean)
{
	wchar_t Result[255];
	wchar_t Default[255];
	wsprintf(Default, L"%s", DefaultBoolean ? L"True" : L"False");
	GetPrivateProfileString(section, key, Default, Result, 255, m_fileName);
	bool bolResult = (wcscmp(Result, L"True") == 0 ||
		wcscmp(Result, L"true") == 0) ? true : false;
	return bolResult;
}

wchar_t* iniReader::ReadString(wchar_t *section, wchar_t* key, const wchar_t* DefaultString)
{
	m_stringResulet = new wchar_t[255];
	memset(m_stringResulet, 0x00, 255);
	 GetPrivateProfileString(section, key, 
		 DefaultString, m_stringResulet, 255, m_fileName);
	 return m_stringResulet;
}