/*
ID: liangyi1
PROG: milk4
LANG: C++
*/
#include <algorithm>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
using namespace std;

int q, p;
int pail[101];
char f[20001][101][2];
char prev[20001][101][2];
bool found = false;
char solution[100], best_solution[100];

void Search(int i, int q, char p) {
  if (q == 0) {
    found = true;
    memcpy(best_solution, solution, sizeof(best_solution));
    return;
  }
  // Case 1: use current_p once, don't use current_p - 1.
  if (f[q - pail[p]][p - 1][0] + 1 == f[q][p][1] &&
      prev[q - pail[p]][p - 1][0] == prev[q][p][1]) {
    if (!found || best_solution[i] <= p) {
      solution[i] = p;
      Search(i + 1, q - pail[p], prev[q][p][1]);
    }
  }
  // Case 2: use p once and use p - 1.
  if (f[q - pail[p]][p - 1][1] + 1 == f[q][p][1] && prev[q][p][1] == p - 1) {
    if (!found || best_solution[i] <= p) {
      solution[i] = p;
      Search(i + 1, q - pail[p], p - 1);
    }
  }
  // Case 3: use p multiple times.
  if (f[q - pail[p]][p][1] == f[q][p][1] &&
      prev[q - pail[p]][p][1] == prev[q][p][1]) {
    Search(i, q - pail[p], p);
  }
}

int main() {
  ifstream fin("milk4.in");
  fin >> q >> p;
  for (int i = 1; i <= p; i++)
    fin >> pail[i];
  fin.close();
  sort(pail + 1, pail + p + 1, greater<int>());  // Important!

  for (int i = 1; i <= q; i++)
    f[i][0][0] = f[i][0][1] = 101;
  for (int i = 1; i <= p; i++)
    f[0][i][1] = 101;
  for (int i = 1; i <= q; i++) {
    for (int j = 1; j <= p; j++) {
      // f[i][j][0]: mustn't use j.
      f[i][j][0] = 101;
      if (f[i][j - 1][0] < f[i][j][0]) {
        f[i][j][0] = f[i][j - 1][0];
        prev[i][j][0] = prev[i][j - 1][0];  // No chance of using j - 1.
      }
      // Why equal: using j - 1 is always better than not using j - 1.
      if (f[i][j - 1][1] <= f[i][j][0]) {
        f[i][j][0] = f[i][j - 1][1];
        prev[i][j][0] = j - 1;
      }

      // f[i][j][1]: must use j.
      f[i][j][1] = 101;
      if (i < pail[j]) continue;
      // Case 1: use j once, but not use j - 1.
      if (f[i - pail[j]][j - 1][0] + 1 < f[i][j][1]) {
        f[i][j][1] = f[i - pail[j]][j - 1][0] + 1;
        prev[i][j][1] = prev[i - pail[j]][j - 1][0];
      }
      // Case 2: use j once, and also use j - 1.
      // Why equal: using j - 1 is always better than not using j - 1.
      if (f[i - pail[j]][j - 1][1] + 1 <= f[i][j][1]) {
        f[i][j][1] = f[i - pail[j]][j - 1][1] + 1;
        prev[i][j][1] = j - 1;
      }
      // Case 3: use j more than once.
      // In the equal case, choose the lager prev.
      if (f[i - pail[j]][j][1] < f[i][j][1] || f[i - pail[j]][j][1] ==
          f[i][j][1] && prev[i - pail[j]][j][1] > prev[i][j][1]) {
        f[i][j][1] = f[i - pail[j]][j][1];
        prev[i][j][1] = prev[i - pail[j]][j][1];
      }
    }
  }

  // Search for the best solution.
  int ans = 101;
  char current_p;
  for (char i = p; i > 0; i--)
    if (f[q][i][1] < ans) {
      ans = f[q][i][1];
      current_p = i;
    }
  Search(0, q, current_p);

  ofstream fout("milk4.out");
  fout << ans;
  for (int i = 0; i < ans; i++)
    fout << ' ' << pail[best_solution[i]];
  fout << endl;
  fout.close();
  return 0;
}
