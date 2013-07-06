/*
ID: liangyi1
PROG: shopping
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

struct Offer {
  int n;
  int code[5];
  int num[5];
  int price;
} offer[100];

int s, b;
int num[5];
int price[5];
int code_id[1000];
int f[7776];

void decode(int x, int *p) {
  while (x > 0) {
    *p++ = x % 6;
    x /= 6;
  }
}

int encode(int *p) {
  return p[4] * 1296 + p[3] * 216 + p[2] * 36 + p[1] * 6 + p[0];
}

int main() {
  ifstream fin("shopping.in");
  fin >> s;
  for (int i = 0; i < s; ++i) {
    fin >> offer[i].n;
    for (int j = 0; j < offer[i].n; ++j) {
      fin >> offer[i].code[j] >> offer[i].num[j];
    }
    fin >> offer[i].price;
  }
  fin >> b;
  for (int i = 0; i < 1000; ++i) {
    code_id[i] = -1;
  }
  memset(num, 0, sizeof(num));
  for (int i = 0; i < b; ++i) {
    int code;
    fin >> code >> num[i] >> price[i];
    code_id[code] = i;
  }
  fin.close();

  // Dynamic programming.
  int state[5], ns[5];
  for (int i = 0; i < 7776; ++i) {
    // Decode the state.
    memset(state, 0, sizeof(state));
    decode(i, state);
    // Necessary to compute?
    bool ok = true;
    for (int j = 0; j < 5; ++j) {
      if (state[j] > num[j]) {
        ok = false;
        break;
      }
    }
    if (!ok) continue;
    // Regular buy.
    for (int j = 0; j < b; ++j) {
      if (state[j] < num[j]) {
        memcpy(ns, state, sizeof(ns));
        ++ns[j];
        int value = encode(ns);
        if (f[value] == 0 || f[i] + price[j] < f[value]) {
          f[value] = f[i] + price[j];
        }
      }
    }
    // Use an offer.
    for (int j = 0; j < s; ++j) {
      ok = true;
      memcpy(ns, state, sizeof(ns));
      for (int k = 0; k < offer[j].n; ++k) {
        int id = code_id[offer[j].code[k]];
        if (id == -1 || ns[id] + offer[j].num[k] > num[id]) {
          ok = false;
          break;
        }
        ns[id] += offer[j].num[k];
      }
      if (!ok) continue;
      int value = encode(ns);
      if (f[value] == 0 || f[i] + offer[j].price < f[value]) {
        f[value] = f[i] + offer[j].price;
      }
    }
  }

  ofstream fout("shopping.out");
  int final = encode(num);
  fout << f[final] << endl;
  fout.close();
  return 0;
}
