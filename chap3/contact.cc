/*
ID: liangyi1
PROG: contact
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

void Scan(const int a, const int b, const string& s, vector<int>* occurs) {
  for (int len = a; len <= min((string::size_type)b, s.size()); ++len) {
    unsigned prefix = 1 << len;
    // Get the first value.
    unsigned value = 0;
    int j;
    for (j = 0; j < len; ++j) {
      value = (value << 1) + (s[j] - '0');
    }
    ++(*occurs)[prefix + value];

    // Get the rest values.
    unsigned mark = (1 << len - 1) - 1;
    while (j < s.size()) {
      value = ((value & mark) << 1) + (s[j] - '0');
      ++(*occurs)[prefix + value];
      ++j;
    }
  }
}

bool compare(pair<int, int> p1, pair<int, int> p2) {
  if (p1.first == p2.first) {
    return p1.second < p2.second;
  } else {
    return p1.first > p2.first;
  }
}

string Decode(unsigned x) {
  string s;
  while (x != 1) {
    s.append(1, '0' + (x & 1));
    x >>= 1;
  }
  reverse(s.begin(), s.end());
  return s;
}

int main() {
  ifstream fin("contact.in");
  int a, b, n;
  string s, line;
  fin >> a >> b >> n;
  while (fin >> line) {
    s.append(line);
  }
  fin.close();

  vector<int> occurs(1 << b + 1);
  Scan(a, b, s, &occurs);
  vector<pair<int, int> > freq_pairs;
  for (int i = 0; i < occurs.size(); ++i) {
    if (occurs[i] != 0) {
      freq_pairs.push_back(make_pair(occurs[i], i));
    }
  }
  sort(freq_pairs.begin(), freq_pairs.end(), compare);
  
  // Output.
  ofstream fout("contact.out");
  int pos = 0, repeat;
  while (pos < freq_pairs.size()) {
    if (pos == 0 || freq_pairs[pos].first != freq_pairs[pos - 1].first) {
      if (pos > 0) {
        fout << endl;
      }
      if (--n < 0) {
        break;
      }
      repeat = 0;
      fout << freq_pairs[pos].first << endl;
      fout << Decode(freq_pairs[pos].second);
    } else {
      if (repeat == 5) {
        fout << endl << Decode(freq_pairs[pos].second);
        repeat = 0;
      } else {
        fout << ' ' << Decode(freq_pairs[pos].second);
        ++repeat;
      }
    }
    ++pos;
  }
  if (n >= 0) {
    fout << endl;
  }
  fout.close();
  return 0;
}
