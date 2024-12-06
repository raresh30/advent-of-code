#include <stdio.h>
#include <ctype.h>

const int MAX_N = 130;
const int MAX_M = 130;

const int BORDER = 0;
const int EMPTY = 1;
const int BLOCK = 2;

const int NDIR = 4;
int dlin[NDIR] = {-1, 0, 1, 0};
int dcol[NDIR] = {0, 1, 0, -1};

struct Point {
  int l, c;
};

int n, m;
Point guard;
int guard_dir;
char mat[MAX_N + 2][MAX_M + 2];
char vis[MAX_N + 2][MAX_M + 2][NDIR];

int read_line(int l) {
  char ch = fgetc(stdin);
  if(ch == EOF) {
    return 0;
  }

  m = 0;
  do {
    if(ch == '^' || ch == '>' || ch == 'v' || ch == '<') {
      if(ch == '^') {
        guard_dir = 0;
      } else if(ch == '>') {
        guard_dir = 1;
      } else if(ch == 'v') {
        guard_dir = 3;
      } else {
        guard_dir = 4;
      }
      guard = {l + 1, m + 1};
      ch = '.';
    }
    mat[l + 1][m + 1] = ch == '.' ? EMPTY : BLOCK;
    m++;
  } while(!isspace(ch = fgetc(stdin)));
  return 1;
}

void read_input() {
  n = 0;
  while(read_line(n)) {
    n++;
  }
}

int mark_points() {
  Point p = guard;
  int dir = guard_dir;
  int nl = p.l, nc = p.c;
  while(!vis[nl][nc][dir] && mat[nl][nc] != BORDER) {
    int l = nl, c = nc;
    vis[l][c][dir] = 1;
    nl = l + dlin[dir];
    nc = c + dcol[dir];
    while(mat[nl][nc] == BLOCK) {
      dir = (dir + 1) % NDIR;
      nl = l + dlin[dir];
      nc = c + dcol[dir];
    }
  }
  if(mat[nl][nc] == BORDER) {
    return 0;
  }
  return 1;
}

void reset_vis() {
  for(int l = 1; l <= n; l++) {
    for(int c = 1; c <= m; c++) {
      for(int d = 0; d < NDIR; d++) {
        vis[l][c][d] = 0;
      }
    }
  }
}

int main() {
  read_input();

  int res = 0;
  for(int l = 1; l <= n; l++) {
    for(int c = 1; c <= m; c++) {
      if(mat[l][c] == EMPTY && (l != guard.l || c != guard.c)) {
        mat[l][c] = BLOCK;
        reset_vis();
        int x = mark_points();
        res += x;
        mat[l][c] = EMPTY;
      }
    }
  }

  printf("%d\n", res);

  return 0;
}
