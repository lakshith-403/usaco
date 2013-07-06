/*
ID: liangyi1
PROG: ratios
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;

int gcd(int a, int b) {
  if (b == 0) {
    return a;
  } else {
    return gcd(b, a % b);
  }
}

int main() {
  int a[4], b[4], c[4];
  ifstream fin("ratios.in");
  for (int i = 0; i < 4; ++i) {
    fin >> a[i] >> b[i] >> c[i];
  }
  fin.close();

  int min_sum = -1, bx, by, bz, bt;
  for (int x = 0; x < 100; ++x) {
    for (int y = 0; y < 100; ++y) {
      for (int z = 0; z < 100; ++z) {
        if (min_sum != -1 && x + y + z > min_sum) {
          continue;
        }
        int sum_a = a[1] * x + a[2] * y + a[3] * z;
        int sum_b = b[1] * x + b[2] * y + b[3] * z;
        int sum_c = c[1] * x + c[2] * y + c[3] * z;
        int t;
        if (a[0] != 0) {
          if (sum_a % a[0]) continue;
          t = sum_a / a[0];
          if (b[0] * t != sum_b || c[0] * t != sum_c) continue;
        } else if (b[0] != 0) {
          if (sum_b % b[0]) continue;
          t = sum_b / b[0];
          if (c[0] * t != sum_c) continue;
        } else if (c[0] != 0) {
          if (sum_c % c[0]) continue;
          t = sum_c / c[0];
        }
        if (t == 0) continue;
        min_sum = x + y + z;
        bx = x;
        by = y;
        bz = z;
        bt = t;
      }
    }
  }

  ofstream fout("ratios.out");
  if (min_sum == -1) {
    fout << "NONE" << endl;
  } else {
    fout << bx << ' ' << by << ' ' << bz << ' ';
    if (a[0] != 0) {
      fout << (a[1] * bx + a[2] * by + a[3] * bz) / a[0] << endl;
    } else if (b[0] != 0) {
      fout << (b[1] * bx + b[2] * by + b[3] * bz) / b[0] << endl;
    } else if (c[0] != 0) {
      fout << (c[1] * bx + c[2] * by + c[3] * bz) / c[0] << endl;
    } else {
      fout << '0' << endl;
    }
  }
  fout.close();
  return 0;
}
