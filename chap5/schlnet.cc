#include <fstream>
#include <queue>
using namespace std;

int n;
int num[100];
int g[100][100];

int Task1() {
  int color = 0;
  int c[100] = {0};
  for (int i = 0; i < n; i++) {
    if (c[i]) continue;
    c[i] = ++color;
    queue<int> q;
    q.push(i);
    bool visit[100] = {0};
    visit[i] = true;
    while (!q.empty()) {
      int h = q.front();
      q.pop();
      for (int j = 0; j < num[h]; j++) {
        if (!go[g[h][j]]) {
          go[g[h][j]] = true;
          c[g[h][j]] = color;
          q.push(g[h][j]);
        }
      }
    }
  }
  int ret = 0;
  bool use_c[100] = {0};
  for (int i = 0; i < n; i++)
    use_c[c[i]] = true;
  for (int i = 0; i < n; i++)
    ret += use_c[i];
  return ret;
}

int total;  // Number of components.
int prev;  // The last found component's id.
int id[100];  // Id of its strongly-connected component.
bool has_in[100], has_out[100];  // Does the component has in-arc/out-arc?
int index;
int order[100];  // DFS index.

int DFS(int node) {
  int low = order[node] = ++index;
  for (int i = 0; i < num[node]; i++) {
    if (!index[g[node][i]]) {
      int sub_low = DFS(g[node][i]);
      if (sub_low < low) low = sub_low;
    } else {
      if (index[g[node[i]]] < low) low = index[g[node][i]];
    }
  }
  // Is it the end of a component?
}

int Task2() {
  for (int i = 0; i < n; i++)
    if (!id[i]) DFS(0, i);
}

int main() {
  ifstream fin("schlnet.in");
  fin >> n;
  for (int i = 0; i < n; i++) {
    int r;
    for (fin >> r; r != 0; fin >> r)
      g[i][num[i]++] = r;
  }
  fin.close();

  ofstream fout("schlnet.in");
  // Task 1: graph coloring.
  fout << Task1() << endl;
  // Task 2: find the strongly-connected components.
  fout << Task2() << endl;
  fout.close();
  return 0;
}
