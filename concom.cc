/*
ID: liangyi1
PROG: concom
LANG: C++
*/

#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>
#include <utility>
using namespace std;

int control[101][101];
int own[101][101];

int main() {
  ifstream fin("concom.in");
  ofstream fout("concom.out");
  // Initialize control and share.
  memset(control, 0, sizeof(control));
  memset(own, 0, sizeof(own));
  for (int i = 1; i <= 100; ++i) {
    control[i][i] = 100;
    own[i][i] = 100;
  }
  // Read the share and initialize the queue.
  int n;
  queue<pair<int, int> > q;
  fin >> n;
  for (int i = 0; i < n; ++i) {
    int x, y, p;
    fin >> x >> y >> p;
    own[x][y] = control[x][y] = p;
    if (p > 50) {
      q.push(make_pair(x, y));
    }
  }
  // Propaganda the controlling relations.
  while (!q.empty()) {
    pair<int, int> head = q.front();
    int x = head.first;
    int y = head.second;
    q.pop();
    // Update the controlling amounts.
    for (int i = 1; i <= 100; ++i) {
      if (control[i][x] > 50 && control[i][y] <= 50) {
        control[i][y] += own[x][y];
        if (control[i][y] > 50) {
          q.push(make_pair(i, y));
        }
      }
    }
    for (int i = 1; i <= 100; ++i) {
      if (control[x][i] <= 50) {
        control[x][i] += own[y][i];
        if (control[x][i] > 50) {
          q.push(make_pair(x, i));
        }
      }
    }
  }
  // Output the relations.
  for (int i = 1; i <= 100; ++i) {
    for (int j = 1; j <= 100; ++j) {
      if (i != j && control[i][j] > 50) fout << i << ' ' << j << endl;
    }
  }
  fin.close();
  fout.close();
  return 0;
}
