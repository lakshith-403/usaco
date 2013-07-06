/*
ID: liangyi1
LANG: C++
TASK: barn1
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
  ifstream fin("barn1.in");
  ofstream fout("barn1.out");
  int m, s, c;
  vector<int> cows;
  fin >> m >> s >> c;
  for (int i = 0; i < c; i++) {
    int pos;
    fin >> pos;
    cows.push_back(pos);
  }
  if (m >= c) {
    fout << c << endl;
  } else {
    sort(cows.begin(), cows.end());
    // Greedy: pick the m - 1 largest holes.
    vector<int> holes;
    for (int i = 1; i < cows.size(); i++) {
      holes.push_back(cows[i] - cows[i - 1] - 1);
    }
    sort(holes.begin(), holes.end(), std::greater<int>());
    int ans = cows[cows.size() - 1] - cows[0] + 1;
    for (int i = 0; i < m - 1; i++) {
      ans -= holes[i];
    }
    fout << ans << endl;
  }
  fin.close();
  fout.close();
  return 0;
}
