#include <stdio.h>
#include <ctype.h>

struct Robot {
  int x, y, dx, dy;
};

const int EASTER_EGG = 40;
const int SIZE_X = 101;
const int SIZE_Y = 103;

const int MAX_ROBOTS = 1'000;

const int NDIR = 4;
const int X_DIFF[NDIR] = {0, 1, 0, -1};
const int Y_DIFF[NDIR] = {-1, 0, 1, 0};

Robot r[MAX_ROBOTS];
char mat[SIZE_X][SIZE_Y];

int read_int() {
  char ch;
  while(!isdigit(ch = fgetc(stdin)) && ch != '-');
  int sign;
  if(ch == '-') {
    sign = -1;
    ch = fgetc(stdin);
  } else {
    sign = 1;
  }
  int ret = 0;
  do {
    ret = ret * 10 + ch - '0';
  } while(isdigit(ch = fgetc(stdin)));
  return sign * ret;
}

int read_robot(int i) {
  char ch = fgetc(stdin);
  if(ch == EOF) {
    return 0;
  }
  r[i].x = read_int();
  r[i].y = read_int();
  r[i].dx = read_int();
  r[i].dy = read_int();
  return 1;
}

void move_robot(Robot &rob) {
  rob.x = (rob.x + rob.dx + SIZE_X) % SIZE_X;
  rob.y = (rob.y + rob.dy + SIZE_Y) % SIZE_Y;
}

int inside(int x, int y) {
  return x >= 0 && x < SIZE_X && y >= 0 && y < SIZE_Y;
}

int dfs(int x, int y) {
  mat[x][y] = 0;
  int ret = 1;
  for(int dir = 0; dir < NDIR; dir++) {
    int nx = x + X_DIFF[dir];
    int ny = y + Y_DIFF[dir];
    if(inside(nx, ny) && mat[nx][ny] == 1) {
      ret += dfs(nx, ny);
    }
  }
  return ret;
}

int max_region(int n) {
  for(int i = 0; i < n; i++) {
    mat[r[i].x][r[i].y] = 1;
  }
  
  int ret = -1;
  for(int x = 0; x < SIZE_X; x++) {
    for(int y = 0; y < SIZE_Y; y++) {
      if(mat[x][y] == 1) {
        int size = dfs(x, y);
        if(size > ret) {
          ret = size;
        }
      }
    }
  }
  return ret;
}

int main() {
  int n = 0;
  while(read_robot(n)) {
    n++;
  }
  int i = 0;
  while(max_region(n) < EASTER_EGG) {
    for(int j = 0; j < n; j++) {
      move_robot(r[j]);
    }
    i++;
  }
  printf("%d\n", i);

  return 0;
}
