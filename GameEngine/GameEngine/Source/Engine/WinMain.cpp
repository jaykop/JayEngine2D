/******************************************************************************/
/*!
\file   WinMain.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains WinMain function

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#if defined(DEBUG) | defined (_DEBUG)
#define CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif

#include "Utilities/Debug/Debug.h"
#include "Apps/Application.h"
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

	//Values to init my application from main, these could be read from a file
	InitData initData;
	initData.instance = instance;
	initData.isFullScreen = false;
	initData.scrSize.height = 768;
	initData.scrSize.width = 1280;
	initData.title = TEXT("Game Engine");

	//Start and run my application
	Application app(initData);
	if (app.DataLoaded())
		app.Update();

	DEBUG_DESTROY_CONSOLE();

	return 0;
}
