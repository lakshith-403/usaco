/*
ID: liangyi1
PROG: camelot
LANG: C++
*/
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

int r, c, sx, sy;
int n;  // Number of knights.
int kx[780], ky[780];
int dis[26][30][26][30];

const int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int dy[8] = {-1, -2, -2, -1, 1, 2, 2, 1};

void CalculateDistance() {
  queue<pair<int, int> > q;
  for (int i = 0; i < c; ++i) {
    for (int j = 0; j < r; ++j) {
      // Initialize.
      for (int x = 0; x < c; ++x) {
        for (int y = 0; y < r; ++y) {
          dis[i][j][x][y] = -1;
        }
      }
      dis[i][j][i][j] = 0;
      q.push(make_pair(i, j));
      while (!q.empty()) {
        pair<int, int> head = q.front();
        q.pop();
        for (int k = 0; k < 8; ++k) {
          int nx = head.first + dx[k];
          int ny = head.second + dy[k];
          if (nx >= 0 && nx < c && ny >= 0 && ny < r &&
              dis[i][j][nx][ny] == -1) {
            dis[i][j][nx][ny] = dis[i][j][head.first][head.second] + 1;
            q.push(make_pair(nx, ny));
          }
        }
      }
    }
  }
}

int KingWalk(int x, int y) {
  int x_dif = abs(x - sx);
  int y_dif = abs(y - sy);
  return x_dif > y_dif ? x_dif : y_dif;
}

int TwoMenOneHorse(int kx, int ky, int tx, int ty) {
  static const int bound = 3;
  int best = 10000000;
  for (int mx = max(0, sx - bound); mx <= min(c - 1, sx + bound); ++mx) {
    for (int my = max(0, sy - bound); my <= min(r - 1, sy + bound); ++my) {
      if (dis[kx][ky][mx][my] == -1) continue;
      if (dis[mx][my][kx][ky] == -1) continue;
      int value = dis[kx][ky][mx][my] + KingWalk(mx, my) + dis[mx][my][tx][ty];
      if (value < best) best = value;
    }
  }
  return best;
}

int main() {
  char x;
  int y;
  ifstream fin("camelot.in");
  fin >> r >> c;
  fin >> x >> y;
  sx = x - 'A';
  sy = y - 1;
  while (fin >> x >> y) {
    kx[n] = x - 'A';
    ky[n] = y - 1;
    ++n;
  }
  CalculateDistance();

  // Enumerate the destination.
  int ans = 100000000;
  for (int tx = 0; tx < c; ++tx) {
    for (int ty = 0; ty < r; ++ty) {
      // Count all the knights' steps.
      int knight_sum = 0;
      bool ok = true;
      for (int i = 0; i < n; ++i) {
        if (dis[kx[i]][ky[i]][tx][ty] == -1) {
          ok = false;
          break;
        }
        knight_sum += dis[kx[i]][ky[i]][tx][ty];
      }
      if (!ok) continue;
      int best = knight_sum + KingWalk(tx, ty);
      // Enumerate the king picker.
      for (int i = 0; i < n; ++i) {
        int other_knights = knight_sum - dis[kx[i]][ky[i]][tx][ty];
        int duo = TwoMenOneHorse(kx[i], ky[i], tx, ty);
        if (duo == -1) continue;
        if (other_knights + duo < best) best = other_knights + duo;
      }
      if (best < ans) ans = best;
    }
  }

  ofstream fout("camelot.out");
  fout << ans << endl;
  fout.close();
  return 0;
}
