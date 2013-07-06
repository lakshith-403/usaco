/*
ID: liangyi1
PROG: schlnet
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int n;
int num[101];
int g[101][101];

int Task1() {
  int color = 0;
  int c[101] = {0};
  for (int i = 1; i <= n; i++) {
    if (c[i]) continue;
    c[i] = ++color;
    queue<int> q;
    q.push(i);
    bool visit[101] = {0};
    visit[i] = true;
    while (!q.empty()) {
      int h = q.front();
      q.pop();
      for (int j = 0; j < num[h]; j++) {
        if (!visit[g[h][j]]) {
          visit[g[h][j]] = true;
          c[g[h][j]] = color;
          q.push(g[h][j]);
        }
      }
    }
  }
  int ret = 0;
  bool use_c[101] = {0};
  for (int i = 1; i <= n; i++)
    use_c[c[i]] = true;
  for (int i = 1; i <= n; i++)
    ret += use_c[i];
  return ret;
}

int num_comp;  // Number of components.
int comp_id[101];
int id;
int order[101];  // DFS order.
stack<int> s;

int DFS(int node) {
  int low = order[node] = ++id;
  s.push(node);
  for (int i = 0; i < num[node]; i++) {
    if (!order[g[node][i]]) {
      int sub_low = DFS(g[node][i]);
      if (sub_low < low) low = sub_low;
    } else if (!comp_id[g[node][i]]) {
      if (order[g[node][i]] < low) low = order[g[node][i]];
    }
  }
  // Is it the end of a component?
  if (low == order[node]) {
    num_comp++;
    // Mark all nodes in the component.
    int out;
    do {
      out = s.top();
      s.pop();
      comp_id[out] = num_comp;
    } while (out != node);
  }
  return low;
}

int Task2() {
  for (int i = 1; i <= n; i++)
    if (!order[i]) {
      DFS(i);
    }
  bool has_in[101] = {0}, has_out[101] = {0};
  for (int i = 1; i <= n; i++)
    for (int j = 0; j < num[i]; j++)
      if (comp_id[i] != comp_id[g[i][j]]) {
        has_in[comp_id[g[i][j]]] = true;
        has_out[comp_id[i]] = true;
      }
  int root, leaf, both;
  root = leaf = both = 0;
  for (int i = 1; i <= num_comp; i++) {
    if (!has_in[i] && !has_out[i])
      both++;
    else if (!has_in[i])
      root++;
    else if (!has_out[i])
      leaf++;
  }
  if (leaf == 0 && root == 0 && both == 1)
    return 0;
  else
    return max(leaf + both, root + both);
}

int main() {
  ifstream fin("schlnet.in");
  fin >> n;
  for (int i = 1; i <= n; i++) {
    int r;
    for (fin >> r; r != 0; fin >> r)
      g[i][num[i]++] = r;
  }
  fin.close();

  ofstream fout("schlnet.out");
  // Task 1: graph coloring.
  fout << Task1() << endl;
  // Task 2: find the strongly-connected components.
  fout << Task2() << endl;
  fout.close();
  return 0;
}
