/*
ID: liangyi1
PROG: game1
LANG: C++
*/
#include <fstream>
using namespace std;

int n;
int num[101], sum[101];
int f[101][101];

int main() {
  ifstream fin("game1.in");
  fin >> n;
  for (int i = 1; i <= n; ++i) {
    fin >> num[i];
    sum[i] = num[i] + sum[i - 1];
  }
  fin.close();

  // Dynamic programming.
  for (int i = 1; i <= n; ++i) {
    f[i][i] = num[i];
  }
  for (int len = 2; len <= n; ++len) {
    for (int i = 1; i <= n - len + 1; ++i) {
      int j = i + len - 1;
      int take_left = num[i] + (sum[j] - sum[i]) - f[i + 1][j];
      int take_right = num[j] + (sum[j - 1] - sum[i - 1]) - f[i][j - 1];
      f[i][j] = max(take_left, take_right);
    }
  }

  ofstream fout("game1.out");
  // Which number is taken at the first step?
  int take_left = num[1] + (sum[n] - sum[1]) - f[2][n];
  int take_right = num[n] + sum[n - 1] - f[1][n - 1];
  if (take_left > take_right) {
    fout << take_left << ' ' << f[2][n] << endl;
  } else {
    fout << take_right << ' ' << f[1][n - 1] << endl;
  }
  fout.close();
  return 0;;
}
