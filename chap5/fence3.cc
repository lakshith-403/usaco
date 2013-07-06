/*
ID: liangyi1
PROG: fence3
LANG: C++
*/
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

int n;

struct Fence {
  int x1, y1, x2, y2;
} f[150];

struct Grid {
  int x, y;
  double score;

  bool operator<(const Grid &that) const {
    return this->score < that.score;
  }
};

void Swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

inline double Distance(double x1, double y1, double x2, double y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double ComputeDistance(double x, double y) {
  double ret = 0;
  for (int i = 0; i < n; i++)
    if (f[i].x1 == f[i].x2) {  // Vertical.
      if (f[i].y2 < y)
        ret += Distance(x, y, f[i].x2, f[i].y2);
      else if (f[i].y1 > y)
        ret += Distance(x, y, f[i].x1, f[i].y1);
      else
        ret += fabs(x - f[i].x1);
    } else {
      if (f[i].x2 < x)
        ret += Distance(x, y, f[i].x2, f[i].y2);
      else if (f[i].x1 > x)
        ret += Distance(x, y, f[i].x1, f[i].y1);
      else
        ret += fabs(y - f[i].y1);
    }
  return ret;
}

int main() {
  ifstream fin("fence3.in");
  fin >> n;
  for (int i = 0; i < n; i++) {
    fin >> f[i].x1 >> f[i].y1 >> f[i].x2 >> f[i].y2;
    if (f[i].x1 > f[i].x2) Swap(&f[i].x1, &f[i].x2);
    if (f[i].y1 > f[i].y2) Swap(&f[i].y1, &f[i].y2);
  }
  fin.close();

  // Compute the quality (average total length) of each grid.
  vector<Grid> grids;
  for (int i = 0; i < 100; i++)
    for (int j = 0; j < 100; j++) {
      Grid g;
      g.x = i;
      g.y = j;
      g.score = 0;
      for (int k = 0; k < 5; k++) {
        g.score += ComputeDistance(i + static_cast<double>(rand()) / RAND_MAX,
            j + static_cast<double>(rand()) / RAND_MAX);
      }
      g.score /= 5;
      grids.push_back(g);
    }
  sort(grids.begin(), grids.end());

  // Test in the top 4 grids.
  double best_x, best_y, best = 1e20;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 100; j++)
      for (int k = 0; k < 100; k++) {
        double sum = ComputeDistance(j / 100.0 + grids[i].x,
            k / 100.0 + grids[i].y);
        if (sum < best) {
          best = sum;
          best_x = j / 100.0 + grids[i].x;
          best_y = k / 100.0 + grids[i].y;
        }
      }
  }

  ofstream fout("fence3.out");
  fout << fixed << setprecision(1) << best_x << ' ' << best_y << ' ' << best
       << endl;
  fout.close();
  return 0;
}
