#include <stdio.h>
#include <ctype.h>

const int MAX_N = 8;

int n;
int v[MAX_N];
int conflicts[MAX_N];

int read_line() {
  char ch = fgetc(stdin);
  if(ch == EOF) {
    return 0;
  }
  n = 0;
  v[0] = 0;
  while(ch != '\n') {
    if(isdigit(ch)) {
      v[n] = v[n] * 10 + ch - '0';
    } else {
      n++;
      v[n] = 0;
    }
    ch = fgetc(stdin);
  }
  n++;
  return 1;
}

bool can_remove(int i, int sign) {
  if(i == 0 || i == n - 1) {
    return true;
  }
  return (v[i + 1] * sign > v[i - 1] * sign &&
          v[i + 1] * sign - v[i - 1] * sign <= 3);
}

bool is_safe(int sign) {
  for(int i = 0; i < n; i++) {
    conflicts[i] = 0;
  }

  int sum = 0;
  for(int i = 1; i < n; i++) {
    if(!(v[i] * sign > v[i - 1] * sign &&
         v[i] * sign - v[i - 1] * sign <= 3)) {
      conflicts[i]++;
      conflicts[i - 1]++;
      sum++;
    }
  }

  for(int i = 0; i < n; i++) {
    if(conflicts[i] >= sum && can_remove(i, sign)) {
      return true;
    }
  }
  return false;
}

int main() {
  int ans = 0;
  while(read_line()) {
    if(is_safe(1) || is_safe(-1)) {
      ans++;
    }
  }
  printf("%d\n", ans);

  return 0;
}
