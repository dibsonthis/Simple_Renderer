#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

enum ASCII_CODES
{
    SHADED_BLOCK_1 = 176,
    SHADED_BLOCK_2,
    SHADED_BLOCK_3,
    FULL_BLOCK = 219

};

enum Style
{
    S_DEFAULT = 0,
    S_BOLD_BRIGHT = 1,
    S_UNDERLINE = 4,
    S_NEGATIVE = 7,
    S_NO_BOLD_BRIGHT = 22,
    S_NO_UNDERLINE = 24,
    S_POSITIVE = 27,

    FG_DEFAULT = 39,
    BG_DEFAULT = 49,

    FG_BLACK = 30,
    FG_RED,
    FG_GREEN,
    FG_YELLOW,
    FG_BLUE,
    FG_MAGENTA,
    FG_CYAN,
    FG_WHITE,

    BG_BLACK = 40,
    BG_RED,
    BG_GREEN,
    BG_YELLOW,
    BG_BLUE,
    BG_MAGENTA,
    BG_CYAN,
    BG_WHITE
};

class Color
{
    public:
    int r, g, b;
    Color();
    Color(int _r, int _g, int _b);
};

class Pixel
{
    private:
    char character;
    Color f_color, b_color;
    std::vector<Style> styles;

    public:
    Pixel(char character, Color f_color = Color(), Color b_color = Color(), std::vector<Style> styles = {});

    char get_character();

    Color get_f_color();
    Color get_b_color();

    std::vector<Style>& get_styles();

    void set_character(char c);

    void set_f_color(Color c);
    void set_b_color(Color c);

    void set_styles(std::vector<Style>& s);
};

class Canvas
{
    public:

    int width;
    int height;
    char init_character;
    Color init_f_color, init_b_color;
    std::vector<Style> init_styles;
    std::string canvas;
    std::vector<Pixel*> pixels;

    Canvas(int width, int height, char character, Color f_color = Color(), Color b_color = Color(), 
    std::vector<Style> styles = {});

    Pixel* get_pixel(int x, int y);

    void draw(int x, int y, char character);
    void draw(int x, int y, char character, Color f_color);
    void draw(int x, int y, char character, Color f_color, Color b_color);
    void draw(int x, int y, char character, std::vector<Style> styles);
    void draw(int x, int y, char character, Color f_color, Color b_color, std::vector<Style> styles);
    void draw(int x, int y, char character, Color f_color, std::vector<Style> styles);

    void draw_line(float x1, float y1, float x2, float y2, char character, Color f_color);

    void draw_string(int x, int y, std::string string, Color f_color = Color(), Color b_color = Color(), 
        std::vector<Style> styles = {});

    void clear_pixels();
    void clear_pixels(Color f_color, Color b_color);
    void clear_pixels(Color f_color, Color b_color, std::vector<Style> styles);

    void construct_canvas();

    void clear();
    void clear(Color f_color, Color b_color);
    void clear(Color f_color, Color b_color, std::vector<Style> styles);

    void update();

    void print();
};