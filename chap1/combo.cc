/*
ID: liangyi1
PROG: combo
LANG: C++
*/
#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

int n;

bool InRange(int a, int b) {
  if (a >= b) {
    int temp = a;
    a = b;
    b = temp;
  }
  // a <= b
  return b - a <= 2 || b - a >= n - 2;
}

int main() {
  ifstream fin("combo.in");
  ofstream fout("combo.out");
  fin >> n;
  int a[3], b[3];
  fin >> a[0] >> a[1] >> a[2];
  fin >> b[0] >> b[1] >> b[2];
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      for (int k = 1; k <= n; ++k) {
        if (InRange(i, a[0]) && InRange(j, a[1]) && InRange(k, a[2])) {
          ++ans;
          continue;
        }
        if (InRange(i, b[0]) && InRange(j, b[1]) && InRange(k, b[2])) {
          ++ans;
        }
      }
  fout << ans << endl;
  fin.close();
  fout.close();
  return 0;
}
