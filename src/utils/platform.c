#include "platform.h"

#ifdef TMWIN32
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

void mywrite(const char *message, u8 colour) 
{
	// todo: check error looks boring but important
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE); 

    DWORD dwMode = 0;
	// always call GetConsoleMode before SetConsoleMode ..
    GetConsoleMode(console_handle, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(console_handle, dwMode);

	// FATAL,ERROR,WARN,INFO,DEBUG,TRACE
	/* static u8 levels[6] = {BACKGROUND_RED, FOREGROUND_RED, FOREGROUND_GREEN | FOREGROUND_RED, FOREGROUND_GREEN,FOREGROUND_BLUE, FOREGROUND_INTENSITY}; */
	/* SetConsoleTextAttribute(console_handle, levels[colour]); //check MSDN deprecated for powershell */
    OutputDebugStringA(message); //DEBUG console output windows only
    u64 length = strlen(message);
    LPDWORD number_written = 0;
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD)length, number_written, 0);
	/* SetConsoleTextAttribute(console_handle, 0x0F); //resets the color */
}

void mywrite_error(const char *message, u8 colour) 
{
	//  todo: check error looks boring but important
    HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);

    DWORD dwMode = 0;
    GetConsoleMode(console_handle, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(console_handle, dwMode);

    // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
	/* static u8 levels[6] = {BACKGROUND_RED, FOREGROUND_RED, FOREGROUND_GREEN | FOREGROUND_RED, FOREGROUND_GREEN,FOREGROUND_BLUE, FOREGROUND_INTENSITY}; */
	/* SetConsoleTextAttribute(console_handle, levels[colour]); */
    OutputDebugStringA(message);
    u64 length = strlen(message);
    LPDWORD number_written = 0;
    WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, (DWORD)length, number_written, 0);
	/* SetConsoleTextAttribute(console_handle, 0x0F); //resets the color */
}
#endif
