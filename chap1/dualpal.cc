/*
ID: liangyi1
LANG: C++
TASK: dualpal
*/

#include <iostream>
#include <fstream>
using namespace std;

bool IsPalindromic(int s, int b) {
  string num;
  while (s > 0) {
    num.append(1, s % b + '0');
    s /= b;
  }
  for (int i = 0; i < num.length() / 2; i++) {
    if (num[i] != num[num.length() - i - 1]) return false;
  }
  return true;
}

int main() {
  ifstream fin("dualpal.in");
  ofstream fout("dualpal.out");
  int n, s, total = 0;
  fin >> n >> s;
  while (total < n) {
    s++;
    int is_pal = 0;
    for (int b = 2; b <= 10; b++) {
      if (IsPalindromic(s, b)) {
        is_pal++;
        if (is_pal >=2) break;
      }
    }
    if (is_pal >= 2) {
      fout << s << endl;
      total++;
    }
  }
  fin.close();
  fout.close();
  return 0;
}
