/*****************
Name: Ziyang Li
Update Date: 11/25/2024

******************/



#include <iostream>
#include "Display.h"
#include <cmath>
#include <algorithm>

#include <numeric>
using namespace std;

const int n = 180; // Image Size N x N
// Save the image after rotation
int tracy[n][n];

int final[n][n];

int sinogram[n][n];

int sino[n][n];

void rotation(int angle, int (&Pixels)[n][n])
{
    int width = n; // using 'constant' rather than literals within the code
    int height = n;
    int background = 2; // this is the background color - use a suitable value here

    float rads = angle * 3.14159265359 / 180.0; // fixed constant PI
    float cs = cos(-rads);                      // precalculate these values
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

void re(int angle, int (&s)[n][n])
{
    int temp[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp[j][i] = s[angle][i];
        }
        rotation(-angle, temp);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            final[i][j] += tracy[i][j];
        }
    }
}

void reduce(int (&s)[n][n])
{
    int max1 = 0;

    for (int i = 0; i < n; i++)
    {
        int max2 = 0;
        for (int j = 0; j < n; j++)
            max2 = max(max2, s[i][j]);
        max1 = max(max1, max2);
    }

    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < n; j++)
            s[i][j] = s[i][j] * 255 / max1;
    }
}

void dft(int row, vector<double> &real, vector<double> &imag)
{
    // for X[0]
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += sinogram[row][i];
    real.push_back(sum);
    imag.push_back(0);
    // cout << nums[0] << ":  "<< accumulate(nums.begin(), nums.end(), 0) << " + 0j" << endl;

    double pi = 3.1415926;

    for (int i = 1; i < n; i++)
    {
        double nonJ = 0.00, jPart = 0.00;
        for (int j = 0; j < n; j++)
        {
            if (j == 0)
            {
                nonJ += sinogram[row][j];
                continue;
            }
            double exponent = (2 * pi * j * i) / n;
            nonJ += sinogram[row][j] * cos(exponent);
            jPart += -(sinogram[row][j] * sin(exponent));
        }
        real.push_back(nonJ);
        imag.push_back(jPart);
    }
}

void idft(int row, vector<double> &real, vector<double> &imag)
{
    double pi = 3.1415926;
    for (int k = 0; k < n; k++)
    {
        double sumReal = 0.0;
        double sumImag = 0.0;
        for (int j = 0; j < n; j++)
        {
            double angle = (2 * pi * j * k) / n;
            sumReal += real[j] * cos(angle) - imag[j] * sin(angle);
            sumImag += real[j] * sin(angle) + imag[j] * cos(angle);
        }
        // Divide by n to complete the inverse transform
        double res = sumReal / n;
         int resInt = static_cast<int>(ceil(res));
        //int resInt = static_cast<int>(floor(res));
        // cout<<res<<" ";

        sino[row][k] = resInt > 0 ? resInt : 0;
        //sino[row][k] = abs(resInt);
    }
    // return ans;
}

void createFilter(double (&rampFilter)[n])
{
    double c;
    for (int i = 0; i < n; i++)
    {
        c = abs(i - n / 2);
        rampFilter[i] = (n - 2 * c) / n;
    }
}

int main()
{
    for (int i = 0; i < n; i++)
    {
        vector<double> real, imag;
        dft(i, real, imag);
        double rampFilter[n];
        createFilter2(rampFilter);
        
        /*
        for(int j = 0; j < n; j++){
            real[j] *= rampFilter[j];
            imag[j] *= rampFilter[j];
        }
        */
        
        int mid = n / 2;
        for (int j = 0; j < mid; j++)
        {
             real[mid + j] *= rampFilter[j];
             imag[mid + j] *= rampFilter[j];
        }
        for (int j = 0; j < mid; j++)
        {
            real[j] *= rampFilter[mid + j];
            imag[j] *= rampFilter[mid + j];
        }
        idft(i, real, imag);
    }

    reduce(sino);
    Display image1(sino, "output11");
  
    for (int i = 0; i < n; i++) re(i, sino);
    reduce(final);
    Display image2(final, "output12");

    return 0;
}
