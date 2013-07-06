/*
ID: liangyi1
PROG: agrinet
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <iostream>
#include <set>
using namespace std;

int n;
int dis[100][100];

void ReadData(ifstream &fin) {
  fin >> n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      fin >> dis[i][j];
    }
  }
}

int Prim() {
  int length = 0;
  bool connected[100];
  int min_dis[100];
  // Initialize: put the first farm in the connected set.
  memset(connected, 0, sizeof(connected));
  connected[0] = true;
  for (int i = 0; i < n; ++i) {
    min_dis[i] = dis[0][i];
  }
  // Main loop: iteratively add new farms.
  for (int i = 1; i < n; ++i) {
    int next_farm, best_dis = -1;
    for (int j = 0; j < n; ++j) {
      if (!connected[j] && (best_dis == -1 || min_dis[j] < best_dis)) {
        best_dis = min_dis[j];
        next_farm = j;
      }
    }
    // Connect the new farm.
    connected[next_farm] = true;
    length += best_dis;
    // Update the minial distance of unconnected farms.
    for (int j = 0; j < n; ++j) {
      if (!connected[j] && dis[next_farm][j] < min_dis[j]) {
        min_dis[j] = dis[next_farm][j];
      }
    }
  }
  return length;
}

int main() {
  ifstream fin("agrinet.in");
  ofstream fout("agrinet.out");
  ReadData(fin);
  fout << Prim() << endl;
  fin.close();
  fout.close();
  return 0;
}
