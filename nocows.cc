/*
ID: liangyi1
PROG: nocows
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

int main() {
  ifstream fin("nocows.in");
  ofstream fout("nocows.out");
  int n, k;
  int count[200][100];
  fin >> n >> k;
  // Initialization.
  memset(count, 0, sizeof(count));
  count[1][1] = 1;
  // Calculation.
  for (int nodes = 2; nodes <= n; ++nodes) {
    for (int height = 2; height <= k; ++height) {
      // Enumerate the number of nodes of the left subtree.
      for (int left_nodes = 1; left_nodes < nodes - 1; ++left_nodes) {
        int right_nodes = nodes - 1 - left_nodes;

        // Case 1: left_height < height - 1, right_height == height - 1.
        int right_height = height - 1;
        for (int left_height = 1; left_height < height - 1; ++left_height) {
          if (count[left_nodes][left_height] == 0) continue;
          if (count[right_nodes][right_height] == 0) continue;
          count[nodes][height] += count[left_nodes][left_height] *
            count[right_nodes][right_height];
          count[nodes][height] %= 9901;
        }

        // Case 2: left_height == height - 1, right_height < height.
        int left_height = height - 1;
        if (count[left_nodes][left_height] == 0) continue;
        for (int right_height = 1; right_height < height; ++right_height) {
          if (count[right_nodes][right_height] == 0) continue;
          count[nodes][height] += count[left_nodes][left_height] *
            count[right_nodes][right_height];
          count[nodes][height] %= 9901;
        }
      }
    }
  }
  fout << count[n][k] << endl;
  fin.close();
  fout.close();
  return 0;
}
