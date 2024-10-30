// Back-projection
// Edit By: Ziyang Li
// Date: 10/18/24
// Description: This file using back-projection reconstructing from sinogram 500 * 500

#include <iostream>
#include "Display02.h"
#include "Display.h"
#include <cmath>
#include <algorithm>
#include "line_functions.h"
using namespace std;

const int n = 500, N = 180;// Image Size N x N
int Pixels[n][n];

// Save the image after rotation
int tracy[n][n];

int final[n][n] = {0};



void square(int row1, int row2, int col1, int col2)
{
    for (int i = row1 - 1; i < row2; i++)
    {
        for (int j = col1 - 1; j < col2; j++)
            Pixels[i][j] = 250;
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
            line3(x, y + y1, x, y1 - y, Pixels);
        }
    }
}

void trangle(int h1, int h2, int b1, int b2, int bRow)
{
    for (int i = b1; i < b2; i++)
    {
        line3(h1, h2, bRow, i, Pixels);
    }
}

void rotation(int angle, int (&Pixels)[n][n])
{
    int width = n; // using 'constant' rather than literals within the code
    int height = n;
    int background = 2; // this is the background color - use a suitable value here

    float rads = angle * 3.14159265359 / 180.0; // fixed constant PI
    float cs = cos(-rads);                  // precalculate these values
    float ss = sin(-rads);
    float xcenter = (float)(width) / 2.0;
    float ycenter = (float)(height) / 2.0;
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            // now find the pixel of the original image that is rotated to (r,c)
            // rotation formula assumes that origin = top-left and y points down
            int rorig = ycenter + ((float)(r)-ycenter) * cs - ((float)(c)-xcenter) * ss;
            int corig = xcenter + ((float)(r)-ycenter) * ss + ((float)(c)-xcenter) * cs;
            // now get the pixel value if you can
            int p = background; // in case there is no original pixel
            if (rorig >= 0 && rorig < height && corig >= 0 && corig < width)
            {
                p = Pixels[rorig][corig];
            }
            tracy[r][c] = p;
        }
    }
}

void re(int angle, int (&s)[N][n]) {
    int temp[n][n] = {0}; 

    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            
            if (angle < N && i < n) {
                temp[i][j] = s[angle][j]; 
            }
        }
    }
    rotation(-angle, temp); 

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            final[i][j] += tracy[i][j];
        }
    }
}

void reduce(int (&s)[n][n]){
    int max1 = 0;

    for(int i = 0; i < n; i++){
        int max2 = 0;
        for(int j = 0; j < n; j++) max2 = max(max2, s[i][j]);
        max1 = max(max1, max2);
    }
    
    for(int i = 0; i < n; i++){
        
        for(int j = 0; j < n; j++) s[i][j] = s[i][j] * 255 / max1;
        
    }

}

int main()
{

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            Pixels[row][col] = 2;
        }
    }

    // Creat three shape
    square(30, 90, 338, 396);
    square(388, 438, 255, 346);
    circle(288, 288, 50);
    circle(188, 328, 70);
    trangle(50, 250, 100, 300, 100);
    trangle(350, 150, 122, 180, 250);

    Display02 image(Pixels, "output03");
    

    

    int sinogram[N][n];

    for (int i = 0; i < N; i++)
    {
        rotation(i, Pixels);
        for (int row = 0; row < n; row++)
        {
            int res = 0;

            for (int col = 0; col < n; col++)
            {
                res += tracy[col][row];
            }
            sinogram[i][row] = res;
        }
    }

    int max1 = 0;

    for(int i = 0; i < N; i++){
        int max2 = 0;
        for(int j = 0; j < n; j++) max2 = max(max2, sinogram[i][j]);
        max1 = max(max1, max2);
    }
    
    for(int i = 0; i < N; i++){
        
        for(int j = 0; j < n; j++) sinogram[i][j] = sinogram[i][j] * 255 / max1;
        
    }

    //reduce(sinogram);
    
    Display image3(sinogram, "output05");


    for(int i = 0; i < N; i++) re(i, sinogram);

    reduce(final);

    Display02 image2(final, "output04");
     

    return 0;
}