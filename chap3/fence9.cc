/*
ID: liangyi1
PROG: fence9
LANG: C++
*/
#include <cmath>
#include <fstream>
using namespace std;

int main() {
  int n, m, p;
  ifstream fin("fence9.in");
  fin >> n >> m >> p;
  fin.close();

  int ans = 0;
  for (int i = 1; i < m; ++i) {
    double low = ceil(static_cast<double>(i * n + 0.5) / m);
    int high = floor(p - static_cast<double>((p - n) * i + 0.5) / m);
    if (low <= high) ans += high - low + 1;
  }
  ofstream fout("fence9.out");
  fout << ans << endl;
  fout.close();
  return 0;
}
