/*
ID: liangyi1
PROG: fence8
LANG: C++
*/
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

int n, m, total;
int b[51], sum_b[51], rest[51];
int r[1024], sum_r[1024], num_r[129], size[129];
int need[129];  // Search states for rails.

bool Search(int pos, int last_pos, int cap, int sum_r) {
  if (pos == -1) return true;
  if (cap < sum_r) return false;
  for (int i = last_pos; i >= 1; --i) {
    if (rest[i] < size[pos]) continue;
    if (b[i] < size[pos]) break;
    if (rest[i] == size[pos]) {
      rest[i] = 0;
      --need[pos];
      if (Search(need[pos] == 0 ? pos - 1 : pos,
            need[pos] == 0 ? n : i,
            cap - size[pos], sum_r - size[pos])) return true;
      ++need[pos];
      rest[i] = size[pos];
      return false;
    } else if (rest[i] - size[pos] < size[0]) {
      rest[i] -= size[pos];
      --need[pos];
      if (Search(need[pos] == 0 ? pos - 1 : pos,
            need[pos] == 0 ? n : i,
            cap - rest[i] - size[pos], sum_r - size[pos])) return true;
      ++need[pos];
      rest[i] += size[pos];
    } else {
      // Normal case.
      rest[i] -= size[pos];
      --need[pos];
      if (Search(need[pos] == 0 ? pos - 1 : pos,
            need[pos] == 0 ? n : i,
            cap - size[pos], sum_r - size[pos])) return true;
      ++need[pos];
      rest[i] += size[pos];
    }
  }
  return false;
}

int main() {
  ifstream fin("fence8.in");
  fin >> n;
  for (int i = 1; i <= n; ++i) {
    fin >> b[i];
  }
  fin >> m;
  for (int i = 1; i <= m; ++i) {
    fin >> r[i];
    ++num_r[r[i]];
  }
  fin.close();

  // Preprocess.
  sort(b + 1, b + n + 1);
  sort(r + 1, r + m + 1);
  for (int i = 1; i <= n; ++i) sum_b[i] = sum_b[i - 1] + b[i];
  for (int i = 1; i <= m; ++i) sum_r[i] = sum_r[i - 1] + r[i];
  int num_sizes = 0;
  for (int i = 1; i <= 128; ++i) {
    if (num_r[i] > 0) size[num_sizes++] = i;
  }

  // IDA.
  total = 0;
  while (total < m) {
    ++total;
    // Initialize.
    memcpy(rest, b, sizeof(rest));
    memset(need, 0, sizeof(need));
    int i = 0, amount = total;
    while (amount > num_r[size[i]]) {
      need[i] = num_r[size[i]];
      amount -= num_r[size[i]];
      ++i;
    }
    need[i] = amount;
    if (!Search(i, n, sum_b[n], sum_r[total])) {
      --total;
      break;
    }
  }

  ofstream fout("fence8.out");
  fout << total << endl;
  fout.close();
  return 0;
}
