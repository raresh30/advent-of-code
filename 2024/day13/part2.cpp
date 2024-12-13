#include <stdio.h>
#include <ctype.h>

using ll = __int128;
const int INF = 2'000'000'000;
const ll INCREMENT = 10'000'000'000'000LL;

struct Point {
  ll x, y;
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
  prize.x = read_int() + INCREMENT;
  prize.y = read_int() + INCREMENT;
  return 1;
}

int main() {
  ll res = 0;
  while(read_machine_info()) {
    ll denom = (b.x * a.y - b.y * a.x);
    if(denom != 0 &&
       (prize.x * a.y - prize.y * a.x) % denom == 0) {
      ll pb = (prize.x * a.y - prize.y * a.x) / denom;
      if((prize.x - pb * b.x) % a.x == 0) {
        ll pa = (prize.x - pb * b.x) / a.x;
        if(pa * a.x + pb * b.x == prize.x &&
           pa * a.y + pb * b.y == prize.y) {
          res += 3 * pa + pb;
        }
      }
    }
  }
  printf("%lld\n", (long long)res);
  
  return 0;
}