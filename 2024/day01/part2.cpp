#include <stdio.h>
#include <algorithm>
#include <math.h>

const int MAX_N = 1'000;
const int MAX_VAL = 99'999;

int freq1[MAX_VAL + 1], freq2[MAX_VAL + 1];

int main() {
  int x, y;
  while((scanf("%d%d", &x, &y)) == 2) {
    freq1[x]++;
    freq2[y]++;
  }

  int res = 0;
  for(int i = 0; i <= MAX_VAL; i++) {
    res += freq1[i] * i * freq2[i];
  }

  printf("%d\n", res);

  return 0;
}
