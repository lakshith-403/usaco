/*
ID: liangyi1
PROG: latin
LANG: C++
*/
#include <stdint.h>
#include <fstream>
using namespace std;

int n, ans;
char num[7][7];
bool col[7][7];
const int64_t fact[] = {1, 1, 2, 6, 24, 120, 12198297600};

inline void Swap(char* a, char* b) {
  char temp = *a;
  *a = *b;
  *b = temp;
}

void Search(int r, int c) {
  if (r == n - 1) {
    ans++;
    return;
  }
  for (int i = c; i < n; i++) {
    if (col[c][num[r][i]]) continue;
    col[c][num[r][i]] = true;
    Swap(&num[r][c], &num[r][i]);
    if (c < n - 1)
      Search(r, c + 1);
    else {
      Search(r + 1, 1);
    }
    // Backtracking.
    Swap(&num[r][c], &num[r][i]);
    col[c][num[r][i]] = false;
  }
}

int main() {
  ifstream fin("latin.in");
  fin >> n;
  fin.close();

  for (int i = 0; i < n; i++)
    col[i][i] = true;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < n; j++) num[i][j] = j;
    num[i][0] = i;
    num[i][i] = 0;
  }
  if (n < 7)
    Search(1, 1);
  else
    ans = 1;

  ofstream fout("latin.out");
  fout << ans * fact[n - 1] << endl;
  fout.close();
  return 0;
}
