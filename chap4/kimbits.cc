/*
ID: liangyi1
PROG: kimbits
LANG: C++
*/
#include <fstream>
#include <iostream>
using namespace std;

int main() {
  ifstream fin("kimbits.in");
  unsigned n, l, rank;
  fin >> n >> l >> rank;
  fin.close();

  int num[32][32]; // num[i][j]: length i has l bits.
  num[0][0] = 1;
  for (unsigned i = 1; i <= n; ++i) {
    num[i][0] = num[i][i] = 1;
    for (unsigned j = 1; j <= min(i - 1, l); ++j) {
      num[i][j] = num[i - 1][j] + num[i - 1][j - 1];
    }
  }

  string ans;
  int pos = n, ones = l;
  while (pos > 0) {
    // Count how many strings left if we choose 0 at this pos.
    unsigned sum = 0;
    for (int i = 0; i <= min(ones, pos - 1); ++i) {
      sum += num[pos - 1][i];
    }
    if (sum >= rank) {
      ans += '0';
    } else {
      ans += '1';
      --ones;
      rank -= sum;
    }
    --pos;
  }

  ofstream fout("kimbits.out");
  fout << ans << endl;
  fout.close();
  return 0;
}
