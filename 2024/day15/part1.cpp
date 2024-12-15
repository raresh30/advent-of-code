#include <stdio.h>
#include <ctype.h>

const int MAX_N = 50;
const int MAX_M = 50;

const char ROBOT = '@';
const char BOX = 'O';
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

int read_line() {
  char ch = fgetc(stdin);
  if(ch == '\n') {
    return 0;
  }
  m = 0;
  do {
    if(ch == ROBOT) {
      robot_pos = {n, m};
    }
    mat[n][m++] = ch;
  } while(!isspace(ch = fgetc(stdin)));
  n++;
  return 1;
}

void move_robot(int dir) {
  int l = robot_pos.l, c = robot_pos.c;
  int k = 1;
  while(mat[l + k * dlin[dir]][c + k * dcol[dir]] == BOX) {
    k++;
  }
  if(mat[l + k * dlin[dir]][c + k * dcol[dir]] == EMPTY) {
    mat[l][c] = EMPTY;
    mat[l + k * dlin[dir]][c + k * dcol[dir]] = BOX;
    mat[l + dlin[dir]][c + dcol[dir]] = ROBOT;
    robot_pos = {l + dlin[dir], c + dcol[dir]};
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
      res += (mat[l][c] == BOX) * (100 * l + c);
    }
  }

  printf("%d\n", res);

  return 0;
}
