/*
ID: liangyi1
PROG: castle
LANG: C++
*/
#include <fstream>
#include <iostream>
using namespace std;

int m, n;
int num_parts;
int part[50][50];
int wall[50][50];
int area[2501];

const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {-1, 0, 1, 0};

void Fill(int x, int y) {
  part[x][y] = num_parts;
  ++area[num_parts];
  for (int i = 0; i < 4; ++i) {
    if (wall[x][y] & (1 << i)) continue;  // There is a wall.
    int nx = x + dx[i];
    int ny = y + dy[i];
    if (nx >= 0 && nx < n && ny >= 0 && ny < m && part[nx][ny] == 0) {
      Fill(nx, ny);
    }
  }
}

int main() {
  ifstream fin("castle.in");
  ofstream fout("castle.out");
  fin >> m >> n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      fin >> wall[i][j];
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (part[i][j] == 0) {
        ++num_parts;
        Fill(i, j);
      }
    }
  }
  fout << num_parts << endl;
  int max_area = 0;
  for (int i = 1; i <= num_parts; ++i) {
    max_area = max(max_area, area[i]);
  }
  fout << max_area << endl;
  // Find the wall.
  max_area = 0;
  int ans_x, ans_y;
  char ans_direction;
  for (int y = 0; y < m; ++y) {
    for (int x = n - 1; x >= 0; --x) {
      // For north.
      if (x > 0 && part[x][y] != part[x - 1][y]) {
        int sum_area = area[part[x][y]] + area[part[x - 1][y]];
        if (sum_area > max_area) {
          max_area = sum_area;
          ans_x = x;
          ans_y = y;
          ans_direction = 'N';
        }
      }
      // For east.
      if (y < m - 1 && part[x][y] != part[x][y + 1]) {
        int sum_area = area[part[x][y]] + area[part[x][y + 1]];
        if (sum_area > max_area) {
          max_area = sum_area;
          ans_x = x;
          ans_y = y;
          ans_direction = 'E';
        }
      }
    }
  }
  fout << max_area << endl;
  fout << ans_x + 1 << ' ' << ans_y + 1 << ' ' << ans_direction << endl;
  fin.close();
  fout.close();
  return 0;
}
