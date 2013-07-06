/*
ID: liangyi1
PROG: fc
LANG: C++
*/
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int n;
struct Point {
  public:
    double x, y;
} p[10000], hull[10000];

double InnerProduct(const Point& p0, const Point& p1, const Point& p2) {
  return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

double Distance(const Point& p1, const Point& p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int Compare(const void* e1, const void* e2) {
  const Point *p1 = static_cast<const Point*>(e1);
  const Point *p2 = static_cast<const Point*>(e2);
  double ret = InnerProduct(p[0], *p1, *p2);
  return (ret < 0) * 2 - 1;
}

int main() {
  ifstream fin("fc.in");
  fin >> n;
  for (int i = 0; i < n; i++) {
    int x, y;
    fin >> p[i].x >> p[i].y;
  }
  fin.close();

  // Find the lowest point.
  for (int i = 1; i < n; i++) {
    if (p[i].y < p[0].y || (p[i].y == p[0].y && p[i].x < p[0].x)) {
      Point temp = p[i];
      p[i] = p[0];
      p[0] = temp;
    }
  }

  qsort(p + 1, n - 1, sizeof(Point), Compare);
  hull[0] = p[0];
  hull[1] = p[1];
  int total = 2;
  for (int i = 2; i < n; i++) {
    while (InnerProduct(hull[total - 2], hull[total - 1], p[i]) <= 0)
      total--;
    hull[total++] = p[i];
  }

  double ans = Distance(hull[0], hull[total - 1]);
  for (int i = 0; i < total - 1; i++)
    ans += Distance(hull[i], hull[i + 1]);

  ofstream fout("fc.out");
  fout << setprecision(2) << fixed << ans << endl;
  fout.close();
  return 0;
}
