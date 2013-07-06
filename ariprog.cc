/*
ID: liangyi1
PROG: ariprog
LANG: C++
*/

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ifstream fin("ariprog.in");
  ofstream fout("ariprog.out");
  int n, m;
  fin >> n >> m;
  // Get all the bisquares.
  vector<bool> is_bisquare(m * m * 2 + 1, false);
  for (int p = 0; p <= m; p++) {
    for (int q = 0; q <= m; q++) {
      is_bisquare[p * p + q * q] = true;
    }
  }
  vector<int> bisquares;  // Max size: 20k.
  for (int i = 0; i < is_bisquare.size(); i++) {
    if (is_bisquare[i]) {
      bisquares.push_back(i);
    }
  }
  // Estimate the max possible difference.
  int max_diff = is_bisquare.size() / (n - 1);
  // Enumerate the sequence from min to max difference.
  bool output = false;
  for (int b = 1; b <= max_diff; b++) {
    vector<int> starters;
    for (vector<int>::reverse_iterator a = bisquares.rbegin();
         a != bisquares.rend(); a++) {
      if (*a - b * (n - 1) < 0) break;
      // if (!is_bisquare[*a - b * (n - 1)]) continue;
      int i = *a, rest = n;
      while (rest > 0 && is_bisquare[i]) {
        rest--;
        i -= b;
      }
      if (rest == 0) {
        starters.push_back(*a - b * (n - 1));
      }
    }
    if (!starters.empty()) {
      output = true;
      for (vector<int>::reverse_iterator rit = starters.rbegin(); rit !=
           starters.rend(); rit++) {
        fout << *rit << ' ' << b << endl;
      }
    }
  }
  if (!output) {
    fout << "NONE" << endl;
  }
  fin.close();
  fout.close();
  return 0;
}
