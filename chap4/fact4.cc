/*
ID: liangyi1
PROG: fact4
LANG: C++
*/
#include <fstream>
#include <iostream>
using namespace std;

int fact5[4221];
const int pow5[] = {1, 5, 25, 125, 625, 3125};

int main() {
  ifstream fin("fact4.in");
  int n;
  fin >> n;
  fin.close();

  int total5 = 0;
  for (int i = 5; i <= n; ++i) {
    if (i % 5 == 0) {
      fact5[i] = fact5[i / 5] + 1;
    }
    total5 += fact5[i];
  }

  int total2 = 0;
  int ans = 1;
  for (int i = 2; i <= n; ++i) {
    int num = i;
    while (num % 2 == 0 && total2 < total5) {
      num /= 2;
      ++total2;
    }
    num /= pow5[fact5[num]];
    ans = (ans * num) % 10;
  }

  ofstream fout("fact4.out");
  fout << ans << endl;
  fout.close();
  return 0;
}
