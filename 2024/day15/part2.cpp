#include <stdio.h>
#include <ctype.h>

const int MAX_N = 50;
const int MAX_M = 100;

const char ROBOT = '@';
const char BOX = 'O';
const char BOX_LEFT = '[';
const char BOX_RIGHT = ']';
const char EMPTY = '.';
const char WALL = '#';

struct Point {
  int l, c;
};

int n, m;
char mat[MAX_N][MAX_M];
Point robot_pos;

const int NDIR = 4;
const int MAX_CH = 128;

char dir_codes[NDIR + 1] = "^>v<";
int dlin[NDIR] = {-1, 0, 1, 0};
int dcol[NDIR] = {0, 1, 0, -1};
char ch2dir[MAX_CH];

void print_board() {
  for(int l = 0; l < n; l++) {
    for(int c = 0; c < m; c++) {
      printf("%c", mat[l][c]);
    }
    printf("\n");
  }
  printf("\n");
}

int read_line() {
  char ch = fgetc(stdin);
  if(ch == '\n') {
    return 0;
  }
  m = 0;
  do {
    if(ch == BOX) {
      mat[n][m++] = BOX_LEFT;
      mat[n][m++] = BOX_RIGHT;
    } else if(ch == ROBOT) {
      robot_pos = {n, m};
      mat[n][m++] = ROBOT;
      mat[n][m++] = EMPTY;
    } else {
      mat[n][m++] = ch;
      mat[n][m++] = ch;
    }
  } while(!isspace(ch = fgetc(stdin)));
  n++;
  return 1;
}

void update_pos(int l, int c, int dir) {
  int nl = l + dlin[dir], nc = c + dcol[dir];
  mat[nl][nc] = ROBOT;
  mat[l][c] = EMPTY;
  robot_pos = {nl, nc};
}

void update_box(int l, int c, int dir) {
  int ll = l + dlin[dir];
  int cc = c + dcol[dir];
  mat[ll][cc] = BOX_LEFT;
  mat[ll][cc + 1] = BOX_RIGHT;
  mat[l][c] = mat[l][c + 1] = EMPTY;
}

void change_box(int l, int c, int dir) {
  int ll = l + dlin[dir];
  int cc = c + dcol[dir];
  if(mat[ll][cc] == BOX_LEFT) {
    change_box(ll, cc, dir);
  } else {
    if(mat[ll][cc] == BOX_RIGHT) {
      change_box(ll, cc - 1, dir);
    }
    if(mat[ll][cc + 1] == BOX_LEFT) {
      change_box(ll, cc + 1, dir);
    }
  }
  update_box(l, c, dir);
}

int move_box(int l, int c, int dir) {
  int ll = l + dlin[dir];
  int cc = c + dcol[dir];
  if(mat[ll][cc] == WALL || mat[ll][cc + 1] == WALL) {
    return 0;
  }
  if(mat[ll][cc] == EMPTY && mat[ll][cc + 1] == EMPTY) {
    return 1;
  }
  int x = 0;
  if(mat[ll][cc] == BOX_LEFT) {
    x = move_box(ll, cc, dir);
  } else {
    x = 1;
    if(mat[ll][cc] == BOX_RIGHT) {
      x &= move_box(ll, cc - 1, dir);
    }
    if(mat[ll][cc + 1] == BOX_LEFT) {
      x &= move_box(ll, cc + 1, dir);
    }
  }
  return x;
}

void move_robot(int dir) {
  int l = robot_pos.l, c = robot_pos.c;
  int nl = l + dlin[dir], nc = c + dcol[dir];

  if(dir % 2 == 0) { // up down
    int x = 0;
    if(mat[nl][nc] == BOX_LEFT) {
      x = move_box(nl, nc, dir);
    } else if(mat[nl][nc] == BOX_RIGHT) {
      x = move_box(nl, nc - 1, dir);
    } else if(mat[nl][nc] == EMPTY) {
      x = 1;
    }
    if(x > 0) {
      if(mat[nl][nc] == BOX_LEFT) {
        change_box(nl, nc, dir);
      } else if(mat[nl][nc] == BOX_RIGHT) {
        change_box(nl, nc - 1, dir);
      }
      mat[nl][nc] = ROBOT;
      mat[l][c] = EMPTY;
      robot_pos = {nl, nc};
    }
  } else {
    int k = 1;
    int cc = c + 2 * k * dcol[dir];
    while((dir == 1 && 
           mat[l][cc] == BOX_RIGHT) ||
          (dir == 3 &&
           mat[l][cc] == BOX_LEFT)) {
      k++;
      cc = c + 2 * k * dcol[dir];
    }
    cc -= dcol[dir];
    if(mat[l][cc] == EMPTY) {
      for(int col = cc; col != c; col -= dcol[dir]) {
        mat[l][col] = mat[l][col - dcol[dir]];
      }
      robot_pos.c += dcol[dir];
      mat[l][c] = EMPTY;
    }
  }
}

int main() {
  n = 0;
  while(read_line());

  for(int i = 0; i < NDIR; i++) {
    ch2dir[(int)dir_codes[i]] = i;
  }

  char ch;
  while((ch = fgetc(stdin)) != EOF) {
    if(ch != '\n') {
      move_robot(ch2dir[(int)ch]);
    }
  }

  int res = 0;
  for(int l = 1; l < n - 1; l++) {
    for(int c = 1; c < m - 1; c++) {
      res += (mat[l][c] == BOX_LEFT) * (100 * l + c);
    }
  }

  printf("%d\n", res);

  return 0;
}
