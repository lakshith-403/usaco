/*
ID: liangyi1
PROG: stall4
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <vector>
using namespace std;

int n, m;
// vertex 0: source, vertex 1..n: cows, vertex n+1 ... n+m: stalls,
// vertex n+m+1: sink.
vector<int> g[402];
bool cap[402][402];
bool visit[402];
int prev[402];

bool DFS(int v) {
  if (v == n + m + 1) return true;
  visit[v] = true;
  for (vector<int>::const_iterator i = g[v].begin(); i != g[v].end(); ++i) {
    if (!visit[*i] && cap[v][*i]) {
      prev[*i] = v;
      if (DFS(*i)) return true;
    }
  }
  return false;
}

int MaxFlow() {
  int total = 0;
  while (true) {
    // Use DFS to find an augmenting path.
    memset(visit, 0, sizeof(visit));
    if (!DFS(0)) break;
    ++total;
    // Adjust the graph.
    int i = n + m + 1;
    while (i != 0) {
      int j = prev[i];
      cap[j][i] = false;
      cap[i][j] = true;
      i = j;
    }
  }
  return total;
}

int main() {
  ifstream fin("stall4.in");
  fin >> n >> m;
  // Connect source and sink.
  for (int i = 1; i <= n; ++i) {
    g[0].push_back(i);
    cap[0][i] = true;
  }
  for (int i = 1; i <= m; ++i) {
    g[n + i].push_back(n + m + 1);
    cap[n + i][n + m + 1] = true;
  }
  for (int i = 1; i <= n; ++i) {
    int num;
    fin >> num;
    for (; num > 0; --num) {
      int s;
      fin >> s;
      g[i].push_back(n + s);
      g[n + s].push_back(i);
      cap[i][n + s] = true;
    }
  }
  fin.close();

  // Compute the max-flow.
  ofstream fout("stall4.out");
  fout << MaxFlow() << endl;
  fout.close();
  return 0;
}
