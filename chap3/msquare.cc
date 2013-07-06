/*
ID: liangyi1
PROG: msquare
LANG: C++
*/
#include <fstream>
#include <queue>
using namespace std;

int from[40320];
char trans[40320];

struct State {
  char fig[8];
  int perm;
};

const char map[3][8] = {
  {7, 6, 5, 4, 3, 2, 1, 0},
  {3, 0, 1, 2, 5, 6, 7, 4},
  {0, 6, 1, 3, 4, 2, 5, 7}
};

const int fac[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};

int perm(char fig[]) {
  char i, j;
  char order;
  int ans = 0;
  for (i = 0; i < 7; ++i) {
    order = 0;
    for (j = i + 1; j < 8; ++j) {
      if (fig[j] < fig[i]) {
        ++order;
      }
    }
    ans += order * fac[7 - i];
  }
  return ans;
}

int main() {
  State target;
  ifstream fin("msquare.in");
  for (int i = 0; i < 8; ++i) {
    fin >> target.fig[i];
  }
  fin.close();
  target.perm = perm(target.fig);

  // Initialize and search.
  for (int i = 0; i < fac[8]; ++i) {
    from[i] = -1;
  }
  State state;
  for (int i = 0; i < 8; ++i) {
    state.fig[i] = i + 1;
  }
  state.perm = 0;
  from[0] = 0;
  queue<State> q;
  q.push(state);
  while (true) {
    state = q.front();
    q.pop();
    if (state.perm == target.perm) {
      break;
    }
    for (int i = 0; i < 3; ++i) {
      State ns;
      for (int j = 0; j < 8; ++j) {
        ns.fig[j] = state.fig[map[i][j]];
      }
      ns.perm = perm(ns.fig);
      if (from[ns.perm] == -1) {
        from[ns.perm] = state.perm;
        trans[ns.perm] = i;
        q.push(ns);
      }
    }
  }

  // Output the solution.
  ofstream fout("msquare.out");
  string s;
  for (int i = target.perm; i != 0; i = from[i]) {
    s.append(1, trans[i] + 'A');
  }
  fout << s.length() << endl;
  int total = 0;
  for (int i = s.size() - 1; i >= 0; --i) {
    fout << s[i];
    if (++total == 60) {
      fout << endl;
      total = 0;
    }
  }
  if (s.size() == 0 || total != 0) {
    fout << endl;
  }
  fout.close();

  return 0;
}
