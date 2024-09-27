#include <iostream>
#include <vector>
#include "Display.h"
#include "line_functions.h"
using namespace std;

const int N = 500;
const int n = 10;

int main()
{
  int phantom[n][n] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 1, 1, 1, 0, 0}, {0, 0, 0, 0, 1, 1, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
  // threshold = 18.5;

  cout << "\nPhantom" << endl;
  int row, col;
  for (row = 0; row < n; row++)
  {
    for (col = 0; col < n; col++)
      cout << phantom[row][col] << " ";
    cout << endl;
  }

  // grayImage
  short grayImage[N][N];
  for (row = 0; row < N; row++)
    for (col = 0; col < N; col++)
      grayImage[row][col] = 0;

  int r, c;

  for (row = 0; row < N; row++)
    for (col = 0; col < N; col++)
    {
      r = row / 50;
      c = col / 50;
      if (phantom[r][c] == 0)
        grayImage[row][col] = 224;
    }

  Display image01(grayImage, "outputZ");

  // Computing vertical rays

  vector<int> hor;

  for (row = 0; row < n; row++)
  {
    int res = 0;
    for (col = 0; col < n; col++)
    {
      res += phantom[row][col];
    }
    hor.push_back(res);
  }

  vector<int> ve;
  // Computing horizontal rays
  for (row = 0; row < n; row++)
  {
    int res = 0;
    for (col = 0; col < n; col++)
    {
      res += phantom[col][row];
    }
    ve.push_back(res);
  }

  cout << endl
       << endl;
  for (int x : ve)
    cout << x << " ";
  cout << endl
       << endl;
  for (int x : hor)
    cout << x << " ";

  // Computing diagonal rays
  vector<int> dia;
  int x = n - 1, y = 0;
  for (y = 0; y < n; y++)
  {
    dia.push_back(line1(x, y, x - y, 0, phantom));
  }
  y = n - 1;
  for (x = y - 1; x >= 0; x--)
  {
    dia.push_back(line1(x, y, 0, y - x, phantom));
  }

  cout << endl;
  for (int x : dia)
    cout << x << " ";

  // Computing anti-diagonal rays
  vector<int> anti;
  x = 0;
  y = 0;
  for (y = 0; y < n; y++)
  {
    anti.push_back(line1(x, y, y, x, phantom));
  }
  y = n - 1;
  for (x = 1; x < n; x++)
  {
    anti.push_back(line1(x, y, y, x, phantom));
  }
  cout << endl;
  for (int x : anti)
    cout << x << " ";

  // Reconstruction
  short reconstruction[n][n];
  for (row = 0; row < n; row++)
    for (col = 0; col < n; col++)
      reconstruction[row][col] = 0;

  // Reconstruction from vertical rays"
  for (row = 0; row < n; row++)
    for (col = 0; col < n; col++)
      reconstruction[row][col] += ve[col];

  cout << endl
       << endl;
  for (row = 0; row < n; row++)
  {
    for (col = 0; col < n; col++)
      cout << reconstruction[row][col] << " ";
    cout << endl;
  }

  // Reconstruction from horizontal rays
  for (row = 0; row < n; row++)
    for (col = 0; col < n; col++)
      reconstruction[row][col] += hor[row];

  cout << endl
       << endl;
  for (row = 0; row < n; row++)
  {
    for (col = 0; col < n; col++)
      cout << reconstruction[row][col] << " ";
    cout << endl;
  }

  // Reconstruction from diagonal rays
  x = n - 1, y = 0;
  int z = 0;

  for (y = 0; y < n; y++)
    line2(x, y, x - y, 0, dia[z++], reconstruction);

  y = n - 1;

  for (x = y - 1; x >= 0; x--)
    line2(x, y, 0, y - x, dia[z++], reconstruction);
  cout << endl
       << endl;
  for (row = 0; row < n; row++)
  {
    for (col = 0; col < n; col++)
      cout << reconstruction[row][col] << " ";
    cout << endl;
  }

  // Reconstruction from anti-diagonal rays

  x = 0, y = 0, z = 0;
  for (y = 0; y < n; y++)
    line2(x, y, y, x, anti[z++], reconstruction);

  y = n - 1;
  for (x = 1; x < n; x++)
    line2(x, y, y, x, anti[z++], reconstruction);

  cout << endl
       << endl;
  for (row = 0; row < n; row++)
  {
    for (col = 0; col < n; col++)
      cout << reconstruction[row][col] << " ";
    cout << endl;
  }

  for (row = 0; row < n; row++)
  {
    for (col = 0; col < n; col++)
      if (reconstruction[row][col] > 18.5)
        reconstruction[row][col] = 1;
      else
        reconstruction[row][col] = 0;
  }

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

  Display image02(grayImage, "outputZZ");

  return 0;
}
