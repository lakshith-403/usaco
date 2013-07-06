/*
ID: liangyi1
PROG: zerosum
LANG: C++
*/
#include <fstream>
#include <vector>
using namespace std;

ofstream fout("zerosum.out");
int n;
vector<char> operators;

void Search(int i, char pre_op, int operand, int result) {
  if (i > n) {
    result += (pre_op == '+'? operand: -operand);
    if (result == 0) {
      fout << '1';
      for (int i = 0; i < n - 1; ++i) {
        fout << operators[i] << i + 2;
      }
      fout << endl;
    }
  } else {
    // Try space ' '.
    operators.push_back(' ');
    Search(i + 1, pre_op, operand * 10 + i, result);
    operators.pop_back();
    // Try add '+'.
    operators.push_back('+');
    Search(i + 1, '+', i, result + (pre_op == '+'? operand: -operand));
    operators.pop_back();
    // Try minus '-'.
    operators.push_back('-');
    Search(i + 1, '-', i, result + (pre_op == '+'? operand: -operand));
    operators.pop_back();
  }
}

int main() {
  ifstream fin("zerosum.in");
  fin >> n;
  Search(2, '+', 1, 0);
  fin.close();
  fout.close();
  return 0;
}
