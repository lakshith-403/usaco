/*
ID: liangyi1
PROG: stamps
LANG: C++
*/
#include <fstream>
#include <iostream>
using namespace std;

unsigned char f[2000001];

int main() {
  ifstream fin("stamps.in");
  int k, n, max_stamp = 0;
  int stamp[50];
  fin >> k >> n;
  for (int i = 0; i < n; ++i) {
    fin >> stamp[i];
    max_stamp = max(max_stamp, stamp[i]);
  }
  fin.close();

  ofstream fout("stamps.out");
  int max_sum = k * max_stamp;
  int i;
  for (i = 0; i <= max_sum; ++i) {
    if (i > 0 && f[i] == 0) {
      fout << i - 1 << endl;
      break;
    }
    if (f[i] == k) {
      continue;
    }
    for (int j = 0; j < n; ++j) {
      if (i + stamp[j] <= max_sum && (f[i + stamp[j]] == 0 ||
            f[i + stamp[j]] > f[i] + 1)) {
        f[i + stamp[j]] = f[i] + 1;
      }
    }
  }
  if (i > max_sum) {
    fout << max_sum << endl;
  }
  fout.close();
  return 0;
}
