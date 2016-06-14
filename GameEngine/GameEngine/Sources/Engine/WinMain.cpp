#if defined(DEBUG) | defined (_DEBUG)
#define CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif

#include "Utilities/Debug/Debug.h"
#include "Apps/Application.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h> //WinMain

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
	initData.title = "Game Engine";

	//Start and run my application
	Application app(initData);
	if (app.DataLoaded())
		app.Update();

	DEBUG_DESTROY_CONSOLE();
	//DEBUG_ASSERT(1 == 0 , "This is how u do a custom assert!");
	return 0;
}
