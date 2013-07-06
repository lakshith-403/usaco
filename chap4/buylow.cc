/*
ID: liangyi1
PROG: buylow
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <string>
using namespace std;

const int BASE = 10000000;

class BigNumber {
  public:
    BigNumber() {
      len = 0;
      memset(a, 0, sizeof(a));
    }

    void Add(BigNumber that) {
      for (int i = 0; i < that.len; i++) a[i] += that.a[i];
      if (that.len > len) len = that.len;
      for (int i = 0; i < len; i++)
        if (a[i] >= BASE) {
          a[i + 1] += a[i] / BASE;
          a[i] %= BASE;
        }
      while (a[len] > 0) {
        if (a[len] >= BASE) {
          a[len + 1] = a[len] / BASE;
          a[len] %= BASE;
        }
        len++;
      }
    }

    void Set(int x) {
      len = 1;
      memset(a, 0, sizeof(a));
      a[0] = x;
    }

    friend ostream& operator<<(ostream &out, const BigNumber& num);

  private:
    int len;
    int a[10];
};

ostream& operator<<(ostream &out, const BigNumber& num) {
  int len = 0;
  char buf[100];
  for (int i = 0; i < num.len; i++) {
    int x = num.a[i];
    while (x > 0) {
      buf[len++] = '0' + x % 10;
      x /= 10;
    }
  }
  for (int i = len - 1; i >= 0; i--) out << buf[i];
  if (len == 0) out << '0';
  return out;
}

int n, p[5000], f[5000];
int max_len = 0;
BigNumber num[5000];

int main() {
  ifstream fin("buylow.in");
  fin >> n;
  for (int i = 0; i < n; i++) fin >> p[i];
  fin.close();

  f[0] = 1;
  num[0].Set(1);
  max_len = 1;
  for (int i = 1; i < n; i++) {
    int j;
    for (j = i - 1; j >= 0 && p[j] != p[i]; j--) {
      if (p[j] > p[i]) {
        if (f[j] + 1 > f[i]) {
          f[i] = f[j] + 1;
          num[i] = num[j];
        } else if (f[j] + 1 == f[i]) {
          num[i].Add(num[j]);
        }
      }
    }
    if (f[i] == 0 && j < 0) {  // New number.
      f[i] = 1;
      num[i].Set(1);
    }
    if (f[i] > max_len) max_len = f[i];
  }

  BigNumber ans;
  for (int i = 0; i < n; i++) {
    if (f[i] == max_len) ans.Add(num[i]);
  }

  ofstream fout("buylow.out");
  fout << max_len << ' ' << ans << endl;
  fout.close();
  return 0;
}
