/******************************************************************************/
/*!
\file   WinMain.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains WinMain function

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/

#if defined(DEBUG) | defined (_DEBUG)
#define CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif

#include "Utilities/Debug/Debug.h"
#include "Utilities/INI/iniReader.h"
#include "App/Application.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h> //WinMain

/******************************************************************************/
/*!
\brief - Main window function

\param instance

\return 0 

*/
/******************************************************************************/
int WINAPI WinMain(HINSTANCE instance, HINSTANCE /*prev*/, 
	LPSTR /*command line*/, int /*show*/)
{
	DEBUG_LEAK_CHECKS(-1);
	DEBUG_CREATE_CONSOLE();

	//! Set default values
	char* Title = "Demo Engine";
	int Resolution = 1;
	bool ScreenMode = true;

	//! Load ini setting values
	iniReader LoadSetting("Resource/Data/Settings.ini");
	Title = LoadSetting.ReadString("Setting", "Title");
	Resolution = LoadSetting.ReadInt("Setting", "Resolution");
	ScreenMode = LoadSetting.ReadBool("Setting", "FullScreen");
	
	//! Values to init my application from main, these could be read from a file
	InitData initData;
	initData.instance = instance;

	//! Set title and screen mode
	initData.title = Title;
	initData.isFullScreen = ScreenMode;

	//! Set screen size
	switch (Resolution)
	{
	case 1: 
		initData.scrSize = SCR_640X480;
		break;
	case 2: 
		initData.scrSize = SCR_800X600;
		break;
	case 3: 
		initData.scrSize = SCR_1024X768;
		break;
	case 4: 
		initData.scrSize = SCR_1280X1024;
		break;
	case 5: 
		initData.scrSize = SCR_1920X1080;
		break;
	default: 
		initData.scrSize = SCR_640X480;
		break;
	}

	//Start and run my application
	Application app(initData);
	if (app.DataLoaded())
		app.Update();

	DEBUG_DESTROY_CONSOLE();

	return 0;
}
