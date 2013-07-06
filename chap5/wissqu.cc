/*
ID: liangyi1
PROG: wissqu
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

int ans = 0;
char pas[16], target[16];
char num[16][5];  // num[i][j] number of herd j around position i
char rest[5] = {3, 3, 3, 3, 3};
bool replaced[16];
bool found = false;
char solution[16][2], saved[16][2];

const char num_adj[16] = {3, 5, 5, 3, 5, 8, 8, 5, 5, 8, 8, 5, 3, 5, 5, 3};
const char adj[16][8] = {
  {1, 4, 5},
  {0, 2, 4, 5, 6},
  {1, 3, 5, 6, 7},
  {2, 6, 7},
  {0, 1, 5, 8, 9},
  {0, 1, 2, 4, 6, 8, 9, 10},
  {1, 2, 3, 5, 7, 9, 10, 11},
  {2, 3, 6, 10, 11},
  {4, 5, 9, 12, 13},
  {4, 5, 6, 8, 10, 12, 13, 14},
  {5, 6, 7, 9, 11, 13, 14, 15},
  {6, 7, 10, 14, 15},
  {8, 9, 13},
  {8, 9, 10, 12, 14},
  {9, 10, 11, 13, 15},
  {10, 11, 14}
};

void Search(int total) {
  if (total == 16) {
    if (!found) {
      memcpy(target, pas, sizeof(target));
      memcpy(saved, solution, sizeof(saved));
      found = true;
    }
    ans++;
    return;
  }
  for (int i = 0; i < 5; i++) {
    if (rest[i] == 0) continue;
    rest[i]--;
    for (int j = 0; j < 16; j++) {
      if (replaced[j] || pas[j] == i || num[j][i] > 0) continue;
      if (found && target[j] != i) continue;
      replaced[j] = true;
      char prev = pas[j];
      pas[j] = i;
      for (int k = 0; k < num_adj[j]; k++) {
        num[adj[j][k]][prev]--;
        num[adj[j][k]][i]++;
      }
      solution[total][0] = i;
      solution[total][1] = j;
      Search(total + 1);
      // Backtracking.
      pas[j] = prev;
      for (int k = 0; k < num_adj[j]; k++) {
        num[adj[j][k]][i]--;
        num[adj[j][k]][prev]++;
      }
      replaced[j] = false;
    }
    rest[i]++;
  }
}

int main() {
  ifstream fin("wissqu.in");
  for (int i = 0; i < 16; i++) {
    char c;
    fin >> c;
    pas[i] = c - 'A';
  }
  fin.close();

  // Try the first D.
  for (int i = 0; i < 16; i++) {
    bool has_d = false;
    for (int j = 0; j < num_adj[i]; j++)
      if (pas[adj[i][j]] == 3) {
        has_d = true;
        break;
      }
    if (has_d) continue;
    char prev = pas[i];
    pas[i] = 3;  // Put the first D.
    solution[0][0] = 3;
    solution[0][1] = i;
    // Initialize for search.
    memset(num, 0, sizeof(num));
    for (int j = 0; j < 16; j++)
      for (int k = 0; k < num_adj[j]; k++)
        num[adj[j][k]][pas[j]]++;
    memset(replaced, 0, sizeof(replaced));
    replaced[i] = true;
    Search(1);
    pas[i] = prev;
  }

  ofstream fout("wissqu.out");
  for (int i = 0; i < 16; i++) {
    fout << static_cast<char>(saved[i][0] + 'A');
    int row = saved[i][1] / 4 + 1;
    int col = saved[i][1] % 4 + 1;
    fout << ' ' << row << ' ' << col << endl;
  }
  fout << ans << endl;
  fout.close();
  return 0;
}
