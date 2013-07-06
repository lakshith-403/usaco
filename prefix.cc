/*
ID: liangyi1
PROG: prefix
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Trie {
 public:
  Trie() {
    memset(child, 0, sizeof(child));
    end = false;
  }

  /* Delete the subtrees in destruction. */
  ~Trie() {
    for (int i = 0; i < 26; ++i) {
      if (child[i] != NULL) {
        delete child[i];
      }
    }
  }

  void Insert(string &s, int pos) {
    if (pos < s.length()) {
      if (child[s[pos] - 'A'] == NULL) {
        child[s[pos] - 'A'] = new Trie();
      }
      child[s[pos] - 'A']->Insert(s, pos + 1);
    } else {
      end = true;
    }
  }

  void Push(string& s, int pos, bool *prefix) {
    if (end) {
      prefix[pos - 1] = true;  // Pattern matched.
    }
    if (pos < s.length() && child[s[pos] - 'A'] != NULL) {
      // Go further if we can.
      child[s[pos] - 'A']->Push(s, pos + 1, prefix);
    }
  }

  int LongestPrefix(string &s) {
    int longest = 0;
    bool *prefix = new bool[s.length()];  // True means the prefix exists.
    memset(prefix, 0, sizeof(bool) * s.length());
    Push(s, 0, prefix);
    for (int i = 0; i < s.length(); ++i) {
      if (prefix[i]) {
        longest = i + 1;
        Push(s, i + 1, prefix);
      }
    }
    delete [] prefix;
    return longest;
  }

 private:
  Trie *child[26];
  bool end;
};

int main() {
  ifstream fin("prefix.in");
  ofstream fout("prefix.out");
  // Construct a prefix tree.
  string prefix;
  Trie t;
  while (1) {
    fin >> prefix;
    if (prefix == ".") break;
    t.Insert(prefix, 0);
  }
  // Computation.
  string s;
  string piece;
  while (fin >> piece) {
    s.append(piece);
  }
  fout << t.LongestPrefix(s) << endl;
  fin.close();
  fout.close();
  return 0;
}
