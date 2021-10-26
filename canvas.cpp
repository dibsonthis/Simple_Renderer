#include "canvas.hpp"

Color::Color() : r(-1), g(-1), b(-1) {}
Color::Color(int _r, int _g, int _b) : r(_r), g(_g), b(_b) {}

Pixel::Pixel(char character, Color f_color, Color b_color, std::vector<Style> styles) 
    : character(character), f_color(f_color), b_color(b_color), styles(styles) {}

char Pixel::get_character()
{
    return character;
}

Color Pixel::get_f_color()
{
    return f_color;
}

Color Pixel::get_b_color()
{
    return b_color;
}

std::vector<Style>& Pixel::get_styles()
{
    return styles;
}

void Pixel::set_character(char c)
{
    character = c;
}

void Pixel::set_f_color(Color c)
{
    f_color = c;
}

void Pixel::set_b_color(Color c)
{
    b_color = c;
}

void Pixel::set_styles(std::vector<Style>& s)
{
    styles = s;
}

Canvas::Canvas(int width, int height, char character, Color f_color, Color b_color, std::vector<Style> styles)
    : width(width), height(height), init_character(character), init_f_color(f_color), init_b_color(b_color), init_styles(styles)
    {
        for (int y = 1; y <= height; y++)
        {
            for (int x = 1; x <= width; x++)
            {
                pixels.push_back(new Pixel(init_character, init_f_color, init_b_color, init_styles));
            }
        }

        construct_canvas();
    }

Pixel* Canvas::get_pixel(int x, int y)
{
    return pixels[(y-1) * width + (x-1)];
}

void Canvas::draw(int x, int y, char character)
{
    if (x < 1 || x > width)
    {
        return;
    }
    if (y < 1 || y > height)
    {
        return;
    }

    Pixel* pixel = get_pixel(x, y);
    pixel->set_character(character);
    pixel->set_f_color(init_f_color);
    pixel->set_b_color(init_b_color);
    pixel->set_styles(init_styles);     
}

void Canvas::draw(int x, int y, char character, Color f_color)
{
    if (x < 1 || x > width)
    {
        return;
    }
    if (y < 1 || y > height)
    {
        return;
    }

    Pixel* pixel = get_pixel(x, y);
    pixel->set_character(character);
    pixel->set_f_color(f_color);
    pixel->set_b_color(init_b_color);
    pixel->set_styles(init_styles);     
}

void Canvas::draw(int x, int y, char character, Color f_color, Color b_color)
{
    if (x < 1 || x > width)
    {
        return;
    }
    if (y < 1 || y > height)
    {
        return;
    }

    Pixel* pixel = get_pixel(x, y);
    pixel->set_character(character);
    pixel->set_f_color(f_color);
    pixel->set_b_color(b_color);
    pixel->set_styles(init_styles);     
}

void Canvas::draw(int x, int y, char character, std::vector<Style> styles)
{
    if (x < 1 || x > width)
    {
        return;
    }
    if (y < 1 || y > height)
    {
        return;
    }

    Pixel* pixel = get_pixel(x, y);
    pixel->set_character(character);
    pixel->set_f_color(init_f_color);
    pixel->set_b_color(init_b_color);
    pixel->set_styles(init_styles);     
}

void Canvas::draw(int x, int y, char character, Color f_color, Color b_color, std::vector<Style> styles)
{
    if (x < 1 || x > width)
    {
        return;
    }
    if (y < 1 || y > height)
    {
        return;
    }

    Pixel* pixel = get_pixel(x, y);
    pixel->set_character(character);
    pixel->set_f_color(f_color);
    pixel->set_b_color(b_color);
    pixel->set_styles(styles);     
}

void Canvas::draw(int x, int y, char character, Color f_color, std::vector<Style> styles)
{
    if (x < 1 || x > width)
    {
        return;
    }
    if (y < 1 || y > height)
    {
        return;
    }

    Pixel* pixel = get_pixel(x, y);
    pixel->set_character(character);
    pixel->set_f_color(f_color);
    pixel->set_b_color(init_b_color);
    pixel->set_styles(styles);     
}

