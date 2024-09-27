#include <iostream>
#include "../Week_9.22/Display.h"
#include "../Week_9.22/line_functions.h"
using namespace std;

const int N = 500;
const int n = 10;

int main()
{
  // use threshold 19.5
  int verticalMeasurements[10] = {0, 10, 10, 2, 2, 2, 2, 10, 10, 0};
  int horizontalMeasurements[10] = {4, 4, 4, 4, 8, 8, 4, 4, 4, 4};
  int diagonalMeasurements[19] = {0, 1, 2, 2, 2, 2, 2, 4, 6, 6, 6, 4, 2, 2, 2, 2, 2, 1, 0};
  int antiDiagonalMeasurements[19] = {0, 1, 2, 2, 2, 2, 2, 4, 6, 6, 6, 4, 2, 2, 2, 2, 2, 1, 0};
  // Reconstruction
  int row, col;
  short reconstruction[n][n];
  for (row = 0; row < n; row++)
    for (col = 0; col < n; col++)
      reconstruction[row][col] = 0;

  cout << "\n\nReconstruction from vertical rays" << endl;
  for (row = 0; row < n; row++)
    for (col = 0; col < n; col++)
      reconstruction[row][col] += verticalMeasurements[col];

  for (row = 0; row < n; row++)
  {
    for (col = 0; col < n; col++)
      cout << reconstruction[row][col] << " ";
    cout << endl;
  }

  cout << "\n\nReconstruction from horizontal rays" << endl;
  for (row = 0; row < n; row++)
    for (col = 0; col < n; col++)
      reconstruction[row][col] += horizontalMeasurements[row];

  for (row = 0; row < n; row++)
  {
    for (col = 0; col < n; col++)
      cout << reconstruction[row][col] << " ";
    cout << endl;
  }

  cout << "\n\nReconstruction from diagonal rays" << endl;
  int x = n - 1, y = 0, z = 0;

  for (y = 0; y < n; y++)
    line2(x, y, x - y, 0, diagonalMeasurements[z++], reconstruction);

  y = n - 1;

  for (x = y - 1; x >= 0; x--)
    line2(x, y, 0, y - x, diagonalMeasurements[z++], reconstruction);

  for (row = 0; row < n; row++)
  {
    for (col = 0; col < n; col++)
      cout << reconstruction[row][col] << " ";
    cout << endl;
  }

  cout << "\n\nReconstruction from anti-diagonal rays" << endl;

  x = 0, y = 0, z = 0;
  for (y = 0; y < n; y++)
    line2(x, y, y, x, antiDiagonalMeasurements[z++], reconstruction);

  y = n - 1;
  for (x = 1; x < n; x++)
    line2(x, y, y, x, antiDiagonalMeasurements[z++], reconstruction);

  for (row = 0; row < n; row++)
  {
    for (col = 0; col < n; col++)
      cout << reconstruction[row][col] << " ";
    cout << endl;
  }

  for (row = 0; row < n; row++)
  {
    for (col = 0; col < n; col++)
      if (reconstruction[row][col] > 19.5)
        reconstruction[row][col] = 1;
      else
        reconstruction[row][col] = 0;
  }

  short grayImage[N][N];
  int r, c;

  for (row = 0; row < N; row++)
    for (col = 0; col < N; col++)
      grayImage[row][col] = 0;

  for (row = 0; row < N; row++)
    for (col = 0; col < N; col++)
    {
      r = row / 50;
      c = col / 50;
      if (reconstruction[r][c] == 0)
        grayImage[row][col] = 224;
    }

  Display image02(grayImage, "output3");

  return 0;
}
