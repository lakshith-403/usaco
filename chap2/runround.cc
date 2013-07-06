/*
ID: liangyi1
PROG: runround
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <vector>
using namespace std;

bool used[10];

bool IsRunaround(int x) {
  int digit;
  vector<int> digits;
  memset(used, 0, sizeof(used));
  while (x > 0) {
    digit = x % 10;
    if (digit == 0) return false;
    if (used[digit]) return false;
    used[digit] = true;
    digits.push_back(digit);
    x /= 10;
  }
  int i = digits.size() - 1, total = 0;
  do {
    ++total;
    i -= digits[i] % digits.size();
    if (i < 0) i += digits.size();
  } while (i != digits.size() - 1 && total < digits.size());
  return i == digits.size() - 1 && total == digits.size();
}

int main() {
  ifstream fin("runround.in");
  ofstream fout("runround.out");
  int m;
  fin >> m;
  do {
    ++m;
  } while (!IsRunaround(m));
  fout << m << endl;
  fin.close();
  fout.close();
  return 0;
}
