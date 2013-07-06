/*
ID: liangyi1
LANG: C++
TASK: palsquare
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Note: the result is reverse, but that's ok for palindromic!
string ToBase(int num, int b) {
  string sa, sb;
  while (num > 0) {
    char bit = num % b;
    if (bit >= 10) {
      sa.append(1, bit - 10 + 'A');
    } else {
      sa.append(1, bit + '0');
    }
    num /= b;
  }
  for (int i = 0; i < sa.length(); i++) {
    sb.append(1, sa[sa.length() - i - 1]);
  }
  return sb;
}

bool IsPalindromic(string s) {
  for (int i = 0; i < s.length() / 2; i++) {
    if (s[i] != s[s.length() - i - 1]) return false;
  }
  return true;
}

int main() {
  ifstream fin("palsquare.in");
  ofstream fout("palsquare.out");
  int b;
  fin >> b;
  for (int n = 1; n <= 300; n++) {
    string num = ToBase(n, b);
    string sq = ToBase(n * n, b);
    if (IsPalindromic(sq)) {
      fout << num << ' ' << sq << endl;
    }
  }
  fin.close();
  fout.close();
  return 0;
}
