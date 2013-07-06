/*
ID: liangyi1
PROG: lgame
LANG: C++
*/
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> dict;
const int score[26] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2,
  1, 2, 4, 6, 6, 7, 5, 7};

int best_score = 0;
vector< pair<string, string> > solutions;

int len;
char perm[8];

void UpdateSolutions() {
  string s;
  for (int i = 1; i <= len; i++) {
    int len1 = i;
    while (len1 > 0) {
      s.assign(perm, len1);
      if (binary_search(dict.begin(), dict.end(), s))
        break;
      len1--;
    }
    int len2 = len - i;
    while (len2 > 0) {
      s.assign(perm + i, len2);
      if (binary_search(dict.begin(), dict.end(), s))
        break;
      len2--;
    }
    int score1 = 0;
    for (int j = 0; j < len1; j++)
      score1 += score[perm[j] - 'a'];
    int score2 = 0;
    for (int j = 0; j < len2; j++)
      score2 += score[perm[i + j] - 'a'];
    if (score1 + score2 >= best_score) {
      if (score1 + score2 > best_score) {
        best_score = score1 + score2;
        solutions.clear();
      }
      // Append the new solution.
      if (score1 == 0) {
        solutions.push_back(make_pair(string(perm + i, len2), ""));
      } else if (score2 == 0) {
        solutions.push_back(make_pair(string(perm, len1), ""));
      } else {
        solutions.push_back(make_pair(string(perm, len1),
              string(perm + i, len2)));
      }
    }
  }
}

void GenPerm(int pos) {
  if (pos == len) {
    UpdateSolutions();
  } else {
    for (int i = pos; i < len; i++) {
      int temp;
      // Swap.
      temp = perm[pos];
      perm[pos] = perm[i];
      perm[i] = temp;
      GenPerm(pos + 1);
      // Swap back.
      temp = perm[pos];
      perm[pos] = perm[i];
      perm[i] = temp;
    }
  }
}

int main() {
  // Load dictionary.
  ifstream fin("lgame.dict");
  string s;
  while (fin >> s) {
    if (s == ".") break;
    dict.push_back(s);
  }
  fin.close();

  fin.open("lgame.in");
  fin >> perm;
  fin.close();
  
  // Enumeration.
  len = strlen(perm);
  GenPerm(0);

  // Sort and unique and output.
  sort(solutions.begin(), solutions.end());
  vector< pair<string, string> >::iterator end;
  end = unique(solutions.begin(), solutions.end());
  ofstream fout("lgame.out");
  fout << best_score << endl;
  for (vector< pair<string, string> >::iterator it = solutions.begin();
      it != end; it++) {
    if (it->second == "")
      fout << it->first << endl;
    else {
      if (it->first <= it->second)
        fout << it->first << ' ' << it->second << endl;
    }
  }
  fout.close();
  return 0;
}
