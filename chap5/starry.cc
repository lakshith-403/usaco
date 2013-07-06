/*
ID: liangyi1
PROG: starry
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

int w, h, total;

char sky[100][101];

struct Cluster {
  int w, h;  // Size of the bounding rectangle. 
  bool map[100][100];
} c[26];

const int dx[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
const int dy[8] = {1, 1, 1, 0, -1, -1, -1, 0};

void GetCluster(int x, int y, Cluster* p_c) {
  // Flood fill.
  memset(p_c->map, 0, sizeof(p_c->map));
  queue< pair<int, int> > q;
  q.push(make_pair(x, y));
  p_c->map[x][y] = true;
  int min_x = 101, min_y = 101;
  int max_x = 0, max_y = 0;
  while (!q.empty()) {
    pair<int, int> pos = q.front();
    q.pop();
    min_x = min(pos.first, min_x);
    min_y = min(pos.second, min_y);
    max_x = max(pos.first, max_x);
    max_y = max(pos.second, max_y);
    for (int i = 0; i < 8; i++) {
      int nx = pos.first + dx[i];
      int ny = pos.second + dy[i];
      if (nx >= 0 && nx < h && ny >= 0 && ny < w && !(p_c->map[nx][ny]) &&
          sky[nx][ny] == '1') {
        q.push(make_pair(nx, ny));
        p_c->map[nx][ny] = true;
      }
    }
  }

  // Shift the pattern to origin.
  p_c->h = max_x - min_x + 1;
  p_c->w = max_y - min_y + 1;
  for (int i = 0; i < p_c->h; i++)
    for (int j = 0; j < p_c->w; j++) {
      p_c->map[i][j] = p_c->map[min_x + i][min_y + j];
    }
}

void Color(int x, int y, char c) {
  queue< pair<int, int> > q;
  q.push(make_pair(x, y));
  sky[x][y] = c;
  while (!q.empty()) {
    pair<int, int> pos = q.front();
    q.pop();
    for (int i = 0; i < 8; i++) {
      int nx = pos.first + dx[i];
      int ny = pos.second + dy[i];
      if (nx >= 0 && nx < h && ny >= 0 && ny < w && sky[nx][ny] == '1') {
        q.push(make_pair(nx, ny));
        sky[nx][ny] = c;
      }
    }
  }
}

void FlipHorizontal(Cluster* p_c) {
  const int& h = p_c->h;
  const int& w = p_c->w;
  for (int i = 0; i < h; i++)
    for (int j = 0; j < w / 2; j++) {
      bool temp = p_c->map[i][j];
      p_c->map[i][j] = p_c->map[i][w - 1 - j];
      p_c->map[i][w - 1 - j] = temp;
    }
}

void FlipVertical(Cluster* p_c) {
  const int& h = p_c->h;
  const int& w = p_c->w;
  for (int i = 0; i < h / 2; i++)
    for (int j = 0; j < w; j++) {
      bool temp = p_c->map[i][j];
      p_c->map[i][j] = p_c->map[h - 1 - i][j];
      p_c->map[h - 1 - i][j] = temp;
    }
}

void Transpose(Cluster* p_c) {
  int len = max(p_c->w, p_c->h);
  for (int i = 0; i < len; i++)
    for (int j = i + 1; j < len; j++) {
      bool temp = p_c->map[i][j];
      p_c->map[i][j] = p_c->map[j][i];
      p_c->map[j][i] = temp;
    }
  int temp = p_c->w;
  p_c->w = p_c->h;
  p_c->h = temp;
}

bool Same(const Cluster& a, const Cluster& b) {
  if (a.h != b.h || a.w != b.w) return false;
  for (int i = 0; i < a.h; i++)
    for (int j = 0; j < a.w; j++)
      if (a.map[i][j] != b.map[i][j])
        return false;
  return true;
}

bool IsSimilar(Cluster& a, Cluster& b) {
  if (a.h == b.h && a.w == b.w) {
    for (int i = 0; i < 4; i++) {
      Cluster c = b;
      if (i & 1) FlipHorizontal(&c);
      if (i & 2) FlipVertical(&c);
      if (Same(a, c)) return true;
    }
  }
  if (a.h == b.w && a.w == b.h) {
    Cluster c = b;
    Transpose(&c);
    for (int i = 0; i < 4; i++) {
      Cluster d = c;
      if (i & 1) FlipHorizontal(&d);
      if (i & 2) FlipVertical(&d);
      if (Same(a, d)) return true;
    }
  }
  return false;
}

int main() {
  ifstream fin("starry.in");
  fin >> w >> h;
  for (int i = 0; i < h; i++)
    fin >> sky[i];
  fin.close();

  for (int i = 0; i < h; i++)
    for (int j = 0; j < w; j++)
      if (sky[i][j] == '1') {
        Cluster new_c;
        GetCluster(i, j, &new_c);
        int id = total;
        for (int k = 0; k < total; k++) {
          if (IsSimilar(c[k], new_c)) {
            id = k;
            break;
          }
        }
        if (id == total)
          c[total++] = new_c;
        // Color the new cluster with letters.
        Color(i, j, id + 'a');
      }

  ofstream fout("starry.out");
  for (int i = 0; i < h; i++)
    fout << sky[i] << endl;
  fout.close();
  return 0;
}
