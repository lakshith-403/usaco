/*
ID: liangyi1
PROG: fracdec
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

void put_and_newline(ofstream &fout, char c) {
  static int counter = 0;
  if (c == '\n' && counter == 0) return;
  fout.put(c);
  if (++counter == 76) {
    counter = 0;
    fout.put('\n');
  }
}


int main() {
  ifstream fin("fracdec.in");
  ofstream fout("fracdec.out");
  int n, d;
  fin >> n >> d;
  int integral = n / d;
  int residual = n % d * 10;
  if (residual == 0) {
    fout << integral << ".0" << endl;
    fin.close();
    fout.close();
    return 0;
  }
  vector<int> decimal;
  map<int, int> positions;
  // Repeat until the same residual appears twice.
  while (residual != 0 && positions.find(residual) == positions.end()) {
    // Record the position of this residual.
    positions.insert(make_pair(residual, decimal.size()));
    // Compute a new decimal digit.
    decimal.push_back(residual / d);
    residual = residual % d * 10;
  }
  int left_bracket = (residual != 0) ? (positions.find(residual)->second) : -1;
  char buffer[10];
  sprintf(buffer, "%d", integral);
  for (int i = 0; i < strlen(buffer); ++i) {
    put_and_newline(fout, buffer[i]);
  }
  put_and_newline(fout, '.');
  // The fraction.
  for (int i = 0; i < decimal.size(); ++i) {
    if (i == left_bracket) {
      put_and_newline(fout, '(');
    }
    put_and_newline(fout, decimal[i] + '0');
  }
  if (residual != 0) {
    put_and_newline(fout, ')');
  }
  put_and_newline(fout, '\n');
  fin.close();
  fout.close();
  return 0;
}
