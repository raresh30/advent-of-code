#include <stdio.h>
#include <ctype.h>

struct Robot {
  int x, y, dx, dy;
};

const int SIZE_X = 101;
const int SIZE_Y = 103;
const int STEPS = 100;

const int MAX_ROBOTS = 1'000;

const int QUADRANTS = 4;
const int X_DIFF[QUADRANTS] = {0, 1, 0, 1};
const int Y_DIFF[QUADRANTS] = {0, 0, 1, 1};

Robot r[MAX_ROBOTS];

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

int count_robots(int n, int q) {
  int xs = X_DIFF[q] * (SIZE_X + 1) / 2;
  int ys = Y_DIFF[q] * (SIZE_Y + 1) / 2;
  int xf = xs + (SIZE_X / 2) - 1;
  int yf = ys + (SIZE_Y / 2) - 1;
  
  int ret = 0;
  for(int i = 0; i < n; i++) {
    if(r[i].x >= xs && r[i].x <= xf &&
       r[i].y >= ys && r[i].y <= yf) {
      ret++;
    }
  }
  return ret;
}

int main() {
  int n = 0;
  while(read_robot(n)) {
    n++;
  }
  for(int i = 0; i < STEPS; i++) {
    for(int j = 0; j < n; j++) {
      move_robot(r[j]);
    }
  }
  int res = 1;
  for(int q = 0; q < QUADRANTS; q++) {
    int x = count_robots(n, q);
    res *= x;
  }
  printf("%d\n", res);

  return 0;
}
