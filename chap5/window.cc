/*
ID: liangyi1
PROG: window
LANG: C++
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct Window {
  Window* prev, *next;
  int x1, y1, x2, y2;

  Window(): prev(NULL), next(NULL) {
  }
};

Window* w[128];  // Map.
Window* head, *tail;  // Linked list.

int ComputeArea(Window* pw, int x1, int y1, int x2, int y2) {
  if (!pw) return (x2 - x1) * (y2 - y1);
  int ret = 0;
  if (y2 > pw->y2) {
    ret += ComputeArea(pw->prev, x1, max(y1, pw->y2), x2, y2);
    y2 = pw->y2;
  }
  if (y1 < pw->y1) {
    ret += ComputeArea(pw->prev, x1, y1, x2, min(y2, pw->y1));
    y1 = pw->y1;
  }
  if (y1 < y2) {
    if (x1 < pw->x1)
      ret += ComputeArea(pw->prev, x1, y1, min(x2, pw->x1), y2);
    if (x2 > pw->x2)
      ret += ComputeArea(pw->prev, max(x1, pw->x2), y1, x2, y2);
  }
  return ret;
}

void Swap(int* a, int*b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int main() {
  ifstream fin("window.in");
  ofstream fout("window.out");
  fout.precision(3);
  fout << fixed;
  string cmd;
  char id;
  Window* pw;
  int area;
  while (fin >> cmd) {
    switch (cmd[0]) {
      case 'w':
        pw = new Window;
        sscanf(cmd.c_str(), "w(%c,%d,%d,%d,%d)", &id, &pw->x1, &pw->y1, &pw->x2,
            &pw->y2);
        if (pw->x1 > pw->x2) Swap(&pw->x1, &pw->x2);
        if (pw->y1 > pw->y2) Swap(&pw->y1, &pw->y2);
        w[id] = pw;
        // Insert to head.
        if (head) {
          head->prev = pw;
          pw->next = head;
          head = pw;
        } else {
          head = tail = pw;
        }
        break;
      case 't':
        id = cmd[2];
        pw = w[id];
        // Move to head.
        if (pw == head) {
        } else if (pw == tail) {
          if (pw->prev) {
            pw->prev->next = NULL;
            tail = pw->prev;
            head->prev = pw;
            pw->next = head;
            pw->prev = NULL;
            head = pw;
          }
        } else {
          pw->prev->next = pw->next;
          pw->next->prev = pw->prev;
          head->prev = pw;
          pw->next = head;
          pw->prev = NULL;
          head = pw;
        }
        break;
      case 'b':
        id = cmd[2];
        pw = w[id];
        // Move to tail.
        if (pw == head) {
          if (pw->next) {
            pw->next->prev = NULL;
            head = pw->next;
            tail->next = pw;
            pw->prev = tail;
            pw->next = NULL;
            tail = pw;
          }
        } else if (pw == tail) {
        } else {
          pw->prev->next = pw->next;
          pw->next->prev = pw->prev;
          tail->next = pw;
          pw->prev = tail;
          pw->next = NULL;
          tail = pw;
        }
        break;
      case 'd':
        id = cmd[2];
        pw = w[id];
        // Remove.
        if (pw == head) {
          if (pw->next) {
            pw->next->prev = NULL;
            head = pw->next;
          } else {
            head = tail = NULL;
          }
        } else if (pw == tail) {
          pw->prev->next = NULL;
          tail = pw->prev;
        } else {
          pw->prev->next = pw->next;
          pw->next->prev = pw->prev;
        }
        delete pw;
        w[id] = NULL;
        break;
      case 's':
        id = cmd[2];
        area = (w[id]->x2 - w[id]->x1) * (w[id]->y2 - w[id]->y1);
        fout << static_cast<double>(ComputeArea(w[id]->prev, w[id]->x1,
              w[id]->y1, w[id]->x2, w[id]->y2)) / area * 100 << endl;
        break;
    };
  }
  fin.close();
  fout.close();
  // Clean up.
  for (int i = 0; i < 128; i++)
    if (w[i]) delete w[i];
  return 0;
}
