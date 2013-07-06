/*
ID: liangyi1
LANG: C++
TASK: calfflac
*/

#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
using namespace std;

void Extend(const string &s, int *len, int *l, int *r) {
  while (true) {
    int new_l = *l - 1;
    while (new_l >= 0 && !isalpha(s[new_l])) {
      new_l--;
    }
    int new_r = *r + 1;
    while (new_r < s.length() && !isalpha(s[new_r])) {
      new_r++;
    }
    if (new_l >= 0 && new_r < s.length() && tolower(s[new_l]) == 
        tolower(s[new_r])) {
      *l = new_l;
      *r = new_r;
      *len += 2;
    } else {
      break;
    }
  }
}

int main() {
  ifstream fin("calfflac.in");
  ofstream fout("calfflac.out");
  // Get the original string.
  string s, line;
  while (getline(fin, line)) {
    s += line + '\n';
  }
  // Find the longest.
  int longest = 0, best_l, best_r;
  for (int i = 0; i < s.length(); i++) {
    // Case 1: s[i] is the center.
    // Tricky below: isalpha may return any non-zero integer as "true"!
    int len = (bool)isalpha(s[i]), l = i, r = i;
    Extend(s, &len, &l, &r);
    if (len > longest) {
      longest = len;
      best_l = l;
      best_r = r;
    }
    // Case 2: s[i],s[i+1] is the center.
    len = 0;
    l = i + 1;
    r = i;
    Extend(s, &len, &l, &r);
    if (len > longest) {
      longest = len;
      best_l = l;
      best_r = r;
    }
  }
  fout << longest << endl;
  for (int i = best_l; i <= best_r; i++) fout << s[i];
  fout << '\n';
  fin.close();
  fout.close();
  return 0;
}
