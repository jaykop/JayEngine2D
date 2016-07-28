/******************************************************************************/
/*!
\file   iniWritter.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/07/28(yy/mm/dd)

\description
Contains iniWritter member function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "iniWritter.h"
#include <iostream>
#include <cstdio>
#include <atlstr.h>

/******************************************************************************/
/*!
\brief - iniWritter Constructor
\param fileName - fileName to write
*/
/******************************************************************************/
iniWritter::iniWritter(const wchar_t* fileName)
{
	// Get file name
	wmemset(m_fileName, 0x00, 255);
	wmemcpy(m_fileName, fileName, wcslen(fileName));
}

/******************************************************************************/
/*!
\brief - Write int to ini file
\param section
\param key
\param DefaultInt - int to write
*/
/******************************************************************************/
void iniWritter::WriteInt(wchar_t *section, wchar_t* key, int DefaultInt)
{
	wchar_t value[255];
	wsprintf(value, L"%d", DefaultInt);
	WritePrivateProfileString(section, key, value, m_fileName);
}

/******************************************************************************/
/*!
\brief - Write float to ini file
\param section
\param key
\param DefaultFloat - float to write
*/
/******************************************************************************/
void iniWritter::WriteFloat(wchar_t *section, wchar_t* key, float DefaultFloat)
{
	wchar_t value[255];
	_stprintf_s(value, L"%f", DefaultFloat);
	WritePrivateProfileString(section, key, value, m_fileName);
}

/******************************************************************************/
/*!
\brief - Write boolean to ini file
\param section
\param key
\param DefaultBoolean - boolean to write
*/
/******************************************************************************/
void iniWritter::WriteBool(wchar_t *section, wchar_t* key, bool DefaultBoolean)
{
	wchar_t value[255];
	wsprintf(value, L"%s", DefaultBoolean ? L"True" : L"False");
	WritePrivateProfileString(section, key, value, m_fileName);
}

/******************************************************************************/
/*!
\brief - Write string to ini file
\param section
\param key
\param DefaultString - string to write
*/
/******************************************************************************/
void iniWritter::WriteString(wchar_t *section, wchar_t* key, const wchar_t* DefaultString)
{
	WritePrivateProfileString(section, key, DefaultString, m_fileName);
}