#include "tests.hpp"

struct Block
{
    Block(int _width, int _height, int _x, int _y, char _c) 
    : width(_width), height(_height), x(_x), y(_y), c(_c) {}
    int width, height;
    float x, y;
    char c;
};

Block block(14, 6, 20, 1, FULL_BLOCK);

int r = 0;
int g = 0;
int b = 0;

double delta = 0.016;

float xPos = 10.0f;
float yPos = 10.0f;
float speed = 100.0f;

void draw_test(Canvas& canvas, Cursor& cursor)
{
    Block block_2(canvas.width - 3, 6, 2, 2, FULL_BLOCK);

    while(true)
    {
        canvas.clear();

        auto t_start = std::chrono::high_resolution_clock::now();

        if(GetKeyState(VK_LEFT) & 0x8000)
        {
            block.x -= (speed * delta);
        }

        if(GetKeyState(VK_RIGHT) & 0x8000)
        {
            block.x += (speed * delta);
        }

        if(GetKeyState(VK_UP) & 0x8000)
        {
            block.y -= (speed * delta);
        }

        if(GetKeyState(VK_DOWN) & 0x8000)
        {
            block.y += (speed * delta);
        }

        if(GetKeyState('R') & 0x8000)
        {
            r += (speed * delta);
            if (r >= 255)
            {
                r = 0;
            }
        }

        if(GetKeyState('G') & 0x8000)
        {
            g += (speed * delta);
            if (g >= 255)
            {
                g = 0;
            }
        }

        if(GetKeyState('B') & 0x8000)
        {
            b += (speed * delta);
            if (b >= 255)
            {
                b = 0;
            }
        }

        canvas.draw_line(1, 1, 80, 10, FULL_BLOCK, {255, 255, 255});
        canvas.draw_line(80, 10, 20+block.x, 20+block.y, FULL_BLOCK, {255, 255, 255});
        canvas.draw_line(20+block.x, 20+block.y, 1, 1, FULL_BLOCK, {255, 255, 255});

        canvas.draw_string(2, 2, "Delta: ", 
        {255, 255, 255}, {0, 0, 0}, {S_BOLD_BRIGHT});

        canvas.draw_string(2 + 7, 2, std::to_string(delta), 
        {255, 255, 255}, {0, 0, 0}, {S_NEGATIVE});

        canvas.update();

        cursor.move_cursor();

        canvas.print();

        auto t_end = std::chrono::high_resolution_clock::now();

        delta = std::chrono::duration<double, std::milli>(t_end-t_start).count()/1000.0f;

    }

    std::cin.get();
}

void capture_test(Canvas& canvas, Cursor& cursor, int columns, int rows)
{
    // Capture Setup //

    /* Initialize ESCAPI */
  
    int devices = setupESCAPI();

    if (devices == 0)
    {
        printf("ESCAPI initialization failure or no devices found.\n");
        std::cin.get();
    }

    /* Set up capture parameters.
    * ESCAPI will scale the data received from the camera 
    * (with point sampling) to whatever values you want. 
    * Typically the native resolution is 320*240.
    */

    struct SimpleCapParams capture;
    capture.mWidth = columns;
    capture.mHeight = rows;
    capture.mTargetBuf = new int[columns * rows];
    
    /* Initialize capture - only one capture may be active per device,
    * but several devices may be captured at the same time. 
    *
    * 0 is the first device.
    */
    
    if (initCapture(0, &capture) == 0)
    {
        printf("Capture failed - device may already be in use.\n");
        std::cin.get();
    } 

    /* request a capture */      
    doCapture(0);
            
    while (isCaptureDone(0) == 0)
    {
        /* Wait until capture is done. */       
    
        for (int i = 1; i <= capture.mHeight; i++)
        {
            for (int j = 1; j <= capture.mWidth; j++)
            {
                int index = (i-1) * capture.mWidth + (j-1);
                if (i > 0 && i <= capture.mHeight && j > 0 && j <= capture.mWidth)
                {
                    int a, r, g, b;
                    a = ( capture.mTargetBuf[index] >> 24 ) & 0xff;
                    r = ( capture.mTargetBuf[index] >> 16 ) & 0xff;
                    g = ( capture.mTargetBuf[index] >>  8 ) & 0xff;
                    b = ( capture.mTargetBuf[index] >>  0 ) & 0xff;
                    float x = (r+g+b)/3.0f;
                    if (x < 33)
                        x = 33;
                    else if (x > 255)
                        x = 255;
                    char z = x;         
                    canvas.draw(j, i, z, {r, g, b}, {}, {S_BOLD_BRIGHT});
                }
            }
        }

        canvas.update();
        cursor.move_cursor();
        canvas.print();

        doCapture(0);
    }
}