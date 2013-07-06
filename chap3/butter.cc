/*
ID: liangyi1
PROG: butter
LANG: C++
*/
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

int n, p, c;
int cows[800];
vector<pair<int, int> > e[800];
int dis[800];
bool in_queue[800];

int main() {
  ifstream fin("butter.in");
  fin >> n >> p >> c;
  for (int i = 0; i < n; ++i) {
    int pos;
    fin >> pos;
    ++cows[pos - 1];
  }
  for (int i = 0; i < c; ++i) {
    int x, y, z;
    fin >> x >> y >> z;
    e[x - 1].push_back(make_pair(y - 1, z));
    e[y - 1].push_back(make_pair(x - 1, z));
  }
  fin.close();

  int ans = 2147483647;
  for (int i = 0; i < p; ++i) {
    // SPFA!
    for (int j = 0; j < p; ++j) {
      dis[j] = 1000000;
      in_queue[j] = false;
    }
    queue<int> q;
    q.push(i);
    dis[i] = 0;
    in_queue[i] = true;
    while (!q.empty()) {
      int head = q.front();
      q.pop();
      in_queue[head] = false;
      // Relax.
      for (vector<pair<int, int> >::iterator it = e[head].begin();
          it != e[head].end(); ++it) {
        if (dis[head] + it->second < dis[it->first]) {
          dis[it->first] = dis[head] + it->second;
          if (!in_queue[it->first]) {
            q.push(it->first);
            in_queue[it->first] = true;
          }
        }
      }
    }

    int value = 0;
    for (int j = 0; j < p; ++j) {
      value += cows[j] * dis[j];
    }
    if (value < ans) {
      ans = value;
    }
  }

  ofstream fout("butter.out");
  fout << ans << endl;
  fout.close();

  return 0;
}
