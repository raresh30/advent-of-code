#include <stdio.h>
#include <ctype.h>

const int MAX_N = 20;
long long num;
int n;
int a[MAX_N];

int read_op() {
  char ch = fgetc(stdin);
  if(ch == EOF) {
    return 0;
  }
  num = ch - '0';
  while(isdigit(ch = fgetc(stdin))) {
    num = num * 10 + ch - '0';
  }
  n = 0;
  ch = fgetc(stdin);
  while(ch == ' ') {
    a[n] = 0;
    while(isdigit(ch = fgetc(stdin))) {
      a[n] = a[n] * 10 + ch - '0';
    }
    n++;
  }

  return 1;
}

long long cat(long long a, long long b, long long limit) {
  long long p10 = 1;
  long long cb = b;
  while(cb > 0) {
    p10 *= 10;
    cb /= 10;
  }
  __int128 ret = a * p10 + b;
  if(ret > limit) {
    return limit + 1;
  }
  return (long long)ret;
}

bool bkt(int pos, long long sum) {
  if(sum > num) {
    return false;
  }

  if(pos >= n) {
    return (sum == num);
  } else {
    return bkt(pos + 1, sum + a[pos]) ||
           bkt(pos + 1, sum * a[pos]) ||
           bkt(pos + 1, cat(sum, a[pos], num));
  }
}

bool can_obtain() {
  return bkt(1, a[0]);
}

int main() {
  long long res = 0;
  while(read_op()) {
    if(can_obtain()) {
      res += num;
    }
  }
  printf("%lld\n", res);

  return 0;
}