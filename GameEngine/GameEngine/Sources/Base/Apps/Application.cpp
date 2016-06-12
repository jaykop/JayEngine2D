#include "../InputManager/InputManager.h"
#include "../Apps/GLApplication.h"
#include "../Debug/Debug.h"
#include "Application.h"
#include <iostream>

namespace 
{
	/*!Name of the window class*/
	const char* CLASS_NAME = "Ghost Engine";
	/*!Window style if the user chooses full screen*/
	const DWORD FULLSCREEN_STYLE = WS_POPUP | WS_VISIBLE;
	/*!Window style if the user choose windowed mode*/
	const DWORD WINDOWED_STYLE = WS_POPUP | WS_CAPTION;
	//const DWORD WINDOWED_STYLE = WS_OVERLAPPEDWINDOW;
	
	void AdjustAndCenterWindow(DWORD style, RECT& size, int& xStart, int& yStart)
	{
		DEVMODE dm = { 0 };
		int winWidth, winHeight;
		
		/*Get the size of the screen*/
		dm.dmSize = sizeof(dm);
		EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
		
		/*Make client area of window the correct size*/
		AdjustWindowRect(&size, style, false);

		/*Calculate new width and height*/
		winWidth = size.right - size.left;
		winHeight = size.bottom - size.top;

		/*Get start position for center*/
		xStart = (dm.dmPelsWidth / 2) - (winWidth / 2);
		yStart = (dm.dmPelsHeight / 2) - (winHeight / 2);
	}

}//end unnamed namespace

namespace GhostEngine
{

	Application::Application(const InitData& initData)
	{
		//ONLY CALSS ONCE;
		DEBUG_CALL_CHECK();

		//Code data form initData
		m_instance		= initData.instance;
		m_width			= initData.width;
		m_height		= initData.height;
		m_isFullScreen	= initData.isFullScreen;
		m_style			= (initData.isFullScreen) ? FULLSCREEN_STYLE : WINDOWED_STYLE;
		m_isQuitting	= false;

		//Set up our WNDCLASS(defaults)
		m_winClass.style			= CS_OWNDC | CS_HREDRAW | CS_VREDRAW; //OpenGL
		m_winClass.cbClsExtra		= 0;
		m_winClass.cbWndExtra		= 0;
		m_winClass.lpszMenuName		= 0;
		m_winClass.hIcon			= LoadIcon(0, IDI_APPLICATION);
		m_winClass.hCursor			= LoadCursor(0, IDC_ARROW);
		m_winClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
		m_winClass.hInstance		= initData.instance;					//Instance from main 
		m_winClass.lpszClassName	= CLASS_NAME;							//Window class name
		m_winClass.lpfnWndProc		= WinProc;								//Static member
	
		//Register our window class
		RegisterClass(&m_winClass);

		//Make client are the size that we want
		int xStart;
		int yStart;
		RECT size = { 0 };
		size.right = initData.width;
		size.bottom = initData.height;
		AdjustAndCenterWindow(m_style, size, xStart, yStart);

		//Now create our window
		m_window = CreateWindow(
			CLASS_NAME,				//Class name
			initData.title,			//Window Title
			m_style,				//Window style
			xStart,					//x Starting pos
			yStart,					//y Starting pos
			size.right - size.left,	//Width
			size.bottom - size.top,	//Height
			0,						//Parent Window
			0,						//Menu
			m_instance,				//Hinstance
			this					//Lparm This will be available in WM_CREATE
			);

		//Set opengl
		GLApplication::GetInstance().OpenGLInit(m_window, m_width, m_height);

		//Make sure window is showing and messages have been sent
		//SetFullScreen(m_isFullScreen); Sace this for later
		ShowWindow(m_window, true);
		UpdateWindow(m_window);
	}

	Application::~Application(void)
	{
		//Only Call Once
		DEBUG_CALL_CHECK();

		UnregisterClass(CLASS_NAME, m_instance);

		m_instance = 0;
	}

	void Application::Update(void)
	{
		//Only Call Once
		DEBUG_CALL_CHECK();
		m_GSM.Init();
		while (!m_isQuitting)
		{
			//Update GameManager
			m_GSM.Update();

			//If GameManager is Quitting, set Close message
			m_isQuitting = m_GSM.IsQuitting();
		}
		m_GSM.Shutdown();
	}

	void Application::ProccessMessages(void)
	{
		MSG message;
		while (PeekMessage(&message, m_window, 0, 0, PM_REMOVE))
		{	
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

	//Will used by Game Manager
	void Application::Quit(void)
	{
		SendMessage(m_window, WM_CLOSE, 0, 0);
	}

	//Following two functions are provided to user to give control
	int Application::GetHeight(void) const
	{
		return m_height;
	}

	int Application::GetWidth(void) const
	{
		return m_width;
	}

	LRESULT CALLBACK Application::WinProc(HWND win, UINT msg, WPARAM wp, LPARAM lp)
	{
		static Application* s_pApp = 0;

		switch (msg)
		{
			case WM_MOUSEMOVE:
				InputManager::GetInstance().GetRawMousePosition(LOWORD(lp), HIWORD(lp));
				break;

			//Button Down
			case WM_KEYDOWN:
				InputManager::GetInstance().PressActivate(InputManager::GetInstance().KeyTranslator(wp));
				InputManager::GetInstance().SetPressedStatus(DOWN);
				break;
			
			case WM_LBUTTONDOWN:
				InputManager::GetInstance().PressActivate(MOUSE_LBUTTON);
				InputManager::GetInstance().SetPressedStatus(DOWN);
				break;

			case WM_RBUTTONDOWN:
				InputManager::GetInstance().PressActivate(MOUSE_RBUTTON);
				InputManager::GetInstance().SetPressedStatus(DOWN);
				break;

			case WM_KEYUP:
				InputManager::GetInstance().PressInactivate(InputManager::GetInstance().KeyTranslator(wp));
				InputManager::GetInstance().SetPressedStatus(UP);
				break;

			case WM_LBUTTONUP:
				InputManager::GetInstance().PressInactivate(MOUSE_LBUTTON);
				InputManager::GetInstance().SetPressedStatus(UP);
				break;

			case WM_RBUTTONUP:
				InputManager::GetInstance().PressInactivate(MOUSE_RBUTTON);
				InputManager::GetInstance().SetPressedStatus(UP);
				break;

			case WM_CREATE:
			{
				//Contain all data we pass to CreateWindow
				CREATESTRUCT* pCS = reinterpret_cast<CREATESTRUCT*>(lp);
				s_pApp = reinterpret_cast<Application*>(pCS->lpCreateParams);

				//Create graphics here..

				break;
			}

			//Where window is actually destroyed
			case WM_DESTROY:
			{
				//Stop game loop
				s_pApp->m_isQuitting = true;
			    s_pApp->m_window	 = 0;
				PostQuitMessage(0);
				break;
			}
			
			case WM_CLOSE:
			{
				//First destroy the graphics here...
				
				//Then destroy the window
				//Chance to interrupt...
				
				DestroyWindow(win);
				break;
			}
			default:
				return DefWindowProc(win, msg, wp, lp);
		}

		return 0;
	
	}

}//end namespace GhostEngine

