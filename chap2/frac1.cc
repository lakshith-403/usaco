/*
ID: liangyi1
PROG: frac1
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Frac {
 public:
  Frac(int num, int denom) {
    this->num = num;
    this->denom = denom;
  }

  bool operator <(const Frac &other) const {
    return num * other.denom < denom * other.num;
  }

  int num, denom;
};

int GCD(int a, int b) {
  if (b == 0) {
    return a;
  } else if (a >= b) {
    return GCD(b, a % b);
  } else {
    return GCD(b, a);
  }
}

int main() {
  ifstream fin("frac1.in");
  ofstream fout("frac1.out");
  int n;
  fin >> n;
  vector<Frac> fracs;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= i; ++j) {
      if (GCD(i, j) == 1) {
        fracs.push_back(Frac(j, i));
      }
    }
  }
  sort(fracs.begin(), fracs.end());
  for (int i = 0; i < fracs.size(); ++i) {
    fout << fracs[i].num << '/' << fracs[i].denom << endl;
  }
  fin.close();
  fout.close();
  return 0;
}
