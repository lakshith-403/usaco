/*
ID: liangyi1
PROG: wormhole
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

int n;

struct Point {
  int x, y;
} p[12];

// The next point after exiting p[i].
int exit_p[12];

int ans = 0;
int pairing[12];

void ReadData(ifstream& fin) {
  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin >> p[i].x >> p[i].y;
  }
}

void BuildGraph() {
  for (int i = 0; i < n; ++i) {
    exit_p[i] = -1;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (p[i].y == p[j].y && p[i].x < p[j].x) {
        if (exit_p[i] == -1 || p[j].x < p[exit_p[i]].x) {
          exit_p[i] = j;
        }
      }
    }
  }
}

void VerifyPairing() {
  bool visited[12] = {0};
  bool found_cycle = false;

  for (int i = 0; i < n && !found_cycle; ++i) {
    if (visited[i]) continue;
    visited[i] = true;
    int j = i;
    while (true) {
      // Exit p[j] and jump to the next wormhole.
      if (exit_p[j] == -1) break;
      j = pairing[exit_p[j]];
      if (visited[j]) {
        if (j == i) found_cycle = true;
        break;
      } else {
        visited[j] = true;
      }
    }
  }

  if (found_cycle)
    ++ans;
}

void GeneratePair(int i, int num_unpaired) {
  if (i == n) {
    VerifyPairing();
    return;
  }

  // Leave p[i] unpaired.
  if (n - (i + 1) >= num_unpaired + 1) {
    GeneratePair(i + 1, num_unpaired + 1);
  }

  if (num_unpaired > 0) {
    // Pair p[i] with an unpaired point p[j], where j < i.
    for (int j = 0; j < i; ++j) {
      if (pairing[j] == -1) {
        pairing[j] = i;
        pairing[i] = j;
        GeneratePair(i + 1, num_unpaired - 1);
        pairing[j] = pairing[i] = -1;
      }
    }
  }
}

void Solve() {
  for (int i = 0; i < n; ++i)
    pairing[i] = -1;
  // Enuemrate and verify all pairings.
  GeneratePair(0, 0);
}

int main() {
  ifstream fin("wormhole.in");
  ofstream fout("wormhole.out");

  ReadData(fin);
  BuildGraph();
  Solve();
  fout << ans << endl;

  fin.close();
  fout.close();
  return 0;
}
