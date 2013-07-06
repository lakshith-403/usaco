/*
ID: liangyi1
PROG: sort3
LANG: C++
*/
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ifstream fin("sort3.in");
  ofstream fout("sort3.out");
  int n;
  int count[3] = {0};
  int at[3][3] = {0};
  fin >> n;
  vector<int> numbers(n);
  for (int i = 0; i < n; i++) {
    fin >> numbers[i];
    --numbers[i];
    ++count[numbers[i]];
  }
  // Count the six types.
  for (int i = 0; i < n; i++) {
    if (i < count[0]) {
      ++at[numbers[i]][0];
    } else if (i < count[0] + count[1]) {
      ++at[numbers[i]][1];
    } else {
      ++at[numbers[i]][2];
    }
  }
  int ans = min(at[0][1], at[1][0]) + min(at[0][2], at[2][0]) + min(at[1][2],
      at[2][1]) + 2 * abs(at[0][1] - at[1][0]);
  fout << ans << endl;
  fin.close();
  fout.close();
  return 0;
}
