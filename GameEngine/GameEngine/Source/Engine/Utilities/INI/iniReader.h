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

class iniReader
{
public:
	iniReader(const wchar_t* fileName);
	~iniReader();
	int ReadInt(wchar_t *section, wchar_t* key, int DefaultInt);
	float ReadFloat(wchar_t *section, wchar_t* key, float DefaultFloat);
	bool ReadBool(wchar_t *section, wchar_t* key, bool DefaultBoolean);
	wchar_t* ReadString(wchar_t *section, wchar_t* key, const wchar_t* DefaultString);

private:

	wchar_t m_fileName[255];
	wchar_t* m_stringResulet;

};

#endif _INIREADER_H_