/*
ID: liangyi1
PROG: job
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <queue>
using namespace std;

int n, m1, m2;
int a[30];
int b[30];
int times[1000];

void Greedy(ostream &out) {
  // Feed everything into a.
  int num[30] = {0};
  int total = 0;
  for (int i = 0; i < n; ++i) {
    int choose = 0;
    int min_time = (num[0] + 1) * a[0];
    for (int j = 1; j < m1; ++j) {
      if ((num[j] + 1) * a[j] < min_time) {
        min_time = (num[j] + 1) * a[j];
        choose = j;
      }
    }
    ++num[choose];
    times[total++] = num[choose] * a[choose];
  }
  int ans = a[0] * num[0];
  for (int i = 1; i < m1; ++i) {
    if (a[i] * num[i] > ans) ans = a[i] * num[i];
  }
  out << ans << ' ';
  // Feed everything into b, in the reverse order of arriving time.
  int waiting_time[30] = {0};
  int head_time[30] = {0};
  int max_amount = 0;
  memset(num, 0, sizeof(num));
  for (int i = n - 1; i >= 0; --i) {
    int k = -1;
    int min_amount, wait;
    for (int j = 0; j < m2; ++j) {
      int overall;
      int new_wait;
      if (head_time[j] == 0) {
        overall = times[i] + b[j];
        new_wait = 0;
      } else {
        overall = head_time[j] + num[j] * b[j];
        if (times[i] + b[j] <= head_time[j]) {
          overall += waiting_time[j];
          new_wait = waiting_time[j] + head_time[j] - times[i] - b[j];
        } else {
          if (times[i] + b[j] - head_time[j] >= waiting_time[j]) {
            overall += times[i] + b[j] - head_time[j];
            new_wait = 0;
          } else {
            new_wait = waiting_time[j] - (times[i] + b[j] - head_time[j]);
          }
        }
      }
      if (k == -1 || overall < min_amount) {
        min_amount = overall;
        wait = new_wait;
        k = j;
      }
    }
    // Update.
    head_time[k] = times[i];
    waiting_time[k] = wait;
    ++num[k];
    max_amount = max(max_amount, min_amount);
  }
  out << max_amount << endl;
}

int main() {
  ifstream fin("job.in");
  fin >> n >> m1 >> m2;
  for (int i = 0; i < m1; ++i) {
    fin >> a[i];
  }
  for (int i = 0; i < m2; ++i) {
    fin >> b[i];
  }
  fin.close();

  ofstream fout("job.out");
  Greedy(fout);
  fout.close();
  return 0;
}
