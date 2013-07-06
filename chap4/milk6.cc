/*
ID: liangyi1
PROG: milk6
LANG: C++
*/
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n, m;
double min_cost, min_truck;

struct Route {
  int s, e;
  int cost;
} r[1000];

double cap[33][33];

double MaxFlow() {
  // Load the capacities.
  memset(cap, 0, sizeof(cap));
  for (int i = 0; i < m; i++)
    cap[r[i].s][r[i].e] += r[i].cost;

  double total = 0;
  int prev[33];
  double flow[33];
  bool visit[33];
  while (true) {
    memset(flow, 0, sizeof(flow));
    flow[1] = 1e20;
    memset(visit, 0, sizeof(visit));
    while (true) {
      double max_flow = 0;
      int choice = -1;
      for (int i = 1; i <= n; i++) {
        if (!visit[i] && flow[i] > max_flow) {
          max_flow = flow[i];
          choice = i;
        }
      }
      if (choice == -1 || choice == n) break;
      visit[choice] = true;
      // Update the neighbors' flow value.
      for (int i = 1; i <= n; i++) {
        if (flow[i] < min(max_flow, cap[choice][i])) {
          prev[i] = choice;
          flow[i] = min(max_flow, cap[choice][i]);
        }
      }
    }

    if (flow[n] == 0) break;
    total += flow[n];
    // Update the capacities on the augmenting path.
    int i = n;
    while (i != 1) {
      int j = prev[i];
      cap[j][i] -= flow[n];
      cap[i][j] += flow[n];
      i = j;
    }
  }
  return total;
}

void GetCurrentCut(vector<int>* p_cut) {
  bool visit[33] = {0};
  queue<int> q;
  q.push(1);
  while (!q.empty()) {
    int head = q.front();
    q.pop();
    visit[head] = true;
    for (int i = 1; i <= n; i++) {
      if (!visit[i] && cap[head][i] > 0)
        q.push(i);
    }
  }
  p_cut->clear();
  for (int i = 0; i < m; i++) {
    if (visit[r[i].s] && !visit[r[i].e])
      p_cut->push_back(i);
  }
  sort(p_cut->begin(), p_cut->end());
}

int main() {
  ifstream fin("milk6.in");
  fin >> n >> m;
  for (int i = 0; i < m; i++)
    fin >> r[i].s >> r[i].e >> r[i].cost;
  fin.close();

  // cost = 1000 * cost + i
  for (int i = 0; i < m; i++)
    r[i].cost = r[i].cost * 1001 + 1;
  double max_flow = MaxFlow();
  min_cost = floor(max_flow / 1001);
  min_truck = max_flow - min_cost * 1001;

  // Get the first min-cut.
  bool need[1000] = {0};
  bool update = true;
  vector<int> cut, new_cut;
  GetCurrentCut(&cut);
  do {
    update = false;
    // Increase the arc capacity, in decreasing index order.
    for (int i = min_truck - 1; i >= 0; i--) {
      if (need[cut[i]]) continue;
      r[cut[i]].cost += 1;
      if (MaxFlow() != max_flow) {
        r[cut[i]].cost -= 1;
        need[cut[i]] = true;
        continue;
      }
      // The arc can be replaced by other ones.
      GetCurrentCut(&new_cut);
      if (new_cut < cut) {
        cut = new_cut;
        update = true;
      }
    }
  } while (update);

  ofstream fout("milk6.out");
  fout << static_cast<int>(min_cost) << ' ' << static_cast<int>(min_truck)
       << endl;
  for (int i = 0; i < cut.size(); i++) {
    fout << cut[i] + 1 << '\n';
  }
  fout.close();
  return 0;
}
