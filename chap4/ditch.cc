/*
ID: liangyi1
PROG: ditch
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

int n, m, sink;
int cap[401][401];

int MaxFlow() {
  // Initialize.
  int total = 0;
  int prev_node[401];
  int flow[401];
  bool visit[401];
  while (true) {
    // Find the path with highest capacity from source to sink, by a modified
    // dijkstra's algorithm.
    memset(prev_node, 0, sizeof(prev_node));
    memset(flow, 0, sizeof(flow));
    memset(visit, 0, sizeof(visit));
    flow[1] = 10000000;
    while (true) {
      // Find the unvisited node with the highest capacity to it.
      int max_flow = 0;
      int max_node = -1;
      for (int i = 1; i <= m; ++i) {
        if (!visit[i] && flow[i] > max_flow) {
          max_flow = flow[i];
          max_node = i;
        }
      }
      if (max_node == -1 || max_node == sink) break;
      visit[max_node] = true;
      // Update its neighbors.
      for (int i = 1; i <= m; ++i) {
        if (flow[i] < min(max_flow, cap[max_node][i])) {
          prev_node[i] = max_node;
          flow[i] = min(max_flow, cap[max_node][i]);
        }
      }
    }
    if (flow[sink] == 0) break;  // Break if no path.
    total += flow[sink];
    // Update the capacity with the new flow added.
    int i = sink;
    while (i != 1) {
      int j = prev_node[i];
      cap[j][i] -= flow[sink];
      cap[i][j] += flow[sink];
      i = j;
    }
  }
  return total;
}

int main() {
  ifstream fin("ditch.in");
  fin >> n >> m;
  sink = m;
  for (int i = 0; i < n; ++i) {
    int s, e, c;
    fin >> s >> e >> c;
    if (cap[s][e] == 0 && cap[e][s] == 0) {
      cap[s][e] = c;
    } else {
      // Add a new node for the parallel edge.
      ++m;
      cap[s][m] = cap[m][e] = c;
    }
  }
  fin.close();

  ofstream fout("ditch.out");
  fout << MaxFlow() << endl;
  fout.close();
  return 0;
}
