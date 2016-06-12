#ifndef APPLICATION_H
#define APPLICATOPN_H

#define WIN32_LEAN_AND_MEAN
#include "../StateManager/GameStateManager.h"

namespace GhostEngine
{
	//Used as the staring point for the program
	struct InitData
	{
		const char* title;
		HINSTANCE	instance;
		bool		isFullScreen;
		int			width;
		int			height;
	};

	class Application
	{
	public:

		Application(const InitData& initData);
		~Application(void);

		//Application functions called by main
		void Update(void);

		//Fuction called in the main game loop
		void ProccessMessages(void);

		//Function to co torl the window
		void Quit(void);
		void SetFullScreen(bool fullScreen);
		void SetShowWindow(bool show);
		void SetShowCursor(bool show);
		void ChangeResolution(int width, int height);
		int  GetWidth(void) const;
		int  GetHeight(void) const;

		void SysShutdown(void);
		void SetGLFormat(void);

	private:
		static LRESULT CALLBACK WinProc(HWND win, UINT msg, WPARAM wp, LPARAM pl);

		HINSTANCE m_instance;		//!< The instance from main
		WNDCLASS  m_winClass;		//!< The windows class
		DWORD	  m_style;			//!< The windows style
		HWND	  m_window;			//!< The handle to the window
		bool      m_isQuitting;		//!< flag for quitting
		bool	  m_isFullScreen;	//!< flag for fullscreen
		int	      m_width;			//!< The window width
		int		  m_height;			//!< Rhe window height

		GameStateManager m_GSM;

	}; //end GameEngine
}

#endif // APPLICATION_H