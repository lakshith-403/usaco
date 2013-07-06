/*
ID: liangyi1
PROG: humble
LANG: C++
*/
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

int k, n;
int fac[100], next_mate[100];
int humble[100001];

int int_compare(const void* e1, const void* e2) {
  return *(int *)e1 - *(int *)e2;
}

int main() {
  ifstream fin("humble.in");
  ofstream fout("humble.out");
  fin >> k >> n;
  for (int i = 0; i < k; ++i) {
    fin >> fac[i];
  }
  qsort(fac, k, sizeof(int), int_compare);

  // Quite a magic!
  humble[0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < k; ++j) {
      while (fac[j] * humble[next_mate[j]] <= humble[i - 1]) {
        ++next_mate[j];
      }
    }
    int best = fac[0] * humble[next_mate[0]];
    int choice = 0;
    for (int j = 1; j < k; ++j) {
      if (fac[j] * humble[next_mate[j]] < best) {
        best = fac[j] * humble[next_mate[j]];
        choice = j;
      }
    }
    humble[i] = best;
  }
  fout << humble[n] << endl;

  fin.close();
  fout.close();
  return 0;
}
