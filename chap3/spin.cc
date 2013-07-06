/*
ID: liangyi1
PROG: spin
LANG: C++
*/
#include <fstream>
using namespace std;

struct Wedge {
  int l, r;
};

int main() {
  Wedge w[5][5];
  int v[5], num[5];

  ifstream fin("spin.in");
  for (int i = 0; i < 5; ++i) {
    fin >> v[i] >> num[i];
    for (int j = 0; j < num[i]; ++j) {
      int span;
      fin >> w[i][j].l >> span;
      w[i][j].r = (w[i][j].l + span) % 360;
    }
  }

  int t;
  while (t < 360) {
    // Look for the hole.
    int angle;
    for (angle = 0; angle < 360; ++angle) {
      // Test all wheels.
      bool block = false;
      for (int i = 0; i < 5; ++i) {
        int j;
        for (j = 0; j < num[i]; ++j) {
          // Break if this angle is in a wedge.
          if (w[i][j].l <= w[i][j].r) {
            if (w[i][j].l <= angle && angle <= w[i][j].r) {
              break;
            }
          } else {
            if (angle >= w[i][j].l || angle <= w[i][j].r) {
              break;
            }
          }
        }
        if (j == num[i]) {
          block = true;
          break;
        }
      }
      if (!block) {
        break;  // Find an angle to see through.
      }
    }
    if (angle < 360) {
      break;
    }

    // Rotate.
    ++t;
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < num[i]; ++j) {
        w[i][j].l = (w[i][j].l + v[i]) % 360;
        w[i][j].r = (w[i][j].r + v[i]) % 360;
      }
    }
  }

  ofstream fout("spin.out");
  if (t < 360) {
    fout << t << endl;
  } else {
    fout << "none" << endl;
  }
  fout.close();
}
