/*
ID: liangyi1
PROG: fence4
LANG: C++
*/
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
using namespace std;

struct Point {
  double x, y;
  bool operator==(const Point& that) {
    return x == that.x && y == that.y;
  }
  friend ostream& operator<<(ostream&, const Point&);
};

ostream& operator<<(ostream& out, const Point& p) {
  out << p.x << ' ' << p.y;
  return out;
}

int n;
Point o, oo;  // oo = o + (1, 0);
Point p[201];
bool see[200];

double CrossProduct(const Point& a, const Point& b, const Point& c,
    const Point& d) {
  return (b.x - a.x) * (d.y - c.y) - (d.x - c.x) * (b.y - a.y);
}

double InnerProduct(const Point& a, const Point& b, const Point& c,
    const Point& d) {
  return (b.x - a.x) * (d.x - c.x) + (b.y - a.y) * (d.y - c.y);
}

double Angle(const Point& a, const Point& b, const Point& c, const Point& d) {
  double in = InnerProduct(a, b, c, d);
  double out = CrossProduct(a, b, c, d);
  return atan2(out, in);
}

// If point p falls on segment [a, b].
bool OnLine(const Point &p, const Point &a, const Point &b) {
  double cross = CrossProduct(p, a, b, a);
  if (cross != 0) return false;
  return InnerProduct(p, a, p, b) <= 0;
}

// Intersect not on the end points!
bool Intersect(const Point &a, const Point &b, const Point &c,
    const Point &d) {
  // Special case: one end point on the other segment.
  if (OnLine(a, c, d) || OnLine(b, c, d) || OnLine(c, a, b) ||
      OnLine(d, a, b)) return true;
  double cross1 = CrossProduct(a, b, a, c) * CrossProduct(a, b, a, d);
  double cross2 = CrossProduct(c, d, c, a) * CrossProduct(c, d, c, b);
  if (cross1 == 0 && cross2 == 0) {
    // Special case: 4 points on a line.
    double dx = abs(a.x + b.x - c.x - d.x) - abs(a.x - b.x) + abs(c.x - d.x);
    double dy = abs(a.y + b.y - c.y - d.y) - abs(a.y - b.y) + abs(c.y - d.y);
    return dx < 0 || dy < 0;
  } else {
    return cross1 < 0 && cross2 < 0;
  }
  return true;
}

bool IsFence() {
  // Points must be distinct.
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (i != j && p[i] == p[j]) return false;
  // Check for intersections.
  for (int i = 0; i < n - 1; ++i)
    for (int j = i + 2; j < n; ++j) {
      if (i == 0 && j == n - 1) continue;
      if (Intersect(p[i], p[i + 1], p[j], p[j + 1])) return false;
    }
  return true;
}

int compare(const void* e1, const void* e2) {
  const Point* p1 = static_cast<const Point*>(e1);
  const Point* p2 = static_cast<const Point*>(e2);
  if (CrossProduct(o, *p1, o, *p2) == 0 &&
      InnerProduct(o, *p1, o, *p2) > 0) return 0;
  double a1 = Angle(o, oo, o, *p1);
  double a2 = Angle(o, oo, o, *p2);
  if (a1 > a2) return 1; else return -1;
}

double Intercept(const Point& o, const Point& m, const Point& a,
    const Point& b) {
  double delta_y = b.y - a.y, delta_x = b.x - a.x;
  return (a.x * delta_y - a.y * delta_x + o.y * delta_x - o.x * delta_y) /
    CrossProduct(o, m, a, b);
}

int main() {
  ifstream fin("fence4.in");
  fin >> n;
  fin >> o.x >> o.y;
  oo.x = o.x + 1;
  oo.y = o.y;
  for (int i = 0; i < n; ++i) {
    fin >> p[i].x >> p[i].y;
  }
  fin.close();
  p[n] = p[0];
  p[n + 1] = p[1];

  ofstream fout("fence4.out");
  if (!IsFence()) {
    fout << "NOFENCE" << endl;
  } else {
    // Sort the points in counter-clockwise order from the observer.
    Point sp[201];
    memcpy(sp, p, sizeof(sp));
    qsort(sp, n, sizeof(Point), compare);
    sp[n] = sp[0];
    for (int i = 0; i < n; ++i) {
      // Skip zero angles.
      if (CrossProduct(o, sp[i], o, sp[i + 1]) == 0) continue;
      // Skip too large angles (usually the last one).
      if (Angle(o, sp[i], o, sp[i + 1]) <= 0) continue;
      // A ray inside this angle: o -> mp
      Point mp = {
        (sp[i].x + sp[i + 1].x) / 2,
        (sp[i].y + sp[i + 1].y) / 2
      };
      // Which segment blocks this ray?
      int saw = -1;
      double best;
      for (int j = 0; j < n; ++j) {
        // Can't see parallel segments.
        if (CrossProduct(o, mp, p[j], p[j + 1]) == 0) continue;
        if (CrossProduct(o, mp, o, p[j]) *
            CrossProduct(o, mp, o, p[j + 1]) > 0) continue;
        double intercept = Intercept(o, mp, p[j], p[j + 1]);
        if (intercept <= 0) continue;
        if (saw == -1 || best > intercept) {
          best = intercept;
          saw = j;
        }
      }
      see[saw] = true;
    }
    int total = 0;
    for (int i = 0; i < n; ++i) {
      if (see[i]) ++total;
    }
    fout << total << endl;
    for (int i = 0; i < n - 2; ++i) {
      if (see[i]) fout << p[i] << ' ' << p[i + 1] << endl;
    }
    if (see[n - 1]) fout << p[0] << ' ' << p[n - 1] << endl;
    if (see[n - 2]) fout << p[n - 2] << ' ' << p[n - 1] << endl;
  }
  fout.close();
  return 0;
}
