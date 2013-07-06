/*
ID: liangyi1
PROG: friday
LANG: C++
*/
#include <cstring>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int DaysOfMonth(int month, int year) {
  if (month == 1) {
    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
      return 29;
    } else {
      return 28;
    }
  } else if (month == 0 || month == 2 || month == 4 || month == 6 || month == 7
             || month == 9 || month == 11) {
    return 31;
  } else {
    return 30;
  }
}

int main() {
  ifstream fin("friday.in");
  ofstream fout("friday.out");
  int n, weekday;
  int num_13[7];

  fin >> n;
  memset(num_13, 0, sizeof(num_13));
  weekday = 5;  // Jan 13, 1900 is Saturday.
  for (int year = 1900; year < 1900 + n; year++) {
    for (int month = 0; month < 12; month++) {
      num_13[weekday]++;
      weekday = (weekday + DaysOfMonth(month, year)) % 7;
    }
  }

  fout << num_13[5] << ' ' << num_13[6] << ' ' << num_13[0] << ' '
       << num_13[1] << ' ' << num_13[2] << ' ' << num_13[3] << ' '
       << num_13[4] << endl;

  return 0;
}
