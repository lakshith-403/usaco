/*
ID: liangyi1
PROG: rect1
LANG: C++
*/
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Rect {
  int x1, y1, x2, y2;
  int color;
} r[1001];

int a, b, n;
int max_color = 0;
int area[2501];

void ComputeArea(Rect r_old, int pos) {
  while (pos <= n && (r_old.x2 <= r[pos].x1 || r_old.x1 >= r[pos].x2 ||
      r_old.y2 <= r[pos].y1 || r_old.y1 >= r[pos].y2)) {
    ++pos;
  }
  if (pos > n) {
    area[r_old.color] += (r_old.x2 - r_old.x1) * (r_old.y2 - r_old.y1);
  } else {
    if (r_old.x1 < r[pos].x1) {
      Rect r_new(r_old);
      r_new.x2 = r[pos].x1;
      r_old.x1 = r[pos].x1;
      ComputeArea(r_new, pos + 1);
    }
    if (r_old.x2 > r[pos].x2) {
      Rect r_new(r_old);
      r_new.x1 = r[pos].x2;
      r_old.x2 = r[pos].x2;
      ComputeArea(r_new, pos + 1);
    }
    if (r_old.y1 < r[pos].y1) {
      Rect r_new(r_old);
      r_new.y2 = r[pos].y1;
      ComputeArea(r_new, pos + 1);
    }
    if (r_old.y2 > r[pos].y2) {
      Rect r_new(r_old);
      r_new.y1 = r[pos].y2;
      ComputeArea(r_new, pos + 1);
    }
  }
}

int main() {
  ifstream fin("rect1.in");
  ofstream fout("rect1.out");

  fin >> a >> b >> n;
  r[0].x1 = 0;
  r[0].y1 = 0;
  r[0].x2 = a;
  r[0].y2 = b;
  r[0].color = 1;
  for (int i = 1; i <= n; ++i) {
    fin >> r[i].x1 >> r[i].y1 >> r[i].x2 >> r[i].y2
        >> r[i].color;
    max_color = max(max_color, r[i].color);
  }

  for (int i = n; i >= 0; --i) {
    ComputeArea(r[i], i + 1);
  }

  for (int i = 1; i <= max_color; ++i) {
    if (area[i] > 0) {
      fout << i << ' ' << area[i] << '\n';
    }
  }

  fin.close();
  fout.close();
  return 0;
}
