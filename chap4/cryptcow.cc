/*
ID: liangyi1
PROG: cryptcow
LANG: C++
*/
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

char ans[] = "Begin the Escape execution at the Break of Dawn";
int len_ans = strlen(ans);
int profile_ans[128];
int steps;
char s[10][50];
int num_piece;
char piece[30][80];
int piece_len[30];

// Simple hashtable for char arrays.
class Table {
  public:
    Table(int size): size_(size) {
      table_ = new Entry*[size];
    }

    bool Find(char *p, int len) {
      unsigned int h = Hashcode(p, len) % size_;
      Entry *e = table_[h];
      while (e) {
        if (memcmp(p, e->pc, len) == 0) return true;
        e = e->next;
      }
      return false;
    }

    void Insert(char *p, int len) {
      ++num_entries;
      int h = Hashcode(p, len) % size_;
      Entry *e = new Entry;
      e->pc = new char[len];
      memcpy(e->pc, p, len);
      e->next = table_[h];
      table_[h] = e;
    }

    ~Table() {
      for (int i = 0; i < size_; ++i) {
        if (table_[i]) {
          Entry* e = table_[i];
          while (e) {
            delete e->pc;
            Entry* next = e->next;
            delete e;
            e = next;
          }
        }
      }
      delete [] table_;
    }

    int num_entries;
  private:
    struct Entry {
      char *pc;
      Entry* next;
    };

    unsigned int Hashcode(char *p, int len) {
      unsigned int h = 0;
      for (int i = 0; i < len; ++i) h = 31 * h + p[i];
      return h;
    }

    int size_;
    Entry** table_;
};

Table substring_table(1000);
Table search_table(77777);

int buffer_size;
char buffer[80];

bool Search(int p, int len, int l, int r) {
  char *pc;
  if (p == steps) {
    for (int i = 0; i < len; ++i) {
      pc = piece[s[p][i]];
      while (*pc) {
        if (*pc++ != ans[l++]) return false;
      }
    }
    return true;
  }
  int fc = 0, lw = len - 1;
  // Before the first 'C'.
  for (fc = 0; s[p][fc] != 'C'; ++fc) {
    if (s[p][fc] == 'O' || s[p][fc] == 'W') return false;
    pc = piece[s[p][fc]];
    while (*pc) {
      if (*pc != ans[l]) return false;
      ++pc;
      ++l;
    }
  }
  // After the last 'W'.
  for (lw = len - 1; s[p][lw] != 'W'; --lw) {
    if (s[p][lw] == 'C' || s[p][lw] == 'O') return false;
    pc = piece[s[p][lw]] + piece_len[s[p][lw]] - 1;
    while (pc >= piece[s[p][lw]]) {
      if (*pc != ans[r]) return false;
      --pc;
      --r;
    }
  }
  // Substring examiniation.
  pc = NULL;
  for (int i = fc; i <= lw; ++i) {
    if (s[p][i] != 'C' && s[p][i] != 'O' && s[p][i] != 'W') {
      if (pc == NULL) pc = s[p] + i;
    } else {
      if (pc != NULL) {
        // Concatenate and compare.
        buffer_size = 0;
        while (pc < s[p] + i) {
          memcpy(buffer + buffer_size, piece[*pc], piece_len[*pc]);
          buffer_size += piece_len[*pc];
          ++pc;
        }
        if (!substring_table.Find(buffer, buffer_size)) return false;
        pc = NULL;
      }
    }
  }
  // Overall repetition.
  if (search_table.Find(s[p], len)) {
    return false;
  } else {
    search_table.Insert(s[p], len);
  }
  for (int i = fc; i < lw; ++i) {
    if (s[p][i] != 'C') continue;
    for (int j = i + 1; j < lw; ++j) {
      if (s[p][j] != 'O') continue;
      for (int k = j + 1; k <= lw; ++k) {
        if (s[p][k] != 'W') continue;
        // Copy and search.
        pc = s[p + 1];
        for (int l = fc; l < i; ++l) *pc++ = s[p][l];
        for (int l = j + 1; l < k; ++l) *pc++ = s[p][l];
        for (int l = i + 1; l < j; ++l) *pc++ = s[p][l];
        for (int l = k + 1; l <= lw; ++l) *pc++ = s[p][l];
        if (Search(p + 1, lw - fc - 2, l, r)) return true;
      }
    }
  }
  return false;
}

int main() {
  // Put the answer substrings into hash table.
  for (int i = 0; i < len_ans; ++i) {
    for (int j = i; j < len_ans; ++j) {
      if (!substring_table.Find(ans + i, j - i + 1)) {
        substring_table.Insert(ans + i, j - i + 1);
      }
    }
  }

  ifstream fin("cryptcow.in");
  string line;
  getline(fin, line);
  fin.close();

  // Cut into pieces.
  char *pc = NULL;
  int len = 0;
  memset(piece, 0, sizeof(piece));
  for (int i = 0; i < line.size(); ++i) {
    if (line[i] != 'C' && line[i] != 'O' && line[i] != 'W') {
      if (!pc) pc = &line[i];
    } else {
      if (pc) {
        strncpy(piece[num_piece], pc, &line[i] - pc);
        piece_len[num_piece] = &line[i] - pc;
        s[0][len++] = num_piece;
        ++num_piece;
        pc = NULL;
      }
      s[0][len++] = line[i];
    }
  }
  if (pc) {
    piece_len[num_piece] = &line[line.size() - 1] - pc + 1;
    strncpy(piece[num_piece], pc, piece_len[num_piece]);
    s[0][len++] = num_piece;
    ++num_piece;
  }

  ofstream fout("cryptcow.out");
  if (line.size() >= len_ans && (line.size() - len_ans) % 3 != 0) {
    fout << 0 << ' ' << 0 << endl;
  } else {
    steps = (line.size() - len_ans) / 3;
    // Check the number of "COW"s.
    int nc = 0, no = 0, nw = 0;
    for (int i = 0; i < line.size(); ++i) {
      if (line[i] == 'C') ++nc;
      if (line[i] == 'O') ++no;
      if (line[i] == 'W') ++nw;
    }
    if (nc != steps || no != steps || nw != steps) {
      fout << 0 << ' ' << 0 << endl;
    } else {
      // Compare the letter profile.
      for (int i = 0; i < len_ans; ++i) ++profile_ans[ans[i]];
      int profile[128] = {0};
      for (int i = 0; i < line.size(); ++i) {
        if (line[i] != 'C' && line[i] != 'O' && line[i] != 'W') {
          ++profile[line[i]];
        }
      }
      if (memcmp(profile_ans, profile, sizeof(profile)) != 0) {
        fout << 0 << ' ' << 0 << endl;
      } else {
        if (Search(0, len, 0, len_ans - 1)) {
          fout << 1 << ' ' << steps << endl;
        } else {
          fout << 0 << ' ' << 0 << endl;
        }
      }
    }
  }
  fout.close();

  return 0;
}
