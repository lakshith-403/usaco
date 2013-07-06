/*
ID: liangyi1
PROG: nuggets
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <queue>
using namespace std;

const int MAX_N = 300;

int main() {
  int n, min_num = MAX_N;
  int num[10];
  ifstream fin("nuggets.in");
  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin >> num[i];
    min_num = min(min_num, num[i]);
  }
  fin.close();

  // Number coloring.
  int min_pack[MAX_N];
  fill_n(min_pack, min_num, -1);
  queue<int> q;
  for (int i = 0; i < n; ++i) q.push(num[i]);
  while (!q.empty()) {
    int head = q.front();
    q.pop();
    if (min_pack[head % min_num] == -1 || head < min_pack[head % min_num]) {
      min_pack[head % min_num] = head;
      for (int i = 0; i < n; ++i) {
        q.push(head + num[i]);
      }
    }
  }

  bool all_colored = true;
  int ans = 0;
  for (int i = 0; i < min_num; ++i) {
    if (min_pack[i] == -1) {
      all_colored = false;
      break;
    }
    ans = max(ans, min_pack[i] - min_num);
  }
  ofstream fout("nuggets.out");
  fout << (all_colored ? ans : 0) << endl;
  fout.close();
  return 0;
}
