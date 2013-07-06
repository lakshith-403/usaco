/*
ID: liangyi1
LANG: C++
TASK: clocks
*/

#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

int clocks[12];
int times[9], best_times[9];
int ans = 3 * 9 + 1;

void search(int move, int num_steps) {
  if (num_steps >= ans) return;
  if (move == 9) {
    ans = num_steps;
    memcpy(best_times, times, sizeof(times));
    return;
  }
  // Enumerate the number of times of the current move.
  for (int i = 0; i < 4; i++) {
    times[move] = i;
    // Check the clocks.
    if (move == 3) {
      // Check A.
      if ((clocks[0] + times[0] + times[1] + times[3]) % 4 != 0) continue;
    } else if (move == 4) {
      // Check B.
      if ((clocks[1] + times[0] + times[1] + times[2] + times[4]) % 4 != 0) {
        continue;
      }
    } else if (move == 5) {
      // Check C.
      if ((clocks[2] + times[1] + times[2] + times[5]) % 4 != 0) continue;
    } else if (move == 6) {
      // Check D.
      if ((clocks[3] + times[0] + times[3] + times[4] + times[6]) % 4 != 0) {
        continue;
      }
    } else if (move == 7) {
      // Check G.
      if ((clocks[6] + times[3] + times[6] + times[7]) % 4 != 0) continue;
    } else if (move == 8) {
      // Check E.
      if ((clocks[4] + times[0] + times[2] + times[4] + times[6] + times[8])
          % 4 != 0) {
        continue;
      }
      // Check F.
      if ((clocks[5] + times[2] + times[4] + times[5] + times[8]) % 4 != 0) {
        continue;
      }
      // Check H.
      if ((clocks[7] + times[4] + times[6] + times[7] + times[8]) % 4 != 0) {
        continue;
      }
      // Check I.
      if ((clocks[8] + times[5] + times[7] + times[8]) % 4 != 0) {
        continue;
      }
    }
    search(move + 1, num_steps + i);
  }
}

int main() {
  ifstream fin("clocks.in");
  ofstream fout("clocks.out");
  for (int i = 0; i < 12; i++) {
    fin >> clocks[i];
    clocks[i] = clocks[i] / 3;
  }
  search(0, 0);
  bool first = true;
  for (int i = 0; i < 9; i++) {
    while (best_times[i] > 0) {
      if (first) {
        first = false;
      } else {
        fout << ' ';
      }
      fout << i + 1;
      best_times[i]--;
    }
  }
  fout << endl;
  fin.close();
  fout.close();
  return 0;
}
