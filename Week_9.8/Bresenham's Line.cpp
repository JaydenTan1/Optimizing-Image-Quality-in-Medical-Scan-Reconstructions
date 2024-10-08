#include <iostream>
#include <cmath>
using namespace std;

const int N = 500; // Image Size N x N
short Pixels[N][N];

//Bresenham's Line Algorithm
//Edit By: Ziyang Li
//Date: 9/20/24
//Description：Bresenham's Line Algorithm 1.0.
void line1(int x1, int y1, int x2, int y2)
{  
    int dx, dy, p, x, y;  
    dx=x2-x1;  
    dy=y2-y1;  
    x=x1;  
    y=y1;  
    p=2*dy-dx;  
    while(x<x1)  
    {  
        if(p>=0)  
        {  
            Pixels[x][y] = 1;  
            y=y+1;  
            p=p+2*dy-2*dx;  
        }  
        else  
        {  
            Pixels[x][y] = 1;  
            p=p+2*dy;}  
            x=x+1;  
        }  
}  


//Bresenham's Line Algorithm
//Edit By: Ziyang Li
//Date: 9/20/24
//Description：An improved version of Bresenham's Line Algorithm that addresses cases where the slope is negative and so on.
void line2(int x1, int y1, int x2, int y2)
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
