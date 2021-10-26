#include "tests.hpp"

int main()
{
    //############################# BEGIN SETUP #############################//

    HWND hWind = GetConsoleWindow();

    RECT ConsoleRect;
	GetWindowRect(hWind, &ConsoleRect); 
 
    MoveWindow(hWind, ConsoleRect.left, ConsoleRect.top, 640, 480, TRUE);

    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return GetLastError();
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return GetLastError();
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(hOut, &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    //############################# END SETUP #############################//

    Cursor cursor;
    cursor.hidecursor();

    Canvas canvas(columns, rows, FULL_BLOCK, {100, 50, 24}, {0, 0, 0}); 

    //draw_test(canvas, cursor);
    capture_test(canvas, cursor, columns, rows);

    return 0;
}