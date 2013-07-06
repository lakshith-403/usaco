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
bool conn[100][100];
int f[100][100];

int main() {
  ifstream fin("tour.in");
  fin >> n >> v;
  map<string, int> ids;
  for (int i = 0; i < n; i++) {
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
  f[0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      for (int k = 0; k < j; k++)
        if (conn[k][j] && f[i][k] > 0 && f[i][k] + 1 > f[i][j])
          f[i][j] = f[i][k] + 1;
      f[j][i] = f[i][j];
    }
  }

  // Find optimal.
  int ans = 1;
  for (int i = 0; i < n; i++) {
    if (conn[i][n - 1] && f[i][n - 1] > ans)
      ans = f[i][n - 1];
  }

  ofstream fout("tour.out");
  fout << ans << endl;
  fout.close();
  return 0;
}
