/*
ID: liangyi1
LANG: C++
TASK: crypt1
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

int main() {
  ifstream fin("crypt1.in");
  ofstream fout("crypt1.out");
  int n;
  vector<int> digits;
  fin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    fin >> x;
    digits.push_back(x);
  }
  int ans = 0;
  // Enumerate the first number.
  for (int i = 0; i < pow((double)n, 3); i++) {
    int x = i;
    int num1[3];
    for (int j = 0; j < 3; j++) {
      num1[j] = digits[x % n];
      x /= n;
    }
    // Enumerate the lower digit of the second number.
    for (int j = 0; j < n; j++) {
      // Check the last digit of the product.
      if (find(digits.begin(), digits.end(), (num1[0] * digits[j]) % 10) ==
          digits.end()) {
        continue;
      }
      // Calculate and check the first partial product.
      int pp1[4];
      bool mismatch = false;
      pp1[0] = 0;
      for (int k = 0; k < 3; k++) {
        pp1[k] += num1[k] * digits[j];
        pp1[k + 1] = pp1[k] / 10;
        pp1[k] %= 10;
        if (find(digits.begin(), digits.end(), pp1[k]) == digits.end()) {
          mismatch = true;
          break;
        }
      }
      if (mismatch || pp1[3] != 0) {
        continue;
      }
      // Enumerate the higher digit of the second number.
      for (int k = 0; k < n; k++) {
        int pp2[4];
        bool mismatch = false;
        pp2[0] = 0;
        for (int l = 0; l < 3; l++) {
          pp2[l] += num1[l] * digits[k];
          pp2[l + 1] = pp2[l] / 10;
          pp2[l] %= 10;
          if (find(digits.begin(), digits.end(), pp2[l]) == digits.end()) {
            mismatch = true;
            break;
          }
        }
        if (mismatch || pp2[3] != 0) {
          continue;
        }
        // Check the final result.
        int result[5];
        mismatch = false;
        result[0] = pp1[0];
        result[1] = pp1[1] + pp2[0];
        result[2] = pp1[2] + pp2[1];
        result[3] = pp2[2];
        result[4] = 0;
        for (int l = 0; l < 4; l++) {
          if (result[l] > 10) {
            result[l + 1]++;
            result[l] -= 10;
          }
          if (find(digits.begin(), digits.end(), result[l]) == digits.end()) {
            mismatch = true;
            break;
          }
        }
        if (mismatch || result[4] != 0) {
          continue;
        } else {
          ans++;
        }
      }
    }
  }
  fout << ans << endl;
  fin.close();
  fout.close();
  return 0;
}
