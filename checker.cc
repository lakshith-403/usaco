/*
ID: liangyi1
LANG: C++
TASK: checker
*/
#include <fstream>
#include <iostream>
using namespace std;

ifstream fin("checker.in");
ofstream fout("checker.out");
int n, num_solutions;
int pos[13];
bool col[13], diag1[25], diag2[25];

void Search(int r) {
  if (r == n) {
    if (num_solutions < 3) {
      fout << pos[0] + 1;
      for (int i = 1; i < n; i++) {
        fout << ' ' << pos[i] + 1;
      }
      fout << endl;
    }
    num_solutions++;
  } else {
    for (int i = 0; i < n; i++) {
      if (col[i] || diag1[r + n - i - 1] || diag2[r + i]) continue;
      col[i] = true;
      diag1[r + n - i - 1] = true;
      diag2[r + i] = true;
      pos[r] = i;
      Search(r + 1);
      col[i] = false;
      diag1[r + n - i - 1] = false;
      diag2[r + i] = false;
    }
  }
}

int main() {
  fin >> n;
  Search(0);
  fout << num_solutions << endl;
  fin.close();
  fout.close();
  return 0;
}
