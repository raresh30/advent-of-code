#include <stdio.h>
#include <map>

using ll = long long;
const int MAX_N = 1'000'000;
const int STEPS = 75;

std::map<ll, ll> vals;
std::map<ll, ll> new_vals;

void read_array() {
  int x;
  while(scanf("%d", &x) == 1) {
    vals[x]++;
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

void get_new(ll x) {
  int nd = num_digits(x);
  if(x == 0) {
    new_vals[1] += vals[0];
  } else if(nd % 2 == 1) {
    new_vals[x * 2024] += vals[x];
  } else {
    ll p10 = half_p10(x, nd);
    new_vals[x / p10] += vals[x];
    new_vals[x % p10] += vals[x];
  }
}

int main() {
  read_array();
  for(int step = 0; step < STEPS; step++) {
    new_vals.clear();
    for(auto x : vals) {
      get_new(x.first);
    }
    std::swap(vals, new_vals);
  }
  ll res = 0;
  for(auto x : vals) {
    res += x.second;
  }
  printf("%lld\n", res);

  return 0;
}
