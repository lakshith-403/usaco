/*
ID: liangyi1
PROG: heritage
LANG: C++
*/
#include <cstring>
#include <fstream>
using namespace std;

char pre[27];
char in[27];

void DumpPost(ostream &out, int in_l, int in_r, int pre_l, int pre_r) {
  if (in_l >= in_r || pre_l >= pre_r) return;
  int i;
  for (i = in_l; i != in_r; ++i) {
    if (in[i] == pre[pre_l]) break;
  }
  int len_l = i - in_l;
  DumpPost(out, in_l, i, pre_l + 1, pre_l + len_l + 1);
  DumpPost(out, i + 1, in_r, pre_l + len_l + 1, pre_r);
  out << pre[pre_l];
}

int main() {
  ifstream fin("heritage.in");
  fin >> in;
  fin >> pre;
  fin.close();

  ofstream fout("heritage.out");
  int len = strlen(in);
  DumpPost(fout, 0, len, 0, len);
  fout << endl;
  fout.close();
}
