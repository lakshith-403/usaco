/*
ID: liangyi1
PROG: range
LANG: C++
*/
#include <fstream>
using namespace std;

int n;
int f[251][251];
int count[251];

int main() {
  ifstream fin("range.in");
  fin >> n;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      char c;
      fin >> c;
      f[i][j] = f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1];
      f[i][j] += (c == '1');
    }
  }
  fin.close();

  // Count.
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      int k = min(n - i, n - j);
      while (k > 0 && f[i + k][j + k] - f[i + k][j - 1] - f[i - 1][j + k] +
          f[i - 1][j - 1] != (k + 1) * (k + 1)) {
        --k;
      }
      while (k > 0) {
        ++count[k + 1];
        --k;
      }
    }
  }

  ofstream fout("range.out");
  for (int i = 2; i <= n; ++i) {
    if (count[i] == 0) break;
    fout << i << ' ' << count[i] << endl;
  }
  fout.close();
  return 0;
}
