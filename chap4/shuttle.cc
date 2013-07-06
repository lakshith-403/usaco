/*
ID: liangyi1
PROG: shuttle
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int n, cost_limit, next_cost_limit, total_states;
char state[25];
vector<char> steps;
ofstream fout;

int MinRemainingSteps() {
  int ret = 0;
  int dest = 0;
  for (int i = 0; i < n + n + 1; i++) {
    if (state[i] == 2) {
      ret += (i - dest + 1) / 2;
      dest++;
    }
  }
  dest = n + n;
  for (int i = n + n; i >= 0; i--) {
    if (state[i] == 1) {
      ret += (dest - i + 1) / 2;
      dest--;
    }
  }
  return ret;
}

bool IsGoal() {
  if (state[n] != 0) return false;
  for (int i = 0; i < n; i++)
    if (state[i] != 2) return false;
  for (int i = n + 1; i < n + n + 1; i++)
    if (state[i] != 1) return false;
  return true;
}

void Output() {
  bool newline = true;
  for (int i = 0; i < steps.size(); i++) {
    if (newline)
      newline = false;
    else
      fout << ' ';
    fout << static_cast<int>(steps[i]);
    if (i % 20 == 19) {
      newline = true;
      fout << endl;
    }
  }
  if (steps.size() % 20 != 0) fout << endl;
}

bool Search(int prev_hole, int hole, int cost) {
  total_states++;
  int total_cost = cost + MinRemainingSteps();
  if (total_cost > cost_limit) {
    next_cost_limit = min(next_cost_limit, total_cost);
    return false;
  } else if (total_cost == cost_limit) {
    if (IsGoal()) {
      Output();
      return true;
    }
  }
  for (int i = max(hole - 2, 0); i <= min(hole + 2, n + n); i++) {
    if (i == hole || i == prev_hole) continue;
    if (i < hole && state[i] == 2) continue;
    if (i > hole && state[i] == 1) continue;
    state[hole] = state[i];
    state[i] = 0;
    steps.push_back(i + 1);
    if (Search(hole, i, cost + 1)) return true;
    steps.pop_back();
    state[i] = state[hole];
    state[hole] = 0;
  }
  return false;
}

int main() {
  ifstream fin("shuttle.in");
  fin >> n;
  fin.close();

  // Iterative deepening A*.
  fout.open("shuttle.out");
  for (int i = 0; i < n; i++)
    state[i] = 1;
  for (int i = n + 1; i < 2 * n + 1; i++)
    state[i] = 2;
  next_cost_limit = MinRemainingSteps();
  bool ret;
  do {
    cost_limit = next_cost_limit;
    next_cost_limit = 1000000;
    steps.clear();
    total_states = 0;
    ret = (Search(-1, n, 0));
  } while (!ret);
  fout.close();
  return 0;
}
