/*
ID: liangyi1
PROG: snail
LANG: C++
*/
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;

int n, b, best = 0, total;
bool bar[120][120];
bool go[120][120];

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
const int turn[4][2] = { {1, 3}, {0, 2}, {1, 3}, {0, 2} };

void Search(int x, int y, int dir) {
  for (int i = 0; i < 2; i++) {
    int nd = turn[dir][i];
    int ex = x + dx[nd], ey = y + dy[nd];
    bool move = false;
    while (ex >= 0 && ex < n && ey >= 0 && ey < n && !bar[ex][ey] &&
        !go[ex][ey]) {
      go[ex][ey] = true;
      total++;
      move = true;
      ex += dx[nd];
      ey += dy[nd];
    }
    if (total > best) best = total;
    // Test stopping.
    if (ex >= 0 && ex < n && ey >= 0 && ey < n && !bar[ex][ey]) {
      // Stop.
    } else if (move) {
      Search(ex - dx[nd], ey - dy[nd], nd);
    }
    // Backtracking.
    while (true) {
      ex -= dx[nd];
      ey -= dy[nd];
      if (ex == x && ey == y) break;
      go[ex][ey] = false;
      total--;
    }
  }
}

int main() {
  char buffer[5];
  ifstream fin("snail.in");
  fin >> n >> b;
  for (int i = 0; i < b; i++) {
    fin >> buffer;
    bar[atoi(&buffer[1]) - 1][buffer[0] - 'A'] = true;
  }
  fin.close();

  go[0][0] = true;
  int y = 0;
  total = 1;
  while (y < n - 1 && !bar[0][y + 1]) {
    go[0][y + 1] = true;
    y++;
    total++;
  }
  Search(0, y, 0);
  memset(go, 0, sizeof(go));
  go[0][0] = true;
  int x = 0;
  total = 1;
  while (x < n - 1 && !bar[x + 1][0]) {
    go[x + 1][0] = true;
    x++;
    total++;
  }
  Search(x, 0, 1);

  ofstream fout("snail.out");
  fout << best << endl;
  fout.close();
  return 0;
}
