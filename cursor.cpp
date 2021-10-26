#include "cursor.hpp"

void Cursor::hidecursor()
{
    std::cout << "\x1b[?25l";
}

void Cursor::move_cursor(int x, int y)
{
    std::cout << "\x1b[" + std::to_string(y) + ";" + std::to_string(x) + "H";
}