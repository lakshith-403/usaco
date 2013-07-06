/*
ID: liangyi1
PROG: preface
LANG: C++
*/
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int counts[26];
const char c10[4] = {'I', 'X', 'C', 'M'};
const char c5[3] = {'V', 'L', 'D'};
const char letters[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};

int main() {
  ifstream fin("preface.in");
  ofstream fout("preface.out");
  int n;
  fin >> n;
  for (int i = 1; i <= n; ++i) {
    int x = i, pos = 0;
    while (x > 0) {
      int digit = x % 10;
      if (digit == 0) {
        // Do nothing.
      } else if (digit <= 3) {
        counts[c10[pos] - 'A'] += digit;
      } else if (digit <= 8) {
        ++counts[c5[pos] - 'A'];
        counts[c10[pos] - 'A'] += abs(digit - 5);
      } else {
        ++counts[c10[pos + 1] - 'A'];
        if (digit == 9) {
          ++counts[c10[pos] - 'A'];
        }
      }
      x /= 10;
      ++pos;
    }
  }
  for (int i = 0; i < 7; ++i) {
    if (counts[letters[i] - 'A'] > 0) {
      fout << letters[i] << ' ' << counts[letters[i] - 'A'] << endl;
    }
  }
  fin.close();
  fout.close();
  return 0;
}
