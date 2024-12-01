#include <stdio.h>
#include <algorithm>
#include <math.h>

const int MAX_N = 1'000;

int a[MAX_N], b[MAX_N];

int main() {
  int x, y, n = 0;
  while((scanf("%d%d", &x, &y)) == 2) {
    a[n] = x;
    b[n] = y;
    n++;
  }

  std::sort(a, a + n);
  std::sort(b, b + n);

  int res = 0;
  for(int i = 0; i < n; i++) {
    res += abs(a[i] - b[i]);
  }

  printf("%d\n", res);

  return 0;
}