/*
ID: liangyi1
PROG: skidesign
LANG: C++
*/
#include <climits>
#include <fstream>
#include <iostream>
using namespace std;

int n;
int hill[1000];

void ReadData(ifstream& fin) {
  fin >> n;
  for (int i = 0; i < n; ++i)
    fin >> hill[i];
}

int Solve() {
  int ans = INT_MAX;
  for (int i = 0; i <= 100 - 17; ++i) {
    // Change all hills to [i, i + 17].
    int cost = 0;
    for (int j = 0; j < n; ++j) {
      if (hill[j] < i)
        cost += (i - hill[j]) * (i - hill[j]);
      else if (hill[j] > i + 17)
        cost += (hill[j] - i - 17) * (hill[j] - i - 17);
    }
    if (cost < ans)
      ans = cost;
  }
  return ans;
}

int main() {
  ifstream fin("skidesign.in");
  ofstream fout("skidesign.out");

  ReadData(fin);
  fout << Solve() << endl;

  fin.close();
  fout.close();
  return 0;
}
