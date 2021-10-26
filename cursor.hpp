#pragma once

#include <iostream>

class Cursor
{
    public:
    
    Cursor(){}

    void hidecursor();
    void move_cursor(int x = 1, int y = 1);

};