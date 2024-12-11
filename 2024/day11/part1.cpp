#include <stdio.h>

using ll = long long;
const int MAX_N = 1'000'000;
const int STEPS = 25;

int n;
ll v[MAX_N];

void read_array() {
  n = 0;
  int x;
  while(scanf("%d", &x) == 1) {
    v[n] = x;
    n++;
  }
}

ll half_p10(ll x, int nd) {
  ll ret = 1;
  for(int i = 0; i < nd / 2; i++) {
    ret *= 10;
  }
  return ret;
}

int num_digits(ll x) {
  int ret = 0;
  while(x > 0) {
    ret++;
    x /= 10;
  }
  return ret;
}

int main() {
  read_array();
  for(int step = 0; step < STEPS; step++) {
    int nn = n;
    for(int i = 0; i < n; i++) {
      int nd = num_digits(v[i]);
      if(v[i] == 0) {
        v[i] = 1;
      } else if(nd % 2 == 1) {
        v[i] *= 2024;
      } else {
        ll x = v[i];
        ll p10 = half_p10(x, nd);
        v[i] = x / p10;
        v[nn++] = x % p10;
      }
    }
    n = nn;
  }
  printf("%d\n", n);

  return 0;
}