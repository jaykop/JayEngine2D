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

iniWritter::iniWritter(const wchar_t* fileName)
{
	// Get file name
	wmemset(m_fileName, 0x00, 255);
	wmemcpy(m_fileName, fileName, wcslen(fileName));
	//CreateNewFileAsUTF16(fileName);
}

DWORD iniWritter::CreateNewFileAsUTF16(IN LPCTSTR lpszFilePath)
{
	HANDLE  hFile = INVALID_HANDLE_VALUE;
	DWORD   wBOM = 0xFEFF;
	DWORD   dwCbWritten = 0;

	hFile = ::CreateFile(lpszFilePath,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		return ::GetLastError();
	}

	::WriteFile(hFile,
		&wBOM,
		sizeof(WORD),
		&dwCbWritten,
		NULL);

	::CloseHandle(hFile);
	hFile = INVALID_HANDLE_VALUE;

	//LPTSTR pszSectionBOM = TEXT("[UseBOM]");

	//::WriteFile(hFile, &wBOM, sizeof(WORD), &dwCbWritten, NULL);
	//::WriteFile(hFile, pszSectionBOM, (wcslen(pszSectionBOM) + 1)*(sizeof(TCHAR)),
	//	&dwCbWritten, NULL);

	return ERROR_SUCCESS;
}

void iniWritter::WriteInt(wchar_t *section, wchar_t* key, int DefaultInt)
{
	wchar_t value[255];
	wsprintf(value, L"%d", DefaultInt);
	WritePrivateProfileString(section, key, value, m_fileName);
}

void iniWritter::WriteFloat(wchar_t *section, wchar_t* key, float DefaultFloat)
{
	wchar_t value[255];
	_stprintf_s(value, L"%f", DefaultFloat);
	WritePrivateProfileString(section, key, value, m_fileName);
}

void iniWritter::WriteBool(wchar_t *section, wchar_t* key, bool DefaultBoolean)
{
	wchar_t value[255];
	wsprintf(value, L"%s", DefaultBoolean ? L"True" : L"False");
	WritePrivateProfileString(section, key, value, m_fileName);
}

void iniWritter::WriteString(wchar_t *section, wchar_t* key, const wchar_t* DefaultString)
{
	WritePrivateProfileString(section, key, DefaultString, m_fileName);
}