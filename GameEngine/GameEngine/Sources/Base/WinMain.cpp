#if defined(DEBUG) | defined (_DEBUG)
#define CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif

#include "Debug/Debug.h"
#include "Apps/Application.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h> //WinMain

/*Because of this macro, this function can only be called once*/
void Test(void)
{
	DEBUG_CALL_CHECK();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE /*prev*/, 
	LPSTR /*command line*/, int /*show*/)
{
	DEBUG_LEAK_CHECKS(-1);
	DEBUG_CREATE_CONSOLE();

	//Values to init my application from main, these could be read from a file
	GhostEngine::InitData initData;
	initData.instance = instance;
	initData.isFullScreen = false;
	initData.height = 720;
	initData.width = 1280;
	initData.title = "Game Engine";

	//Start and run my application
	GhostEngine::Application app(initData);
	app.Update();

	DEBUG_DESTROY_CONSOLE();
	//DEBUG_ASSERT(1 == 0 , "This is how u do a custom assert!");
	return 0;
}
