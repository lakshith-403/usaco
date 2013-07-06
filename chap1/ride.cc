/*
ID: liangyi1
PROG: ride
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  string comet_name, group_name;
  int n1, n2;

  ifstream fin("ride.in");
  ofstream fout("ride.out");
  fin >> comet_name >> group_name;
  n1 = n2 = 1;
  for (int i = 0; i < comet_name.length(); i++) {
    n1 *= (comet_name[i] - 'A' + 1);
  }
  for (int i = 0; i < group_name.length(); i++) {
    n2 *= (group_name[i] - 'A' + 1);
  }
  cout << n1 << ' ' << n2 << endl;
  if ((n1 % 47) == (n2 % 47)) {
    fout << "GO" << endl;
  } else {
    fout << "STAY" << endl;
  }
  return 0;
}
