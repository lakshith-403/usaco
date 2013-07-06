/*
ID: liangyi1
PROG: pprime
LANG: C++
*/
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int a, b;
vector<int> primes;

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

int Reverse(int x) {
  int ret = 0;
  while (x > 0) {
    ret = ret * 10 + x % 10;
    x /= 10;
  }
  return ret;
}

int main() {
  ifstream fin("pprime.in");
  ofstream fout("pprime.out");
  fin >> a >> b;
  GetPrimes();
  // Get the lower length and upper length of the numbers.
  int low = log10(a) + 1;
  int high = min((int)log10(b) + 1, 8);
  // Enumerate.
  vector<int> pal_primes;
  for (int i = low; i <= high; i++) {
    // Special case.
    if (i == 1) {
      pal_primes.push_back(5);
      pal_primes.push_back(7);
      continue;
    }
    // Enumerate the palindromic part.
    for (int j = pow(10, i / 2 - 1); j < pow(10, i / 2); j++) {
      if (i % 2 == 0) {
        int num = j * pow(10, i / 2) + Reverse(j);
        if (IsPrime(num)) {
          pal_primes.push_back(num);
        }
      } else {
        for (int k = 0; k < 10; k++) {
          int num = j * pow(10, i / 2 + 1) + k * pow(10, i / 2) + Reverse(j);
          if (IsPrime(num)) {
            pal_primes.push_back(num);
          }
        }
      }
    }
  }
  for (int i = 0; i < pal_primes.size(); i++) {
    if (pal_primes[i] >= a && pal_primes[i] <= b) {
      fout << pal_primes[i] << endl;
    }
  }
  fin.close();
  fout.close();
  return 0;
}
