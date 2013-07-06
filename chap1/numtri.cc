/*
ID: liangyi1
PROG: numtri
LANG: C++
*/
#include <fstream>
#include <iostream>
using namespace std;

int r;
int num[1000][1000];

int main() {
  ifstream fin("numtri.in");
  ofstream fout("numtri.out");
  fin >> r;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < i + 1; j++) {
      fin >> num[i][j];
    }
  }
  for (int i = 1; i < r; i++) {
    num[i][0] += num[i - 1][0];
    num[i][i] += num[i - 1][i - 1];
    for (int j = 1; j < i; j++) {
      num[i][j] += max(num[i - 1][j - 1], num[i - 1][j]);
    }
  }
  int ans = 0;
  for (int i = 0; i < r; i++) {
    if (num[r - 1][i] > ans) {
      ans = num[r - 1][i];
    }
  }
  fout << ans << endl;
  fin.close();
  fout.close();
  return 0;
}
