/*
ID: liangyi1
PROG: charrec
LANG: C++
*/
#include <algorithm>
#include <bitset>
#include <iostream>
#include <fstream>
using namespace std;

int n;  // Sample size.
bitset<20> font[27][20];
bitset<20> sample[1200];
int diff[27][20][1200];
const int MAX = 1000000;

int f[1200], from[1200];
char last_char[1200];

void ReadFonts() {
  ifstream fin("font.in");
  int n;
  fin >> n;
  for (int i = 0; i < 27; i++)
    for (int j = 0; j < 20; j++)
      fin >> font[i][j];
  fin.close();
}

void ReadSample() {
  ifstream fin("charrec.in");
  fin >> n;
  for (int i = 1; i <= n; i++) fin >> sample[i];
  fin.close();
}

void Preprocess() {
  for (int i = 0; i < 27; i++)
    for (int j = 19; j >= 0; j--)
      for (int k = n; k >= 1; k--) {
        diff[i][j][k] = (font[i][j] ^ sample[k]).count();
        if (j < 19 && k < n)
          diff[i][j][k] += diff[i][j + 1][k + 1];
      }
}

void DP() {
  f[0] = 0;
  for (int i = 1; i <= n; i++) f[i] = MAX;
  for (int i = 0; i < n; i++) {
    if (f[i] == MAX) continue;
    
    // Case 1: one line missing.
    if (i + 19 > n) continue;
    for (int j = 0; j < 27; j++) {
      for (int k = 0; k < 20; k++) {  // The missing line.
        int change = 0;
        if (k > 0) change += diff[j][0][i + 1] - diff[j][k][i + k + 1];
        if (k < 19) change += diff[j][k + 1][i + k + 1];
        if (change <= 120 && f[i] + change < f[i + 19]) {
          f[i + 19] = f[i] + change;
          from[i + 19] = i;
          last_char[i + 19] = j;
        }
      }
    }

    // Case 2: no duplicate and missing.
    if (i + 20 > n) continue;
    for (int j = 0; j < 27; j++) {
      int change = diff[j][0][i + 1];
      if (change <= 120 && f[i] + change < f[i + 20]) {
        f[i + 20] = f[i] + change;
        from[i + 20] = i;
        last_char[i + 20] = j;
      }
    }

    // Case 3: one line duplicated.
    if (i + 21 > n) continue;
    for (int j = 0; j < 27; j++) {
      for (int k = 0; k < 20; k++) {  // The extra line.
        int change = 0;
        if (k > 0) change += diff[j][0][i + 1] - diff[j][k][i + k + 1];
        if (k < 19) change += diff[j][k][i + k + 2];
        if (change <= 120 && f[i] + change < f[i + 21]) {
          f[i + 21] = f[i] + change;
          from[i + 21] = i;
          last_char[i + 21] = j;
        }
      }
    }
  }
}

void Output() {
  ofstream fout("charrec.out");
  string s;
  for (int i = n; i != 0; i = from[i])
    s.append(1, last_char[i] == 0 ? ' ' :
        static_cast<char>('a' + last_char[i] - 1));
  reverse(s.begin(), s.end());
  fout << s << endl;
  fout.close();
}

int main() {
  ReadFonts();
  ReadSample();
  Preprocess();
  DP();
  Output();
  return 0;
}
