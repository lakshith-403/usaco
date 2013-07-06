/*
ID: liangyi1
PROG: rockers
LANG: C++
*/
#include <cstring>
#include <fstream>
using namespace std;

int main() {
  int n, t, m;
  int time[21];
  ifstream fin("rockers.in");
  fin >> n >> t >> m;
  for (int i = 1; i <= n; ++i) fin >> time[i];
  fin.close();

  // Dynamic programming.
  // State: first i songs, in j disks, k mins left in the last disk.
  int f[21][21][21];  
  memset(f, 0, sizeof(f));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= m; ++j) {
      for (int k = 0; k <= t; ++k) {
        // Skip the next song.
        if (f[i][j][k] > f[i + 1][j][k]) {
          f[i + 1][j][k] = f[i][j][k];
        }
        // Use the next song.
        if (j > 0 && time[i + 1] <= k) {
          if (f[i][j][k] + 1 > f[i + 1][j][k - time[i + 1]]) {
            f[i + 1][j][k - time[i + 1]] = f[i][j][k] + 1;
          }
        } else if (j < m && time[i + 1] <= t) {
          if (f[i][j][k] + 1 > f[i + 1][j + 1][t - time[i + 1]]) {
            f[i + 1][j + 1][t - time[i + 1]] = f[i][j][k] + 1;
          }
        }
      }
    }
  }
  int ans = 0;
  for (int i = 0; i <= m; ++i)
    for (int j = 0; j <= t; ++j)
      if (f[n][i][j] > ans) ans = f[n][i][j];
  ofstream fout("rockers.out");
  fout << ans << endl;
  fout.close();
  return 0;
}
