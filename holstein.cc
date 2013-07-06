/*
ID: liangyi1
PROG: holstein
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

int v;
int min_v[25];
int g;
int v_amount[15][25];
int ans = 16;
bool used[15], best_used[15];
int current_v[25];

void Search(int feed, int total) {
  // Check for requirement.
  bool lack = false;
  for (int i = 0; i < v; ++i) {
    if (current_v[i] < min_v[i]) {
      lack = true;
      break;
    }
  }
  // Requirement satisfied.
  if (!lack) {
    ans = total;
    memcpy(best_used, used, sizeof(best_used));
    return;
  }
  // Impossible to be a best solution.
  if (feed == g || total + 1 == ans) {
    return;
  }
  // Use it.
  for (int i = 0; i < v; ++i) {
    current_v[i] += v_amount[feed][i];
  }
  used[feed] = true;
  Search(feed + 1, total + 1);
  // Don't use it.
  for (int i = 0; i < v; ++i) {
    current_v[i] -= v_amount[feed][i];
  }
  used[feed] = false;
  Search(feed + 1, total);
}

int main() {
  ifstream fin("holstein.in");
  ofstream fout("holstein.out");
  fin >> v;
  for (int i = 0; i < v; ++i) {
    fin >> min_v[i];
  }
  fin >> g;
  for (int i = 0; i < g; ++i) {
    for (int j = 0; j < v; ++j) {
      fin >> v_amount[i][j];
    }
  }
  Search(0, 0);
  fout << ans;
  for (int i = 0; i < g; ++i) {
    if (best_used[i]) {
      fout << ' ' << i + 1;
    }
  }
  fout << endl;
  fin.close();
  fout.close();
  return 0;
}
