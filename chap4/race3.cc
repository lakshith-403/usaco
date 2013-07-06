/*
ID: liangyi1
PROG: race3
LANG: C++
*/
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n, next_label;
bool g[50][50];
vector<int> ans1, ans2;

bool Unavoidable(int x) {
  // Perform a BFS without x.
  queue<int> q;
  bool visit[50];
  memset(visit, 0, sizeof(visit));
  q.push(0);
  while (!q.empty()) {
    int head = q.front();
    q.pop();
    visit[head] = true;
    for (int i = 0; i < n; i++) {
      if (i != x && !visit[i] && g[head][i])
        q.push(i);
    }
  }
  return !visit[n - 1];
}

bool IsSplitting(int x) {
  queue<int> q;
  int label[50];

  // Color the nodes up to x as '1'.
  memset(label, 0, sizeof(label));
  q.push(0);
  while (!q.empty()) {
    int head = q.front();
    q.pop();
    label[head] = 1;
    if (head == x) continue;
    for (int i = 0; i < n; i++) {
      if (label[i] == 0 && g[head][i])
        q.push(i);
    }
  }

  // No look back from x.
  for (int i = 0; i < n; i++) {
    if (i != x && g[x][i]) {
      if (label[i] == 1)
        return false;
      else
        q.push(i);
    }
  }

  // Color the rest nodes as '2'. Disallow '2' -> '1'.
  while (!q.empty()) {
    int head = q.front();
    q.pop();
    label[head] = 2;
    for (int i = 0; i < n; i++) {
      if (label[i] == 0 && g[head][i]) {
        q.push(i);
      } else if (i != x && label[head] == 2 && g[head][i] && label[i] == 1) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  ifstream fin("race3.in");
  int x;
  while (true) {
    while (true) {
      fin >> x;
      if (x < 0) break;
      g[n][x] = true;
    }
    if (x == -1) break;
    n++;
  }
  fin.close();

  // Compute the unavoidable points.
  for (int i = 1; i < n - 1; i++) {
    if (Unavoidable(i)) ans1.push_back(i);
  }

  // Compute the splitting points.
  for (int i = 0; i < ans1.size(); i++) {
    if (IsSplitting(ans1[i])) ans2.push_back(ans1[i]);
  }

  ofstream fout("race3.out");
  fout << ans1.size();
  for (int i = 0; i < ans1.size(); i++) fout << ' ' << ans1[i];
  fout << endl;
  sort(ans2.begin(), ans2.end());
  fout << ans2.size();
  for (int i = 0; i < ans2.size(); i++) fout << ' ' << ans2[i];
  fout << endl;
  fout.close();
  return 0;
}
