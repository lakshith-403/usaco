/*
ID: liangyi1
PROG: ttwo
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;

bool state[10][10][4][10][10][4];
bool obstacle[10][10];
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

void move(int *x, int *y, int *d) {
  int nx = *x + dx[*d];
  int ny = *y + dy[*d];
  if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 && !obstacle[nx][ny]) {
    *x = nx;
    *y = ny;
    return;
  }
  // Turn clockwise.
  *d = (*d + 1) % 4;
}

int main() {
  ifstream fin("ttwo.in");
  ofstream fout("ttwo.out");
  char c[11];
  int fx, fy, cx, cy;
  for (int i = 0; i < 10; ++i) {
    fin >> c;
    for (int j = 0; j < 10; ++j) {
      if (c[j] == 'F') {
        fx = i;
        fy = j;
      } else if (c[j] == 'C') {
        cx = i;
        cy = j;
      } else if (c[j] == '*') {
        obstacle[i][j] = true;
      }
    }
  }
  // Simulation.
  int fd = 3, cd = 3;
  int minutes = 0;
  state[fx][fy][fd][cx][cy][cd] = true;
  while (fx != cx || fy != cy) {
    ++minutes;
    move(&fx, &fy, &fd);
    move(&cx, &cy, &cd);
    if (state[fx][fy][fd][cx][cy][cd]) {
      break;
    } else {
      state[fx][fy][fd][cx][cy][cd] = true;
    }
  }
  if (fx == cx && fy == cy) {
    fout << minutes << endl;
  } else {
    fout << 0 << endl;
  }
  fin.close();
  fout.close();
  return 0;
}
