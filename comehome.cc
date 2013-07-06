/*
ID: liangyi1
PROG: comehome
LANG: C++
*/
#include <cctype>
#include <fstream>
#include <iostream>
using namespace std;

const int n = 52;
int dis[52][52];

int index(char c) {
  return isupper(c) ? (c - 'A') : (26 + c - 'a');
}

void ReadData(ifstream &fin) {
  int p, len, i1, i2;
  char c1, c2;
  fin >> p;
  for (int i = 0; i < p; ++i) {
    fin >> c1 >> c2 >> len;
    i1 = index(c1);
    i2 = index(c2);
    if (dis[i1][i2] == 0 || dis[i1][i2] > len) {
      dis[i1][i2] = dis[i2][i1] = len;
    }
  }
}

void Floyd() {
  int i, j, k;
  for (k = 0; k < 52; ++k) {
    for (i = 0; i < 52; ++i) {
      for (j = 0; j < 52; ++j) {
        if (i != j && i != k && j != k && dis[i][k] != 0 && dis[k][j] != 0) {
          if (dis[i][j] == 0 || dis[i][j] > dis[i][k] + dis[k][j]) {
            dis[i][j] = dis[i][k] + dis[k][j];
          }
        }
      }
    }
  }
}

int main() {
  ifstream fin("comehome.in");
  ofstream fout("comehome.out");
  ReadData(fin);
  Floyd();
  int best, len = 0;
  for (int i = 0; i < 25; ++i) {  // Exclude 'Z' itself.
    if (dis[i][25] != 0 && (len == 0 || dis[i][25] < len)) {
      len = dis[i][25];
      best = i;
    }
  }
  fout << (char)(best + 'A') << ' ' << len << endl;
  fin.close();
  fout.close();
  return 0;
}
