/*
ID: liangyi1
LANG: C++
TASK: milk
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Farmer {
  public:
    int price;
    int amount;

    Farmer(int price, int amount) {
      this->price = price;
      this->amount = amount;
    }

    bool operator <(const Farmer &that) const {
      return this->price < that.price;
    }
};

int main() {
  ifstream fin("milk.in");
  ofstream fout("milk.out");
  int n, m;
  vector<Farmer> farmers;
  fin >> n >> m;
  for (int i = 0; i < m; i++) {
    int price, amount;
    fin >> price >> amount;
    farmers.push_back(Farmer(price, amount));
  }
  sort(farmers.begin(), farmers.end());
  int ans = 0;
  for (int i = 0; i < m; i++) {
    if (n > farmers[i].amount) {
      ans += farmers[i].amount * farmers[i].price;
      n -= farmers[i].amount;
    } else {
      ans += farmers[i].price * n;
      break;
    }
  }
  fout << ans << endl;
  fin.close();
  fout.close();
  return 0;
}
