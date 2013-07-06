/*
ID: liangyi1
PROG: sprime
LANG: C++
*/
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> primes;
vector<int> ans;

void GetPrimes() {
  vector<bool> is_prime(10000, true);
  for (int i = 2; i < is_prime.size(); i++) {
    int j = i + i;
    while (j < is_prime.size()) {
      is_prime[j] = false;
      j += i;
    }
  }
  for (int i = 2; i < is_prime.size(); i++) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
  }
}

bool IsPrime(int x) {
  int upper = sqrt(x);
  for (int i = 0; i < primes.size(); i++) {
    if (primes[i] > upper) break;
    if (x % primes[i] == 0) return false;
  }
  return true;
}

void Search(int len, int num) {
  if (len == n) {
    ans.push_back(num);
    return;
  }
  if (len == 0) {
    Search(1, 2);
  }
  for (int i = 1; i < 10; i += 2) {
    if (len == 0 && i == 1) continue;
    int next_num = num * 10 + i;
    if (IsPrime(next_num)) {
      Search(len + 1, next_num);
    }
  }
}

int main() {
  ifstream fin("sprime.in");
  ofstream fout("sprime.out");
  GetPrimes();
  fin >> n;
  Search(0, 0);
  for (int i = 0; i < ans.size(); i++) {
    fout << ans[i] << endl;
  }
  fin.close();
  fout.close();
  return 0;
}
