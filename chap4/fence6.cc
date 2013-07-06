/*
ID: liangyi1
PROG: fence6
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

int n, num_nodes;  // nodes are numbered from 1.
int node_id[101][2];
int cross[101][101];
int dis[200][200];
int f[200][200];

int main() {
  int ns1[8], ns2[8];
  ifstream fin("fence6.in");
  fin >> n;
  for (int i = 0; i < n; ++i) {
    int s, l, n1, n2;
    fin >> s >> l >> n1 >> n2;
    for (int j = 0; j < n1; ++j) {
      fin >> ns1[j];
      if (cross[s][ns1[j]] != 0) node_id[s][0] = cross[s][ns1[j]];
    }
    if (node_id[s][0] == 0) node_id[s][0] = ++num_nodes;
    for (int j = 0; j < n1; ++j) {
      cross[s][ns1[j]] = cross[ns1[j]][s] = node_id[s][0];
    }
    for (int j = 0; j < n2; ++j) {
      fin >> ns2[j];
      if (cross[s][ns2[j]] != 0) node_id[s][1] = cross[s][ns2[j]];
    }
    if (node_id[s][1] == 0) node_id[s][1] = ++num_nodes;
    for (int j = 0; j < n2; ++j) {
      cross[s][ns2[j]] = cross[ns2[j]][s] = node_id[s][1];
    }
    dis[node_id[s][0]][node_id[s][1]] = dis[node_id[s][1]][node_id[s][0]] = l;
  }

  // Floyd.
  int ans = 1000000;
  memcpy(f, dis, sizeof(f));
  for (int k = 1; k <= num_nodes; ++k) {
    // Update.
    for (int i = k + 1; i <= num_nodes; ++i) {
      for (int j = 1; j <= num_nodes; ++j) {
        if (dis[i][k] > 0 && f[i][j] > 0 && f[j][k] > 0 &&
            dis[i][k] + f[i][j] + f[j][k] < ans) {
          ans = dis[i][k] + f[i][j] + f[j][k];
        }
      }
    }
    for (int i = 1; i <= num_nodes; ++i) {
      for (int j = 1; j <= num_nodes; ++j) {
        if (i != j && f[i][k] != 0 && f[k][j] != 0 &&
            (f[i][j] == 0 || f[i][k] + f[k][j] < f[i][j])) {
          f[i][j] = f[i][k] + f[k][j];
        }
      }
    }
  }

  ofstream fout("fence6.out");
  fout << ans << endl;
  fout.close();
  return 0;
}
