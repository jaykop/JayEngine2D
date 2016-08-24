/******************************************************************************/
/*!
\file   Debug.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Debug's macros and functions in debug mode

All codes are written by Jaykop Jeong...
*/
/******************************************************************************/


#include "Debug.h"
#include <sstream>
#include <string>

namespace DebugTools
{
	/******************************************************************************/
	/*!
	\brief - Assert when to do

	\param expression - Show expression
	\param outputMessage - Show message set
	\param functionName - Show function name
	\param fileName - Show file naem
	\param lineNumber - Show line number where crashed
	*/
	/******************************************************************************/
	bool Assert(int expression, const char* outputMessage,
		const char* functionName, const char* fileName,
		unsigned lineNumber)
	{
		if (!expression)
		{
			int returnValue;
			std::stringstream ss;
			// Set output message
			ss << "ASSERTION FAILIURE: ";
			ss << "\nFile: ";
			ss << fileName;
			ss << "\nLine: ";
			ss << lineNumber;
			ss << "\nfunctionName: ";
			ss << functionName;
			ss << "\n\n Description: ";
			ss << outputMessage;
			ss << "\n\nYes: Brek into the Debugger.";
			ss << "\nNo: Exit immediately";

			//dispaly a message to the user
			returnValue = MessageBox(NULL, LPCTSTR(ss.str().c_str()),
				"ASSERT!", MB_TASKMODAL | MB_SETFOREGROUND | MB_YESNO | MB_ICONERROR);

			if (returnValue == IDYES)
				return true;
			ExitProcess((unsigned(-1)));

		}
		return false;
	}

	/******************************************************************************/
	/*!
	\brief - Create debug console
	*/
	/******************************************************************************/
	void CreateConsole(void)
	{
		FILE* pFile;
		AllocConsole();

		freopen_s(&pFile, "CONOUT$", "wt", stdout);
		freopen_s(&pFile, "CONOUT$", "wt", stderr);
		SetConsoleTitle("Debug Console");
	}

	/******************************************************************************/
	/*!
	\brief - Destroy debug console
	*/
	/******************************************************************************/
	void DestroyConsole(void)
	{
		FreeConsole();
	}

	/******************************************************************************/
	/*!
	\brief - Clear the debug screen
	*/
	/******************************************************************************/
	void ClearScreen(void)
	{
		COORD coordScreen = {0, 0};
		DWORD cCharsWritten;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD dwConSize;
		HANDLE hStdout;
		int result;

		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

		//Get the number of chracter cells in the current buffer
		if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
			return;

		dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

		//Fill the entire screen with blanks
		result = FillConsoleOutputCharacter(
			hStdout,		// Handle to console screen buffer
			' ',			// Chracter to write to the buffer
			dwConSize,		// Number of cells to write
			coordScreen,	// Coordinates of first cell
			&cCharsWritten	// Receive number of characters writter
			);

		if (!result)
			return;

		//Get the current text attribute
		if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
			return;

		result = FillConsoleOutputAttribute(
			hStdout,			// Handle to console screen buffer
			csbi.wAttributes,	// Chracter attribute to use
			dwConSize,			// Number of cells to set attribute
			coordScreen,		// Coordinates of first cell
			&cCharsWritten		// Receive number of characters writter
			);

		if (!result)
			return;

		//Put the cursor ar its gome coordinates
		SetConsoleCursorPosition(hStdout, coordScreen);
	}

	/******************************************************************************/
	/*!
	\brief - Show customized message box

	\param outputMessage - Show the message set
	*/
	/******************************************************************************/
	void CustomizedMessageBox(const char* outputMessage)
	{
		MessageBox(NULL, LPCTSTR(outputMessage), "Message Alarmed!",
			MB_SYSTEMMODAL | MB_SETFOREGROUND | MB_OK | MB_ICONERROR);
	}
}