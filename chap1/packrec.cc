/*
ID: liangyi1
LANG: C++
TASK: packrec
*/

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Rect {
  int w, h;
} rects[4];

const int fact[4] = {1, 1, 2, 6};

void GetPermutation(Rect *r, int perm) {
  bool used[4];
  memset(used, 0, sizeof(used));
  for (int i = 3; i >= 0; i--) {
    int count = perm / fact[i];
    perm %= fact[i];
    for (int j = 0; j < 4; j++) {
      if (!used[j] && count == 0) {
        r[i] = rects[j];
        used[j] = true;
        break;
      } else if (!used[j]) {
        --count;
      }
    }
  }
}

void Update(int width, int height, int *ans, vector<int> *factors) {
  if (width * height < *ans || *ans == -1) {
    *ans = width * height;
    factors->clear();
    factors->push_back(min(width, height));
  } else if (width * height == *ans) {
    factors->push_back(min(width, height));
  }
}

void ApplyLayout1(Rect *r, int *ans, vector<int> *factors) {
  int width = r[0].w + r[1].w + r[2].w + r[3].w;
  int height = max(max(r[0].h, r[1].h), max(r[2].h, r[3].h));
  Update(width, height, ans, factors);
}

void ApplyLayout2(Rect *r, int *ans, vector<int> *factors) {
  int height = max(max(r[0].h, r[1].h), r[2].h) + r[3].w;
  int width = max(r[3].h, r[0].w + r[1].w + r[2].w);
  Update(width, height, ans, factors);
}

void ApplyLayout3(Rect *r, int *ans, vector<int> *factors) {
  int width = max(r[0].w + r[1].w, r[2].h) + r[3].w;
  int height = max(max(r[0].h, r[1].h) + r[2].w, r[3].h);
  Update(width, height, ans, factors);
}

void ApplyLayout4(Rect *r, int *ans, vector<int> *factors) {
  int width = r[0].w + max(r[1].w, r[2].w) + r[3].w;
  int height = max(r[0].h, max(r[1].h + r[2].h, r[3].h));
  Update(width, height, ans, factors);
}

void ApplyLayout5(Rect *r, int *ans, vector<int> *factors) {
  int width = max(r[0].w, r[1].w) + r[2].w + r[3].w;
  int height = max(r[0].h + r[1].h, max(r[2].h, r[3].h));
  Update(width, height, ans, factors);
}

void ApplyLayout6(Rect *r, int *ans, vector<int> *factors) {
  int width, height;
  height = max(r[0].h + r[1].h, r[2].h + r[3].w);
  width = r[1].w + r[2].w;
  // Many cases for different widths of the upper part.
  if (r[0].h + r[1].h <= r[2].h) {
    if (r[0].w <= r[1].w) {
      width = max(width, r[3].h);
    } else {
      width = max(r[0].w + r[2].w, r[3].h);
    }
  } else if (r[2].h > r[1].h) {
    if (r[3].h > r[2].w) {
      width = max(width, r[3].h + r[0].w);    
    } else {
      width = max(width, r[2].w + r[0].w);
    }
  } else {
    width = max(r[0].w, r[1].w) + max(r[2].w, r[3].h);
  }
  Update(width, height, ans, factors);
}

int main() {
  ifstream fin("packrec.in");
  ofstream fout("packrec.out");
  for (int i = 0; i < 4; i++) {
    fin >> rects[i].w >> rects[i].h;
  }
  int ans = -1;
  vector<int> factors;
  // Enumerate all permutations.
  for (int i = 0; i < 24; i++) {
    Rect r1[4];
    GetPermutation(r1, i);
    // Enumerate the position of each rectangle.
    for (int j = 0; j < 16; j++) {
      int pos = j;
      Rect r2[4];
      memcpy(r2, r1, sizeof(r1));
      for (int k = 0; k < 4; k++) {
        if (pos % 2 != 0) {
          int temp = r2[k].w;
          r2[k].w = r2[k].h;
          r2[k].h = temp;
        }
        pos /= 2;
      }
      // Apply the six basic layouts.
      ApplyLayout1(r2, &ans, &factors);
      ApplyLayout2(r2, &ans, &factors);
      ApplyLayout3(r2, &ans, &factors);
      ApplyLayout4(r2, &ans, &factors);
      ApplyLayout5(r2, &ans, &factors);
      ApplyLayout6(r2, &ans, &factors);
    }
  }
  fout << ans << endl;
  sort(factors.begin(), factors.end());
  vector<int>::iterator it = unique(factors.begin(), factors.end());
  factors.resize(it - factors.begin());
  for (int i = 0; i < factors.size(); i++) {
    fout << factors[i] << ' ' << ans / factors[i] << endl;
  }
  fin.close();
  fout.close();
  return 0;
}
