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

//! iniWritter class
class iniWritter
{
public:
	iniWritter(const wchar_t* fileName);
	void WriteInt(wchar_t *section, wchar_t* key, int DefaultInt);
	void WriteFloat(wchar_t *section, wchar_t* key, float DefaultFloat);
	void WriteBool(wchar_t *section, wchar_t* key, bool DefaultBoolean);
	void WriteString(wchar_t *section, wchar_t* key, const wchar_t* DefaultString);

private:
	
	// ini file name to write
	wchar_t m_fileName[255];

};

#endif _INIWRITTER_H_