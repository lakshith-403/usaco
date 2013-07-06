/*
ID: liangyi1
LANG: C++
TASK: milk2
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

bool comp(pair<int, int> a, pair<int, int> b) {
  return a.first <= b.first;
}

int main() {
  ifstream fin("milk2.in");
  ofstream fout("milk2.out");
  int n;
  vector< pair<int, int> > intervals;
  // Read data.
  fin >> n;
  for (int i = 0; i < n; i++) {
    int x, y;
    fin >> x >> y;
    intervals.push_back(make_pair(x, y));
  }
  // Sort the intervals by left end points.
  std::sort(intervals.begin(), intervals.end(), comp);
  // Final calculation.
  int max_busy = 0, max_idle = 0;
  int left = intervals[0].first, right = intervals[0].second;
  for (int i = 0; i < intervals.size(); i++) {
    if (intervals[i].first > right) {
      if (intervals[i].first - right > max_idle) {
        max_idle = intervals[i].first - right;
      }
      if (right - left > max_busy) {
        max_busy = right - left;
      }
      left = intervals[i].first;
      right = intervals[i].second;
    } else {
      if (intervals[i].second > right) {
        right = intervals[i].second;
      }
    }
  }
  // Last check for special case: 1 interval.
  if (right - left > max_busy) {
    max_busy = right - left;
  }
  fout << max_busy << ' ' << max_idle << endl;
  fin.close();
  fout.close();
  return 0;
}
