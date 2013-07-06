/*
ID: liangyi1
PROG: gift1
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  ifstream fin("gift1.in");
  ofstream fout("gift1.out");
  int np;
  string name;
  vector<string> names;

  fin >> np;
  for (int i = 0; i < np; i++) {
    fin >> name;
    names.push_back(name);
  }

  vector<int> final(np, 0);
  vector<int> initial(np, 0);
  int num_receivers;
  for (int i = 0; i < np; i++) {
    fin >> name;
    int id = find(names.begin(), names.end(), name) - names.begin();
    cout << id << endl;
    fin >> initial[id] >> num_receivers;
    if (num_receivers > 0) {
      final[id] += initial[id] % num_receivers;
    } else {
      final[id] += initial[id];
    }
    for (int j = 0; j < num_receivers; j++) {
      fin >> name;
      int receiver = find(names.begin(), names.end(), name) - names.begin();
      final[receiver] += initial[id] / num_receivers;
    }
  }

  for (int i = 0; i < np; i++) {
    fout << names[i] << ' ' << final[i] - initial[i] << endl;
  }

  return 0;
}
