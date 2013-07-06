/*
ID: liangyi1
LANG: C++
TASK: transform
*/

#include <iostream>
#include <fstream>
using namespace std;

int n;
string a[10], b[10], c[10];

void NoChange() {
  for (int i = 0; i < n; i++) c[i] = a[i];
}

void Reflect(string a[], string c[]) {
  string b[10];
  for (int i = 0; i < n; i++) b[i] = a[i];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      c[i][n - j - 1] = b[i][j];
}

void Rotate90(string a[], string c[]) {
  string b[10];
  for (int i = 0; i < n; i++) b[i] = a[i];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      c[j][n - i - 1] = b[i][j];
}

void Rotate180(string a[], string c[]) {
  string b[10];
  for (int i = 0; i < n; i++) b[i] = a[i];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      c[n - i - 1][n - j - 1] = b[i][j];
}

void Rotate270(string a[], string c[]) {
  string b[10];
  for (int i = 0; i < n; i++) b[i] = a[i];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      c[n - j - 1][i] = b[i][j];
}

bool TestEqual() {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (b[i][j] != c[i][j])
        return false;
  return true;
}

int DecideMinimum() {
  Rotate90(a, c);
  if (TestEqual()) return 1;
  Rotate180(a, c);
  if (TestEqual()) return 2;
  Rotate270(a, c);
  if (TestEqual()) return 3;
  Reflect(a, c);
  if (TestEqual()) return 4;
  Reflect(a, c);
  Rotate90(c, c);
  if (TestEqual()) return 5;
  Reflect(a, c);
  Rotate180(c, c);
  if (TestEqual()) return 5;
  Reflect(a, c);
  Rotate270(c, c);
  if (TestEqual()) return 5;
  NoChange();
  if (TestEqual()) return 6;
  return 7;
}

int main() {
  ifstream fin("transform.in");
  ofstream fout("transform.out");
  fin >> n;
  for (int i = 0; i < n; i++) {
    fin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    fin >> b[i];
  }
  // Get some space for c.
  for (int i = 0; i < n; i++) c[i] = a[i];
  fout << DecideMinimum() << endl;
  fin.close();
  fout.close();
  return 0;
}
