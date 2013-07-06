/*
ID: liangyi1
LANG: C++
TASK: namenum
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const char map[26] = {'2', '2', '2', '3', '3', '3', '4', '4', '4', '5', '5',
  '5', '6', '6', '6', '7', '0', '7', '7', '8', '8', '8', '9', '9', '9', '0'};

int main() {
  ifstream fin("namenum.in");
  ifstream dict("dict.txt");
  ofstream fout("namenum.out");
  vector<string> valid;
  string number, name;
  fin >> number;
  while (dict >> name) {
    if (name.length() != number.length()) {
      continue;
    }
    bool is_valid = true;
    for (int i = 0; i < name.length(); i++) {
      if (number[i] != map[name[i] - 'A']) {
        is_valid = false;
        break;
      }
    }
    if (is_valid) {
      valid.push_back(name);
    }
  }
  sort(valid.begin(), valid.end());
  for (int i = 0; i < valid.size(); i++) fout << valid[i] << endl;
  if (valid.size() == 0) fout << "NONE\n";
  fin.close();
  dict.close();
  fout.close();
  return 0;
}
