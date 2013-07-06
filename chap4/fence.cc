/*
ID: liangyi1
PROG: fence
LANG: C++
*/
#include <fstream>
#include <stack>
using namespace std;

int f;
int deg[501];
int connect[501][501];

int main() {
  ifstream fin("fence.in");
  fin >> f;
  for (int i = 0; i < f; ++i) {
    int x, y;
    fin >> x >> y;
    ++deg[x];
    ++deg[y];
    ++connect[x][y];
    ++connect[y][x];
  }
  fin.close();

  int node = -1;
  // Start at the lowest odd-degree intersection.
  for (int i = 1; i <= 500; ++i) {
    if (deg[i] % 2) {
      node = i;
      break;
    }
  }
  if (node == -1) {
    // Otherwise start at the lowest even-degree intersection.
    for (int i = 1; i <= 500; ++i) {
      if (deg[i]) {
        node = i;
        break;
      }
    }
  }

  stack<int> s;
  stack<int> path;
  while (true) {
    if (deg[node] == 0) {
      path.push(node);
      if (!s.empty()) {
        node = s.top();
        s.pop();
      } else {
        break;
      }
    } else {
      s.push(node);
      for (int i = 0; i <= 500; ++i) {
        if (connect[node][i] > 0) {
          --connect[node][i];
          --connect[i][node];
          --deg[node];
          --deg[i];
          node = i;
          break;
        }
      }
    }
  }

  // Output.
  ofstream fout("fence.out");
  while (!path.empty()) {
    fout << path.top() << endl;
    path.pop();
  }
  fout.close();

  return 0;
}
