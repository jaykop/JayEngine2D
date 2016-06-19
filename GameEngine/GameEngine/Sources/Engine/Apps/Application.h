/******************************************************************************/
/*!
\file   Application.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Application's class and members
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef APPLICATION_H
#define APPLICATION_H

#define WIN32_LEAN_AND_MEAN
#include "../Graphic/GLManager.h"
#include "../StateManager/GameStateManager/GameStateManager.h"

using namespace Resolution;

//! Used in main to give initial values to the application.
struct InitData
{
	const char* title;
	HINSTANCE	instance;
	bool		isFullScreen;
	ScreenSize	scrSize;
};

//! Used as the staring point for the program
class Application
{
public:

	Application(const InitData& initData);
	~Application(void);

	//Application functions called by main
	void Update(void);

	//Fuction called in the main game loop
	void ProccessMessages(void);

	//Function to contorl the window
	void Quit(void);
	bool DataLoaded(void);
	void SysShutdown(void);
	void SetGLFormat(void);
	void SetShowWindow(bool show);
	void SetShowCursor(bool show);

	//Manager screen mode
	bool GetFullScreen(void) const;
	void SetFullScreen(bool fullScreen);
	ScreenSize GetResolution(void) const;
	void SetResolution(const ScreenSize& res);

	//GL manager
	GLManager* GetGLManager(void) const;

	//Set title icon
	BOOL WINAPI SetConsoleIcon(HICON hIcon);

private:
	static LRESULT CALLBACK WinProc(HWND win, UINT msg, WPARAM wp, LPARAM pl);

	HINSTANCE  m_instance;		//!< The instance from main
	WNDCLASS   m_winClass;		//!< The windows class
	DWORD	   m_style;			//!< The windows style
	HWND	   m_window;		//!< The handle to the window
	bool       m_isQuitting;	//!< flag for quitting
	bool	   m_isFullScreen;	//!< flag for fullscreen
	ScreenSize m_scrSize;		//!< The window width and height

	GameStateManager m_GSM;
	GLManager* m_GLM;

}; //end GameEngine


#endif // APPLICATION_H