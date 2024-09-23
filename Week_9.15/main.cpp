//Identifying pixels
//Edit By: Ziyang Li
//Date: 9/23/24
//Description：Identifying pixels (in a 2D image) corresponding to X-rays in four directions (horizontal, vertical, diagonal, and anti-diagonal)

#include <iostream>
using namespace std;

const int n = 10;
//const int n = 20;


int main() {
  //short verticalRays[n][n];
  //short horizontalRays[n][n];
  short diagonalRays[n][n];
  short antiDiagonalRays[n][n];
  int row, col;
  short ray;

  //Computing vertical rays
  /*
  for (row = 0; row < n; row++) {
    ray = 11;
    for (col = 0; col < n; col++) {
      verticalRays[row][col] = ray;
      ray++;
    }		
  }

  //Computing horizontal rays
  ray = 11;
  for (row = 0; row < n; row++) {		
    for (col = 0; col < n; col++) {
      horizontalRays[row][col] = ray;
    }		
    ray++;
  }
  */

  //Computing diagonal rays
  ray = 11;
  int x = n - 1, y = 0;
  for(y = 0; y < n; y++){
    line1(x,y,x-y,0,ray,diagonalRays);
    ray++;
  }
  y = n - 1;
  for(x = y - 1; x >= 0; x--){
    line1(x,y,0,y-x,ray,diagonalRays);
    ray++;
  }

  //Computing anti-diagonal rays
  ray = 11;
  x = 0;
  y = 0;
  for(y = 0; y < n; y++){
    line1(x,y,y,x,ray,antiDiagonalRays);
    ray++;
  }
  y = n - 1;
  for(x = 1; x < n; x++){
    line1(x,y,y,x,ray,antiDiagonalRays);
    ray++;
  }

  //**********************************
  //*****Displaying vertical rays*****
  //**********************************

  //Displaying vertical rays
  /*
  cout << endl << "Vertical rays:" << endl;
  for (row = 0; row < n; row++) {
    for (col = 0; col < n; col++)
      cout << verticalRays[row][col] << " ";
    cout << endl;
  }

  //Displaying horizontal rays
  cout << endl << "Horizontal rays:" << endl;
  for (row = 0; row < n; row++) {
    for (col = 0; col < n; col++)
      cout << horizontalRays[row][col] << " ";
    cout << endl;
  }
  */

  //Displaying diagonal rays
  cout << endl << "diagonal rays:" << endl;
  for (row = 0; row < n; row++) {
    for (col = 0; col < n; col++)
      cout << diagonalRays[row][col] << " ";
    cout << endl;
  }
  

  //Displaying anti-diagonal rays
  cout << endl << "anti-diagonal rays:" << endl;
  for (row = 0; row < n; row++) {
    for (col = 0; col < n; col++)
      cout << antiDiagonalRays[row][col] << " ";
    cout << endl;
  }

  return 0;
}
