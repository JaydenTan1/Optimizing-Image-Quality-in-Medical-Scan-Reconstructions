#include <iostream>
#include "../Week_9.22/Display.h"
#include "../Week_9.22/line_functions.h"
using namespace std;

const int N = 500;
const int n = 10;

int main() {
  short phantom[n][n] = {{1,1,0,0,0,0,0,0,1,1},{1,1,1,0,0,0,0,1,1,1},{1,1,1,1,0,0,1,1,1,1},{1,1,1,1,1,1,1,1,1,1},{1,1,0,1,1,1,1,0,1,1},{1,1,0,0,1,1,0,0,1,1},{1,1,0,0,0,0,0,0,1,1},{1,1,0,0,0,0,0,0,1,1},{1,1,0,0,0,0,0,0,1,1},{1,1,0,0,0,0,0,0,1,1}}; 

  //double threshold = 18.5;

  cout << "\nPhantom" << endl;
  int row, col;  
  for (row = 0; row < n; row++) {
    for (col = 0; col < n; col++)
        cout << phantom[row][col] << " ";
    cout << endl;
  }

  //grayImage
  short grayImage[N][N];
  for (row = 0; row < N; row++)
    for (col = 0; col < N; col++)
        grayImage[row][col] = 0;

  int r,c;

  for (row = 0; row < N; row++)
    for (col = 0; col < N; col++) {
      r = row/50;
      c = col/50;
      if (phantom[r][c] == 0)
        grayImage[row][col] = 224;
    } 

  Display image01(grayImage,"output");

  int verticalMeasurements[10] = {10,10,3,3,3,3,3,3,10,10};
  int horizontalMeasurements[10] = {4,6,8,10,8,6,4,4,4,4};
  int diagonalMeasurements[19] = {1,2,2,2,2,2,2,2,6,8,7,4,3,4,3,3,2,2,1};
  int antiDiagonalMeasurements[19] = {1,2,2,3,3,4,3,4,7,8,6,2,2,2,2,2,2,2,1};

  cout << "\n\nVertical measurements"<<endl;
  for (col = 0; col < 10; col++)
    cout << verticalMeasurements[col] << " ";

  cout << "\n\nHorizontal measurements"<<endl;
  for (col = 0; col < 10; col++)
    cout << horizontalMeasurements[col] << " ";

  cout << "\n\nDiagonal measurements"<<endl;
  for (col = 0; col < 19; col++)
    cout << diagonalMeasurements[col] << " ";

  cout << "\n\nAnti-diagonal measurements"<<endl;
  for (col = 0; col < 19; col++)
    cout << antiDiagonalMeasurements[col] << " ";

  //Reconstruction
  short reconstruction[n][n];
  for (row = 0; row < n; row++)
    for (col = 0; col < n; col++)
      reconstruction[row][col] = 0;

  cout << "\n\nReconstruction from vertical rays"<<endl;
  for (row = 0; row < n; row++)
    for (col = 0; col < n; col++)
      reconstruction[row][col] += verticalMeasurements[col];  

  for (row = 0; row < n; row++) {
    for (col = 0; col < n; col++)
        cout << reconstruction[row][col]<< " ";
    cout << endl;
  } 

  cout << "\n\nReconstruction from horizontal rays"<<endl;
  for (row = 0; row < n; row++)
    for (col = 0; col < n; col++)
      reconstruction[row][col] += horizontalMeasurements[row];

  for (row = 0; row < n; row++) {
    for (col = 0; col < n; col++)
        cout << reconstruction[row][col] << " ";
    cout << endl;
  } 

  cout << "\n\nReconstruction from diagonal rays"<<endl;
  int x = n - 1, y = 0, z = 0;

  for(y = 0; y < n; y++) line2(x,y,x-y,0,diagonalMeasurements[z++],reconstruction);

  y = n - 1;
  
  for(x = y - 1; x >= 0; x--) line2(x,y,0,y-x,diagonalMeasurements[z++],reconstruction);

  for (row = 0; row < n; row++) {
    for (col = 0; col < n; col++)
      cout << reconstruction[row][col] << " ";
    cout << endl;
  } 


  cout << "\n\nReconstruction from anti-diagonal rays"<<endl;
  
  x = 0, y = 0, z = 0;
  for(y = 0; y < n; y++) line2(x,y,y,x,antiDiagonalMeasurements[z++],reconstruction);

  y = n - 1;
  for(x = 1; x < n; x++) line2(x,y,y,x,antiDiagonalMeasurements[z++],reconstruction);
  
  for (row = 0; row < n; row++) {
    for (col = 0; col < n; col++)
        cout << reconstruction[row][col] << " ";
    cout << endl;
  } 
  
  for (row = 0; row < n; row++) {
    for (col = 0; col < n; col++)
        if(reconstruction[row][col] > 18.5) reconstruction[row][col] = 1;
        else reconstruction[row][col] = 0;
  } 

  for (row = 0; row < N; row++)
    for (col = 0; col < N; col++)
        grayImage[row][col] = 0;


  for (row = 0; row < N; row++)
    for (col = 0; col < N; col++) {
      r = row/50;
      c = col/50;
      if (reconstruction[r][c] == 0)
        grayImage[row][col] = 224;
    } 

  Display image02(grayImage,"output2");

  return 0;

}
