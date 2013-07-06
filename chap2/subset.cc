/*
ID: liangyi1
PROG: subset
LANG: C++
*/
#include <fstream>
#include <iostream>
using namespace std;

unsigned long f[40][2000];

int main() {
  ifstream fin("subset.in");
  ofstream fout("subset.out");
  int n;
  fin >> n;
  unsigned long sum = n * (n + 1) / 2;
  if (sum % 2 != 0) {
    fout << 0 << endl;
  } else {
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j <= sum; ++j) {
        f[i][j] = f[i - 1][j];
      }
      for (int j = i; j <= sum; ++j) {
        f[i][j] = f[i - 1][j] + f[i - 1][j - i];
      }
    }
    fout << f[n][sum / 2] / 2 << endl;
  }
  fin.close();
  fout.close();
  return 0;
}
