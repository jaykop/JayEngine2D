#include "Debug.h"
#include <sstream>
#include <string>

namespace DebugTools
{
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
			returnValue = MessageBox(NULL, ss.str().c_str(),
				"ASSERT!", MB_TASKMODAL | MB_SETFOREGROUND | MB_YESNO | MB_ICONERROR);

			if (returnValue == IDYES)
				return true;
			ExitProcess((unsigned(-1)));

		}
		return false;
	}

	void CreateConsole(void)
	{
		FILE* pFile;
		AllocConsole();

		freopen_s(&pFile, "CONOUT$", "wt", stdout);
		freopen_s(&pFile, "CONOUT$", "wt", stderr);
		SetConsoleTitle("Debug Console");
	}

	void DestroyConsole(void)
	{
		FreeConsole();
	}

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

	void CustomizedMessageBox(const char* outputMessage)
	{
		MessageBox(NULL, outputMessage, "Message Alarmed!",
			MB_SYSTEMMODAL | MB_SETFOREGROUND | MB_OK | MB_ICONERROR);
	}
}