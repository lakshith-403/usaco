/*
ID: liangyi1
PROG: cowcycle
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

int f, r, f1, f2, r1, r2;
double best_var = 1e10;
int front[5], rear[10];
int best_f[5], best_r[10];

// For computing variance.
int total;
double buffer[50];

void SearchRear(int pos) {
  if (pos == r - 1 || r == 1) {
    total = 0;
    for (int i = 0; i < f; i++)
      for (int j = r - 1; j >= 0; j--) {
        buffer[total] = (double) front[i] / rear[j];
        for (int k = total; k > 0 && buffer[k - 1] > buffer[k]; k--) {
          double temp = buffer[k - 1];
          buffer[k - 1] = buffer[k];
          buffer[k] = temp;
        }
        total++;
      }
    double var = 0;
    for (int i = 0; i < f * r - 1; i++)
      var += (buffer[i + 1] - buffer[i]) * (buffer[i + 1] - buffer[i]);
    var /= f * r - 1;
    double mean = (double) front[f - 1] / rear[0] -
      (double) front[0] / rear[r - 1];
    mean /= f * r - 1;
    var -= mean * mean;
    if (var < best_var) {
      best_var = var;
      memcpy(best_f, front, sizeof(best_f));
      memcpy(best_r, rear, sizeof(best_r));
      cout << best_var << endl;
      /*
      for (int i = 0; i < f; i++) cout << front[i] << ' ';
      cout << endl;
      for (int i = 0; i < r; i++) cout << rear[i] << ' ';
      cout << endl;
      */
    }
    return;
  }
  for (int i = rear[pos - 1] + 1; i <= rear[r - 1] - (r - 1 - pos); i++) {
    rear[pos] = i;
    SearchRear(pos + 1);
  }
}

void SearchFront(int pos) {
  if (pos == f - 1 || f == 1) {
    SearchRear(1);
    return;
  }
  for (int i = front[pos - 1] + 1; i <= front[f - 1] - (f - 1 - pos); i++) {
    front[pos] = i;
    SearchFront(pos + 1);
  }
}

int main() {
  ifstream fin("cowcycle.in");
  fin >> f >> r;
  fin >> f1 >> f2 >> r1 >> r2;
  fin.close();

  for (int i = f1; i <= f2 - f + 1; i++)
    for (int j = i + f - 1; j <= f2; j++)
      for (int k = r1; k <= r2 - r + 1; k++)
        for (int l = k + r - 1; l <= r2; l++)
          if (l * j >= 3 * i * k) {
            front[0] = i;
            front[f - 1] = j;
            rear[0] = k;
            rear[r - 1] = l;
            SearchFront(1);
          }

  ofstream fout("cowcycle.out");
  for (int i = 0; i < f; i++) {
    if (i > 0) fout << ' ';
    fout << best_f[i];
  }
  fout << endl;
  for (int i = 0; i < r; i++) {
    if (i > 0) fout << ' ';
    fout << best_r[i];
  }
  fout << endl;
  fout.close();
  return 0;
}
