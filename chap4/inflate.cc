/*
ID: liangyi1
TASK: inflate
LANG: C++
*/
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int m, n, min_len = 10000;
int len[10001];
int point[10001];
int f[10001];

void ReadData(ifstream& fin) {
  fin >> m >> n;
  for (int i = 0; i < n; ++i) {
    fin >> point[i] >> len[i];
    if (len[i] < min_len) {
      min_len = len[i];
    }
  }
}

int Main() {
  int i;
  int best = 0;
  int counter = 0;
  for (i = 0; i <= m - min_len; ++i) {
    if (i > 0 && f[i] == 0) continue;
    ++counter;
    if (f[i] > best) best = f[i];
    for (int j = 0; j < n; ++j) {
      int new_len = i + len[j];
      if (new_len <= m && f[i] + point[j] > f[new_len]) {
        f[new_len] = f[i] + point[j];
      }
    }
  }
  cout << min_len << endl;
  cout << counter << endl;
  while (i <= m) {
    if (f[i] > best) best = f[i];
    ++i;
  }
  return best;
}

int main() {
  ifstream fin("inflate.in");
  ofstream fout("inflate.out");
  ReadData(fin);
  fout << Main() << endl;
  fin.close();
  fout.close();
  return 0;
}
