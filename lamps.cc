/*
ID: liangyi1
PROG: lamps
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

vector<string> states;
vector<int> on, off;

void GetState(int n, int x) {
  string state(n, '1');
  if (x & 1) {
    // Change all.
    for (int i = 0; i < n; ++i) {
      state[i] = state[i] == '0' ? '1' : '0';
    }
  }
  if (x & 2) {
    // Change odd.
    for (int i = 0; i < n; i += 2) {
      state[i] = state[i] == '0' ? '1' : '0';
    }
  }
  if (x & 4) {
    // Change even.
    for (int i = 1; i < n; i += 2) {
      state[i] = state[i] == '0' ? '1' : '0';
    }
  }
  if (x & 8) {
    // Change 3k + 1.
    for (int i = 0; i < n; i += 3) {
      state[i] = state[i] == '0' ? '1' : '0';
    }
  }
  // Check if it fulfils the on, off requirement.
  for (int i = 0; i < on.size(); ++i) {
    if (state[on[i] - 1] != '1') return;
  }
  for (int i = 0; i < off.size(); ++i) {
    if (state[off[i] - 1] != '0') return;
  }
  states.push_back(state);
}

int main() {
  ifstream fin("lamps.in");
  ofstream fout("lamps.out");
  int n, c;
  fin >> n >> c;
  int x;
  while (1) {
    fin >> x;
    if (x != -1) {
      on.push_back(x);
    } else {
      break;
    }
  }
  while (1) {
    fin>> x;
    if (x != -1) {
      off.push_back(x);
    } else {
      break;
    }
  }
  for (int i = 0; i < 16; ++i) {
    int x = i, num_ones = 0;
    while (x > 0) {
      num_ones += (x & 1);
      x >>= 1;
    }
    if (num_ones > c || (c - num_ones) % 2 != 0) continue;
    GetState(n, i);
  }
  sort(states.begin(), states.end());
  vector<string>::iterator it = unique(states.begin(), states.end());
  for (vector<string>::iterator i = states.begin(); i != it; ++i) {
    fout << *i << endl;
  }
  if (states.begin() == it) {
    fout << "IMPOSSIBLE" << endl;
  }
  fin.close();
  fout.close();
  return 0;
}
