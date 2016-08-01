/******************************************************************************/
/*!
\file   Application.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Application's class and member functions

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Application.h"
#include "../Utilities/Debug/Debug.h"
#include "../InputManager/InputManager.h"
#include "../../Game/BaseData/LoadStages.h"
// #include "../../Game/BaseData/LoadLogics.h"

namespace
{
	/*!Name of the window class*/
	LPCTSTR CLASS_NAME = TEXT("Game Engine");
	/*!Window style if the user chooses full screen*/
	const DWORD FULLSCREEN_STYLE = WS_POPUP | WS_VISIBLE;
	/*!Window style if the user choose windowed mode*/
	const DWORD WINDOWED_STYLE = WS_POPUP | WS_CAPTION | WS_SYSMENU;
	//const DWORD WINDOWED_STYLE = WS_OVERLAPPEDWINDOW;

	/******************************************************************************/
	/*!
	\brief - Adjust window size that client want

	\param style - Window's style
	\param size  - Window's size
	\param xStart - Window's x starting point
	\param yStart - Window's y starting point
	*/
	/******************************************************************************/
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

/******************************************************************************/
/*!
\brief - Build stages and game logics for game app

\return true
*/
/******************************************************************************/
bool Application::DataLoaded(void)
{
	// Load stages
	m_GSM.AddStage(ST_MENU, new MainMenuBuilder);
	m_GSM.AddStage(ST_LV1, new LV1Builder);
	m_GSM.AddStage(ST_LV2, new LV2Builder);
	m_GSM.AddStage(ST_LV3, new LV3Builder);
	m_GSM.AddStage(ST_GAMEOVER, new GameOverBuilder);
	m_GSM.AddStage(ST_PAUSE, new PauseBuilder);

	m_GSM.SetFirstStage(ST_MENU);

	// Load sound resources
	m_SM->Load("Resource/Sound/arrow_x.wav", SE_1);
	m_SM->Load("Resource/Sound/drum_roll_y.wav", SE_2);

	// Load font
	m_GLM->SetFont("Resource/Font/SDMiSaeng.ttf");

	return true;
}

/******************************************************************************/
/*!
\brief - Application Constructor

\param initData - Application's init data

*/
/******************************************************************************/
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

	//Set up our WNDCLASS(defaults)
	m_winClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW; //OpenGL
	m_winClass.cbClsExtra = 0;
	m_winClass.cbSize = sizeof(WNDCLASSEX);
	m_winClass.cbWndExtra = 0;
	m_winClass.lpszMenuName = 0;
	m_winClass.hCursor = LoadCursor(0, IDC_ARROW);
	m_winClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_winClass.hInstance = initData.instance;					//Instance from main 
	m_winClass.lpszClassName = CLASS_NAME;						//Window class name
	m_winClass.lpfnWndProc = WinProc;							//Static member

	// Set Icon for app
	m_winClass.hIcon = (HICON)LoadImage(NULL, L"Resource/Texture/Icon/icon_256.ico", IMAGE_ICON, 256, 256, LR_LOADFROMFILE);
	m_winClass.hIconSm = (HICON)LoadImage(NULL, L"Resource/Texture/Icon/icon_32.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);

	//Register our window class
	RegisterClassEx(&m_winClass);

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

	/******************** Set sound system; FMOD ********************/

	m_SM = new SoundManager;
	m_SM->InitFMOD(this);

	/******************** Set Open GL ********************/ 

	m_GLM = new GLManager;
	m_GLM->InitGL(this, m_window, m_scrSize.width, m_scrSize.height);

	/*****************************************************/

	//Make sure window is showing and messages have been sent
	ShowWindow(m_window, true);
	UpdateWindow(m_window);
}

/******************************************************************************/
/*!
\brief - Application Destructor
*/
/******************************************************************************/
Application::~Application(void)
{
	//Only Call Once
	DEBUG_CALL_CHECK();

	// Clear gl and sm
	delete m_GLM;
	delete m_SM;

	m_GLM = 0;
	m_SM = 0;

	UnregisterClass(LPCTSTR(CLASS_NAME), m_instance);

	m_instance = 0;
}

/******************************************************************************/
/*!
\brief - Update Application 
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief - Manage proccess messages
*/
/******************************************************************************/
void Application::ProccessMessages(void)
{
	MSG message;
	while (PeekMessage(&message, m_window, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

/******************************************************************************/
/*!
\brief - Quit application
*/
/******************************************************************************/
void Application::Quit(void)
{
	SendMessage(m_window, WM_CLOSE, 0, 0);
}

/******************************************************************************/
/*!
\brief - Get GLManager

\return m_GLM - pointer to GLManager
*/
/******************************************************************************/
GLManager* Application::GetGLManager(void) const
{
	return m_GLM;
}

/******************************************************************************/
/*!
\brief - Get Sound Manager

\return m_SM - pointer to Sound Manager
*/
/******************************************************************************/
SoundManager* Application::GetSManager(void) const
{
	return m_SM;
}

/******************************************************************************/
/*!
\brief - Get apllication;s resolution

\return m_scrSize - screen size of app
*/
/******************************************************************************/
ScreenSize Application::GetResolution(void) const
{
	return m_scrSize;
}

/******************************************************************************/
/*!
\brief - Set apllication;s resolution

\param res - screen size of app that client want
*/
/******************************************************************************/
void Application::SetResolution(const ScreenSize& res)
{
	m_scrSize.width = res.width;
	m_scrSize.height = res.height;
	SetWindowPos(m_window, 0, 0, 0, m_scrSize.width, m_scrSize.height, SWP_NOMOVE);
	
	m_GLM->Resize(m_scrSize.width, m_scrSize.height);
}

/******************************************************************************/
/*!
\brief - Set apllication;s window mode

\param fullscreen - bool toggle to set app's window mode
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief - Get apllication;s window mode

\return m_isFullScreen - bool toggle of app's window mode
*/
/******************************************************************************/
bool Application::GetFullScreen(void) const
{
	return m_isFullScreen;
}

/******************************************************************************/
/*!
\brief - Application's window procedure

\return 0
*/
/******************************************************************************/
LRESULT CALLBACK Application::WinProc(HWND win, UINT msg, WPARAM wp, LPARAM lp)
{
	static Application* s_pApp = 0;

	switch (msg)
	{
	case WM_MOUSEMOVE:
		InputManager::GetInstance().SetRawMousePosition(LOWORD(lp), HIWORD(lp));
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

		//Button Up
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
