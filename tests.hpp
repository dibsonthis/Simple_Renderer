// System headers
#include <windows.h>

// Standard library C-style
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "canvas.hpp"
#include "cursor.hpp"
#include "escapi.h"

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

void draw_test(Canvas& canvas, Cursor& cursor);
void capture_test(Canvas& canvas, Cursor& cursor, int columns, int rows);