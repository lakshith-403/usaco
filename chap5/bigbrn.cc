/*
ID: liangyi1
PROG: bigbrn
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <utility>
using namespace std;

int n, t;
int h[1000][1000];

int main() {
  ifstream fin("bigbrn.in");
  fin >> n >> t;
  for (int i = 0; i < t; i++) {
    int row, col;
    fin >> row >> col;
    h[row - 1][col - 1] = 1;
  }

  // Compute the max height from each row.
  for (int i = 0; i < n; i++)
    h[0][i] = 1 - h[0][i];
  for (int i = 1; i < n; i++)
    for (int j = 0; j < n; j++)
      h[i][j] = h[i][j] == 1 ? 0 : h[i - 1][j] + 1;

  // Consider the bottom of square on each row.
  int max_len = 0;  // Max dimension of the square.
  for (int i = 0; i < n; i++) {
    // <int, int> in the stack:
    //  first -- height of the left side.
    //  second -- position of the left side.
    stack< pair<int, int> > s;
    for (int j = 0; j < n; j++) {
      int new_pos = j;
      while (!s.empty()) {
        pair<int, int> top = s.top();
        if (top.first <= h[i][j]) break;
        s.pop();
        new_pos = top.second;
        int len = min(j - top.second, top.first);
        max_len = max(max_len, len);
      }
      s.push(make_pair(h[i][j], new_pos));
    }
    while (!s.empty()) {
      pair<int, int> top = s.top();
      s.pop();
      int len = min(n - top.second, top.first);
      max_len = max(max_len, len);
    }
  }

  ofstream fout("bigbrn.out");
  fout << max_len << endl;
  fout.close();
  return 0;
}
