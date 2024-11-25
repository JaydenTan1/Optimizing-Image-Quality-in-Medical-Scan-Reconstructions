/*************
    Name: Ziyang Li
    Update Date: 11/25/2024 
**************/

#include <iostream>
#include "Display.h"
#include <cmath>
#include <algorithm>
using namespace std;

const int n = 180; // Image Size N x N
int Pixels[n][n];

// Save the image after rotation
int tracy[n][n];

int final[n][n] = {0};

int sinogram[n][n];

int sino[n][n];

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

void re(int angle, int (&s)[n][n]){
    int temp[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            temp[j][i] = s[angle][i];
        }
        rotation(-angle, temp);
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
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

void sp(int row) {
    //Window[-1, 2, -1]
    for (int col = 0; col < n; col++) {
        int ans = 0, count = 0;
        
        for (int i = col - 1; i <= col + 1; i++) {

            int k = count == 1 ? 2 : -1;
            count++;
            
            if (i >= 0 && i < n) {
                int temp = sinogram[row][i] * k;  
                ans += temp;
            }
        }
        float weightOriginal = 0.08;  // The weight of the original image
        float weightEdge = 0.92;      // Weighting of edge

        // Weighted Sum
        int combinedResult = static_cast<int>(weightOriginal * sinogram[row][col] + weightEdge * ans);
        sino[row][col] = abs(combinedResult/3);
    }
}

void sp2(){
        for(int row = 0; row < n; row++){
            for(int col = 0; col < n; col++){
                int sum = 0, cnt = 0;
                for(int i = row - 1; i <= row + 1; i++){
                    for(int j = col - 1; j <= col + 1; j++){
                        if((i >= 0 && i < n) && (j >= 0 && j < n)){
                            cnt++;
                            if(i == row && j == col){
                                int s = (int)sinogram[i][j] * 8.3;
                                sum += s;
                                //sum += sinogram[i][j] * 8;

                            } 
                            else sum += -sinogram[i][j];
                        }
                    }
                }
                int res = static_cast<int>(ceil(sum));
                sino[row][col] = abs(res);
            }
        }
}



int main()
{
    //for(int i = 0; i < n; i++)  sp(i);
    sp2(); 
    reduce(sino);
    
    for(int i = 0; i < n; i++) re(i, sino);
    reduce(final);
    Display image2(final, "output");

    return 0;
}
