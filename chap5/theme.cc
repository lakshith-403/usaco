/*
ID: liangyi1
PROG: theme
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int n;
int d[5000];
const int BUCKET_SIZE = 1000;
vector<int> bucket[BUCKET_SIZE];
int pow[2500];

void CalculatePower() {
  pow[0] = 1;
  for (int i = 1; i < 2500; i++)
    pow[i] = (pow[i - 1] * 175) % BUCKET_SIZE;
}

bool FindRepetition(int len) {
  for (int i = 0; i < BUCKET_SIZE; i++)
    bucket[i].clear();
  int hash = 0;
  for (int i = 0; i < len; i++)
    hash = (hash * 175 + d[i]) % BUCKET_SIZE;
  int head = 0, tail = len - 1;
  while (true) {
    bucket[hash].push_back(head);
    hash -= (d[head] * pow[len - 1]) % BUCKET_SIZE;
    hash = (hash + BUCKET_SIZE) % BUCKET_SIZE;
    head++;
    tail++;
    if (tail >= n) break;
    hash = (hash * 175 + d[tail]) % BUCKET_SIZE;
  }

  // Find repetitions in each bucekt.
  for (int i = 0; i < BUCKET_SIZE; i++) {
    int size = bucket[i].size();
    for (int j = 0; j < size; j++)
      for (int k = j + 1; k < size; k++) {
        if (bucket[i][k] - bucket[i][j] <= len) continue;
        bool same = true;
        int h1 = bucket[i][j], h2 = bucket[i][k];
        for (int l = 0; l < len; l++) {
          if (d[h1] != d[h2]) {
            same = false;
            break;
          }
          h1++;
          h2++;
        }
        if (same) {
          return true;
        }
      }
  }
  return false;
}

int main() {
  ifstream fin("theme.in");
  fin >> n;
  int last;
  fin >> last;
  for (int i = 0; i < n - 1; i++) {
    int x;
    fin >> x;
    d[i] = x - last + 87;
    last = x;
  }
  fin.close();

  CalculatePower();

  // Binary search.
  int l = 0, r = n / 2;
  while (l <= r) {
    int mid = (l + r) / 2;
    if (FindRepetition(mid)) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }

  ofstream fout("theme.out");
  fout << (r >= 4 ? r + 1 : 0) << endl;
  fout.close();

  return 0;
}
