//Drawing Graphics
//Edit by: Ziyang Li
//Date: 9/20/2024
//Description: Use Bresenham's Line Algorithm to draw two straight lines with different angles, a square, and a circle.

#include <iostream>
#include "Display.h"
#include <cmath>
using namespace std;

const int N = 500; // Image Size N x N

short Pixels[N][N];

void line1(int x1, int y1, int x2, int y2)
{
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    dx = x2 - x1;
    dy = y2 - y1;
    dx1 = abs(dx);
    dy1 = abs(dy);
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;
    if (dy1 <= dx1)
    {
        if (dx >= 0)
        {
            x = x1;
            y = y1;
            xe = x2;
        }
        else
        {
            x = x2;
            y = y2;
            xe = x1;
        }
        Pixels[x][y] = 1;
        for (i = 0; x < xe; i++)
        {
            x = x + 1;
            if (px < 0) px = px + 2 * dy1;
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1;
                else y = y - 1;
            
                px = px + 2 * (dy1 - dx1);
            }

            Pixels[x][y] = 1;
        }
    }
    else
    {
        if (dy >= 0)
        {
            x = x1;
            y = y1;
            ye = y2;
        }
        else
        {
            x = x2;
            y = y2;
            ye = y1;
        }
        Pixels[x][y] = 1;
        for (i = 0; y < ye; i++)
        {
            y = y + 1;
            if (py <= 0) py = py + 2 * dx1;
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1;
            
                else x = x - 1;
                
                py = py + 2 * (dx1 - dy1);
            }

            Pixels[x][y] = 1;
        }
    }
}

void square(int x1, int x2, int y1, int y2)
{
    for (int i = x1 - 1; i < x2; i++)
    {
        for (int j = y1 - 1; j < y2; j++)
            Pixels[i][j] = 2;
    }
}

void circle(int x1, int y1, int r)
{
    for (int x = x1 - r; x < r + x1; x++)
    {
        int dx = x - x1;
        int right = r * r - dx * dx;
        if (right >= 0)
        {
            int y = sqrt(right);
            // line1(x,y+y1, x, y1 - y);
            Pixels[x][y + y1] = 1;
            Pixels[x][y1 - y] = 1;
        }
    }
}

void circle2(int cx, int cy, int r)
{
    // P[cx][cy] = 255;
    for (int row = 0; row < 500; row++)
    {
        for (int col = 0; col < 500; col++)
        {
            if ((pow((row - cx), 2) + pow((col - cy), 2) == pow(r, 2)))
            {
                Pixels[row][col] = 1;
            }
        }
    }
}

int main()
{

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            Pixels[row][col] = 255;
        }
    }

    line1(0, 0, 332, 21);
    line1(32, 112, 200, 47);
    square(50,100,100,150);
    circle(200,200,80);
    

    Display image(Pixels, "output");

    return 0;
}
