#include "Application.h"
#include "GLManager.h"
#include "../Utilities/Debug/Debug.h"
#include "../InputManager/InputManager.h"
#include "../../Game/BaseData/LoadStages.h"
#include <tchar.h>

namespace
{
	/*!Name of the window class*/
	const char* CLASS_NAME = "Game Engine";
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

Application::Application(const InitData& initData)
{
	//ONLY CALSS ONCE;
	DEBUG_CALL_CHECK();

	//Code data form initData
	m_instance = initData.instance;
	m_scrSize.width = initData.scrSize.width;
	m_scrSize.height = initData.scrSize.height;
	m_isFullScreen = initData.isFullScreen;
	m_style = (initData.isFullScreen) ? FULLSCREEN_STYLE : WINDOWED_STYLE;
	m_isQuitting = false;

	SetConsoleIcon(LoadIcon(0, IDI_EXCLAMATION));

	//Set up our WNDCLASS(defaults)
	m_winClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW; //OpenGL
	m_winClass.cbClsExtra = 0;
	m_winClass.cbWndExtra = 0;
	m_winClass.lpszMenuName = 0;
	m_winClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	m_winClass.hCursor = LoadCursor(0, IDC_ARROW);
	m_winClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_winClass.hInstance = initData.instance;					//Instance from main 
	m_winClass.lpszClassName = CLASS_NAME;							//Window class name
	m_winClass.lpfnWndProc = WinProc;								//Static member

	//Register our window class
	RegisterClass(&m_winClass);

	//Make client are the size that we want
	int xStart;
	int yStart;
	RECT size = { 0 };
	size.right = initData.scrSize.width;
	size.bottom = initData.scrSize.height;

	if (m_isFullScreen)
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = m_scrSize.width;			// Selected Screen Width
		dmScreenSettings.dmPelsHeight = m_scrSize.height;		// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = 32;						// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}

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
	//GLManager::GetInstance().OpenGLInit(m_window, m_scrSize.width, m_scrSize.height);
	m_GLM = new GLManager;
	m_GLM->OpenGLInit(m_window, m_scrSize.width, m_scrSize.height);

	//Make sure window is showing and messages have been sent
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
	m_GSM.Init(this);
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

GLManager* Application::GetGLManager(void) const
{
	return m_GLM;
}

//Build stages for game app
bool Application::DataLoaded(void)
{
	m_GSM.AddStage(ST_MENU, new MainMenuBuilder);
	m_GSM.AddStage(ST_LV1, new LV1Builder);
	m_GSM.AddStage(ST_LV2, new LV2Builder);
	m_GSM.AddStage(ST_LV3, new LV3Builder);
	m_GSM.AddStage(ST_GAMEOVER, new GameOverBuilder);

	m_GSM.SetFirstStage(ST_MENU);

	return true;
}

//Following two functions are provided to user to give control
ScreenSize Application::GetResolution(void) const
{
	return m_scrSize;
}

void Application::SetResolution(const ScreenSize& res)
{
	m_scrSize.width = res.width;
	m_scrSize.height = res.height;
	SetWindowPos(m_window, 0, 0, 0, m_scrSize.width, m_scrSize.height, SWP_NOMOVE);
	
	//GLManager::GetInstance().Resize(m_scrSize.width, m_scrSize.height);
	m_GLM->Resize(m_scrSize.width, m_scrSize.height);
}

void Application::SetFullScreen(bool fullscreen)
{
	m_isFullScreen = fullscreen;
	
	RECT size = { 0 };
	size.right = m_scrSize.width;
	size.bottom = m_scrSize.height;

	DEVMODE dmScreenSettings;								// Device Mode
	memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
	dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
	dmScreenSettings.dmPelsWidth = m_scrSize.width;			// Selected Screen Width
	dmScreenSettings.dmPelsHeight = m_scrSize.height;		// Selected Screen Height
	dmScreenSettings.dmBitsPerPel = 32;						// Selected Bits Per Pixel
	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	if (m_isFullScreen)
	{
		int xStart, yStart;

		// Set fullscreen mode
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		AdjustAndCenterWindow(m_style, size, xStart, yStart);

		// Reset style
		m_style = FULLSCREEN_STYLE;
		
		//Remove caption
		DWORD dwStyle = GetWindowLong(m_window, GWL_STYLE);
		DWORD dwRemove = WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
		DWORD dwNewStyle = dwStyle & ~dwRemove;
		SetWindowLong(m_window, GWL_STYLE, dwNewStyle);

		HDC hDC = GetWindowDC(NULL);
		SetWindowPos(m_window, NULL, 0, 0, GetDeviceCaps(hDC, HORZRES),
			GetDeviceCaps(hDC, VERTRES), SWP_FRAMECHANGED);
	}

	else
	{
		int appPosX = (GetSystemMetrics(SM_CXSCREEN) / 2 );
		int appPosY = (GetSystemMetrics(SM_CYSCREEN) / 2 );

		// Set Windowed Mode
		ChangeDisplaySettings(NULL, 0);

		AdjustAndCenterWindow(m_style, size, appPosX, appPosY);

		// Reset style
		m_style = WINDOWED_STYLE;

		// Add caption
		DWORD dwStyle = GetWindowLong(m_window, GWL_STYLE);
		DWORD dwAdd = WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
		DWORD dwNewStyle = dwStyle | dwAdd;
		SetWindowLong(m_window, GWL_STYLE, dwNewStyle);

		SetWindowPos(m_window, NULL, appPosX, appPosY,
			m_scrSize.width, m_scrSize.height, SWP_FRAMECHANGED);
	}
}

bool Application::GetFullScreen(void) const
{
	return m_isFullScreen;
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
	
	//case WM_SIZE:
	//{
	//				RECT rt;
	//				int width, height;
	//				GetWindowRect(win, &rt);
	//				width = rt.right - rt.left;
	//				height = rt.bottom - rt.top;
	//				SetWindowPos(win, NULL, 0, 0, width, height, SWP_NOMOVE);
	//				break;
	//}

	//Where window is actually destroyed
	case WM_DESTROY:
	{
					   //Stop game loop
					   s_pApp->m_isQuitting = true;
					   s_pApp->m_window = 0;
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

BOOL WINAPI Application::SetConsoleIcon(HICON hIcon)
{
	typedef BOOL(WINAPI *PSetConsoleIcon)(HICON);
	static PSetConsoleIcon pSetConsoleIcon = NULL;
	if (!pSetConsoleIcon)
		pSetConsoleIcon = (PSetConsoleIcon)GetProcAddress(GetModuleHandle(_T("kernel32")), "SetConsoleIcon");
	if (!pSetConsoleIcon)
		return false;
	return pSetConsoleIcon(hIcon);
}