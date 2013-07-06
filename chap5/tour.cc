/*
ID: liangyi1
PROG: tour
LANG: C++
*/
#include <fstream>
#include <map>
#include <string>
using namespace std;

int n, v;
bool conn[101][101];
int f[101][101];

int main() {
  ifstream fin("tour.in");
  fin >> n >> v;
  map<string, int> ids;
  for (int i = 1; i <= n; i++) {
    string s;
    fin >> s;
    ids.insert(make_pair(s, i));
  }
  for (int i = 0; i < v; i++) {
    string s1, s2;
    fin >> s1 >> s2;
    int from = ids.find(s1)->second;
    int to = ids.find(s2)->second;
    conn[from][to] = conn[to][from] = true;
  }
  fin.close();

  // Dynamic programming.
  f[1][1] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (f[i][j] == 0) continue;
      for (int k = max(i, j) + 1; k <= n; k++) {
        if (conn[i][k] && f[i][j] + 1 > f[k][j]) f[k][j] = f[i][j] + 1;
        if (conn[j][k] && f[i][j] + 1 > f[i][k]) f[i][k] = f[i][j] + 1;
      }
    }
  }

  // Find the optimal.
  int ans = 1;
  for (int i = 1; i < n; i++) {
    if (conn[i][n] && f[i][n] > ans) ans = f[i][n];
  }

  ofstream fout("tour.out");
  fout << ans << endl;
  fout.close();
  return 0;
}
