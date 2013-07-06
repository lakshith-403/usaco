/*
ID: liangyi1
PROG: milk3
LANG: C++
*/

#include <fstream>
#include <iostream>
using namespace std;

int ca, cb, cc;
bool state[21][21][21];
bool ans[21];

void expand(int a, int b, int c) {
  if (state[a][b][c]) {
    return;
  } else {
    state[a][b][c] = true;
    if (a == 0) {
      ans[c] = true;
    }
  }
  int amount;
  // A to B.
  amount = min(a, cb - b);
  expand(a - amount, b + amount, c);
  // A to C.
  amount = min(a, cc - c);
  expand(a - amount, b, c + amount);
  // B to A.
  amount = min(b, ca - a);
  expand(a + amount, b - amount, c);
  // B to C.
  amount = min(b, cc - c);
  expand(a, b - amount, c + amount);
  // C to A.
  amount = min(c, ca - a);
  expand(a + amount, b, c - amount);
  // C to B.
  amount = min(c, cb - b);
  expand(a, b + amount, c - amount);
}

int main() {
  ifstream fin("milk3.in");
  ofstream fout("milk3.out");
  fin >> ca >> cb >> cc;
  expand(0, 0, cc);
  bool first = true;
  for (int i = 0; i <= cc; i++) {
    if (ans[i]) {
      if (first) {
        first = false;
      } else {
        fout << ' ';
      }
      fout << i;
    }
  }
  fout << endl;
  fin.close();
  fout.close();
  return 0;
}
