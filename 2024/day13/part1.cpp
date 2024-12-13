#include <stdio.h>
#include <ctype.h>

const int MAX_PRESS = 100;
const int INF = 2'000'000'000;

struct Point {
  int x, y;
};

Point a, b, prize;

int read_int() {
  char ch;
  while(!isdigit(ch = fgetc(stdin)));
  int ret = 0;
  do {
    ret = ret * 10 + ch - '0';
  } while(isdigit(ch = fgetc(stdin)));
  return ret;
}

int read_machine_info() {
  char ch = fgetc(stdin);
  if(ch == EOF) {
    return 0;
  }
  a.x = read_int();
  a.y = read_int();
  b.x = read_int();
  b.y = read_int();
  prize.x = read_int();
  prize.y = read_int();
  return 1;
}

int main() {
  int res = 0;
  while(read_machine_info()) {
    int min_price = INF;
    for(int pa = 0; pa <= 100; pa++) {
      for(int pb = 0; pb <= 100; pb++) {
        if(pa * a.x + pb * b.x == prize.x &&
           pa * a.y + pb * b.y == prize.y) {
          int price = 3 * pa + pb;
          if(price < min_price) {
            min_price = price;
          }
        }
      }
    }
    if(min_price != INF) {
      res += min_price;
    }
  }
  printf("%d\n", res);
  
  return 0;
}