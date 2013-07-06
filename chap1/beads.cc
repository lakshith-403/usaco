/*
ID: liangyi1
LANG: C++
TASK: beads
*/

#include <fstream>
#include <vector>
using namespace std;

#define CHECK(x) if (x > n) x = n;
#define RECORD(x) if (x > ans) ans = x;

int main() {
  ifstream fin("beads.in");
  ofstream fout("beads.out");
  int n;
  string beads;
  fin >> n;
  fin >> beads;
  fin.close();
  beads.append(beads, 0, beads.length() - 1);
  // Things like f[n][BLUE..RED][0..1].
  int red0 = 0, blue0 = 0, red1 = 0, blue1 = 0;
  int ans = 0;
  for (int i = 0; i < beads.length(); i++) {
    if (beads[i] == 'b') {
      red0 = 0;
      ++blue0;
      ++blue1;
      red1 = blue0;
    } else if (beads[i] == 'r') {
      blue0 = 0;
      ++red0;
      ++red1;
      blue1 = red0;
    } else if (beads[i] == 'w') {
      ++red0;
      ++red1;
      ++blue0;
      ++blue1;
    }
    // Out of bound check.
    CHECK(red0);
    CHECK(red1);
    CHECK(blue0);
    CHECK(blue1);
    // Record the max.
    RECORD(red0);
    RECORD(red1);
    RECORD(blue0);
    RECORD(blue1);
  }
  fout << ans << endl;
  fout.close();
  return 0;
}