void Canvas::draw_line(float x1, float y1, float x2, float y2, char character, Color f_color)
{
    draw(x1, y1, character, f_color);

    float dx, dy, step;
    dx=std::abs(x2-x1);
    dy=std::abs(y2-y1);
    
    if(dx>=dy)
        step=dx;
    else
        step=dy;
    
    dx=dx/step;
    dy=dy/step;

    float x, y;

    if (x2 >= x1 && y2 >= y1)
    {
        x=x1;
        y=y1;

        int i=1;
        while(i<=step)
        {
            draw(x, y, character, f_color);
            x=x+dx;
            y=y+dy;
            i++;
        }
    }
    else if (x1 >= x2 && y2 >= y1)
    {
        x=x1;
        y=y1;

        int i=1;
        while(i<=step)
        {
            draw(x, y, character, f_color);
            x=x-dx;
            y=y+dy;
            i++;
        }
    }
    else if (x1 >= x2 && y1 >= y2)
    {
        x=x2;
        y=y2;

        int i=1;
        while(i<=step)
        {
            draw(x, y, character, f_color);
            x=x+dx;
            y=y+dy;
            i++;
        }
    }
    else if (x2 >= x1 && y1 >= y2)
    {
        x=x1;
        y=y1;

        int i=1;
        while(i<=step)
        {
            draw(x, y, character, f_color);
            x=x+dx;
            y=y-dy;
            i++;
        }
    }

    draw(x2, y2, character, f_color);

}

void Canvas::draw_string(int x, int y, std::string string, Color f_color, Color b_color, std::vector<Style> styles)
{
    for (int i = 0; i < string.length(); i++)
    {
        draw(x+i, y, string[i], f_color, b_color, styles);
    }

}

void Canvas::clear_pixels()
{
    for (Pixel* pixel : pixels)
    {
        pixel->set_character(init_character);
        pixel->set_f_color(init_f_color);
        pixel->set_b_color(init_b_color);
        pixel->set_styles(init_styles);
    }
}

void Canvas::clear_pixels(Color f_color, Color b_color)
{
    for (Pixel* pixel : pixels)
    {
        pixel->set_character(init_character);
        pixel->set_f_color(f_color);
        pixel->set_b_color(b_color);
        pixel->set_styles(init_styles);
    }
}

void Canvas::clear_pixels(Color f_color, Color b_color, std::vector<Style> styles)
{
    for (Pixel* pixel : pixels)
    {
        pixel->set_character(init_character);
        pixel->set_f_color(f_color);
        pixel->set_b_color(b_color);
        pixel->set_styles(styles);
    }
}

void Canvas::construct_canvas()
{
    for (int y = 1; y <= height; y++)
    {
        for (int x = 1; x <= width; x++)
        {
            Pixel* pixel = get_pixel(x, y);
            std::string styles = "";
            for (Style style : pixel->get_styles())
            {
                styles += "\x1b[" + std::to_string(style) + "m";
            }
            canvas += styles;
            std::string f_rgb = "\x1b[38;2;" + std::to_string(pixel->get_f_color().r) + ";" 
                + std::to_string(pixel->get_f_color().g) + ";" + std::to_string(pixel->get_f_color().b) + "m";
            std::string b_rgb = "\x1b[48;2;" + std::to_string(pixel->get_b_color().r) + ";" 
                + std::to_string(pixel->get_b_color().g) + ";" + std::to_string(pixel->get_b_color().b) + "m";
            canvas += f_rgb + b_rgb;
            canvas += pixel->get_character();
            canvas += "\x1b[0m";
        }

        if (y < height)
        {
            canvas += "\n";
        }
    }
}

void Canvas::clear()
{
    canvas.clear();
    clear_pixels();
    construct_canvas();
}

void Canvas::clear(Color f_color, Color b_color)
{
    canvas.clear();
    clear_pixels(f_color, b_color);
    construct_canvas();
}

void Canvas::clear(Color f_color, Color b_color, std::vector<Style> styles)
{
    canvas.clear();
    clear_pixels(f_color, b_color, styles);
    construct_canvas();
}

void Canvas::update()
{
    canvas.clear();
    construct_canvas();
}

void Canvas::print()
{
    std::cout << canvas;
}