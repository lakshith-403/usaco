/*
ID: liangyi1
PROG: hamming
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int n, b, d;
int dis[256][256];
vector<int> words;
bool found = false;

const int pow2[] = {1, 2, 4, 8, 16, 32, 64, 128, 256};

void ComputeDistance() {
  for (int i = 0; i < 256; ++i) {
    for (int j = 0; j < 256; ++j) {
      int x = i, y = j;
      dis[i][j] = 0;
      while (x > 0 || y > 0) {
        dis[i][j] += (x & 1) != (y & 1);
        x >>= 1;
        y >>= 1;
      }
      dis[j][i] = dis[i][j];
    }
  }
}

void Search(int p) {
  if (words.size() == n) {
    found = true;
    return;
  }
  if (p >= pow2[b]) return;
  int i;
  for (i = 0; i < words.size(); ++i) {
    if (dis[p][words[i]] < d) break;
  }
  if (i == words.size()) {
    words.push_back(p);
    Search(p + 1);
    if (found) return;
    words.pop_back();
  }
  Search(p + 1);
}

int main() {
  ifstream fin("hamming.in");
  ofstream fout("hamming.out");
  fin >> n >> b >> d;
  ComputeDistance();
  Search(0);
  for (int i = 0; i < n; ++i) {
    if (i % 10 != 0) fout << ' ';
    fout << words[i];
    if (i % 10 == 9) fout << endl;
  }
  if (n % 10 != 0) fout << endl;
  fin.close();
  fout.close();
  return 0;
}
