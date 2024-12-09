#include <stdio.h>
#include <algorithm>

const int MAX_LEN = 20'000;
const int MAX_BLOCKS = 9 * MAX_LEN;
const int EMPTY = -1;

char data[MAX_LEN];
short blocks[MAX_BLOCKS];

int read_line() {
  int n = 0;
  char ch;
  while((ch = fgetc(stdin)) != '\n') {
    data[n++] = ch - '0';
  }
  return n;
}

int compute_blocks(int len) {
  int nb = 0;
  for(int i = 0; i < len; i++) {
    for(int j = 0; j < data[i]; j++) {
      blocks[nb++] = (i % 2 == 0) ? (i / 2) : EMPTY;
    }
  }
  return nb;
}

void update_right(int &r) {
  while(r >= 0 && blocks[r] == EMPTY) {
    r--;
  }
}

void update_left(int &l, int r) {
  while(l <= r && blocks[l] != EMPTY) {
    l++;
  }
}

void compress_blocks(int nb) {
  int l = 0, r = nb - 1;
  update_right(r);
  update_left(l, r);
  while(r > l) {
    std::swap(blocks[l], blocks[r]);
    update_right(r);
    update_left(l, r);
  }
}

long long get_checksum(int nb) {
  long long ret = 0;
  for(int i = 0; i < nb; i++) {
    if(blocks[i] != EMPTY) {
      ret += blocks[i] * i;
    }
  }
  return ret;
}

int main() {
  int n = read_line();
  int nb = compute_blocks(n);
  compress_blocks(nb);
  long long sum = get_checksum(nb);
  printf("%lld\n", sum);
  
  return 0;
}