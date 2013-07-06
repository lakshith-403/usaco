/*
ID: liangyi1
LANG: C++
TASK: cowtour
*/
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

int n;
double x[150], y[150];  // Grid locations.
int partition[150];

double d[150][150], f[150][150], g[150][150];

void ReadData(ifstream& fin) {
  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin >> x[i] >> y[i];
  }
  string bits;
  for (int i = 0; i < n; ++i) {
    fin >> bits;
    for (int j = 0; j < n; ++j) {
      if (bits[j] == '1') {
        d[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) *
            (y[i] - y[j]));
      }
    }
  }
}

void Floyd() {
  int i, j, k;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      g[i][j] = -1;
    }
  }
  memcpy(f, d, sizeof(d));
  for (k = 0; k < n; ++k) {
    for (i = 0; i < n; ++i) {
      for (j = 0; j < n; ++j) {
        if (i != j && k != i && k != j && f[i][k] != 0 && f[k][j] != 0) {
          if (f[i][j] == 0 || f[i][j] > f[i][k] + f[k][j]) {
            f[i][j] = f[i][k] + f[k][j];
            g[i][j] = k;
          }
        }
      }
    }
  }
}

double PickMin() {
  // Find the longest path from each pasture.
  int i, j;
  double longest[150];
  for (i = 0; i < n; ++i) {
    longest[i] = 0;
    int mate;
    for (j = 0; j < n; ++ j) {
      if (f[i][j] > longest[i]) {
        longest[i] = f[i][j];
        mate = j;
      }
    }
  }
  // Partition the graph and find the diameter of each partition.
  int partition_id[150];
  int new_id = 0;
  double diameter[150];
  memset(partition_id, 0, sizeof(partition_id));
  for (i = 0; i < n; ++i) {
    if (partition_id[i] == 0) {
      partition_id[i] = ++new_id;
      diameter[new_id] = longest[i];
      for (j = 0; j < n; ++j) {
        if (f[i][j] > 0) {
          partition_id[j] = new_id;
          if (longest[j] > diameter[new_id]) {
            diameter[new_id] = longest[j];
          }
        }
      }
    }
  }
  // Pick the one with max diameter.
  double best = 0;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      if (i != j && f[i][j] == 0) {
        double midway = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) *
            (y[i] - y[j]));
        double through_midway = midway + longest[i] + longest[j];
        double left_diameter = diameter[partition_id[i]];
        double right_diameter = diameter[partition_id[j]];
        double local_best = max(through_midway, max(left_diameter,
              right_diameter));
        if (local_best < best || best == 0) {
          best = local_best;
        }
      }
    }
  }
  return best;
}

int main() {
  ifstream fin("cowtour.in");
  ofstream fout("cowtour.out");
  ReadData(fin);
  Floyd();
  fout << setprecision(6) << fixed << PickMin() << endl;
  fin.close();
  fout.close();
  return 0;
}
