/*
ID: liangyi1
PROG: money
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

int main() {
  ifstream fin("money.in");
  ofstream fout("money.out");
  int v, n;
  int coin_value[25];
  long long num_ways[25][10001];
  fin >> v >> n;
  for (int i = 0; i < v; ++i) {
    fin >> coin_value[i];
  }
  memset(num_ways, 0, sizeof(num_ways));
  // For the first value.
  for (int i = 0; i <= n; i += coin_value[0]) {
    num_ways[0][i] = 1;
  }
  for (int i = 1; i < v; ++i) {
    for (int j = 0; j <= n; ++j) {
      num_ways[i][j] = num_ways[i - 1][j];
      if (j >= coin_value[i]) {
        num_ways[i][j] += num_ways[i][j - coin_value[i]];
      }
    }
  }
  fout << num_ways[v - 1][n] << endl;
  fin.close();
  fout.close();
  return 0;
}
