#include <stdio.h>

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

int find_chunk(int size, int max_pos) {
  int cnt = 0;
  for(int i = 0; i <= max_pos; i++) {
    if(blocks[i] == EMPTY) {
      cnt++;
    } else {
      cnt = 0;
    }

    if(cnt == size) {
      return i - size + 1;
    }
  }
  return -1;
}

void compress_blocks(int nb) {
  int r = nb - 1;
  while(r >= 0) {
    if(blocks[r] != EMPTY) {
      int id = blocks[r];
      int size = 0;
      while(r >= 0 && blocks[r] == id) {
        size++;
        r--;
      }
      int pos = find_chunk(size, r);
      if(pos > -1) {
        for(int i = pos; i < pos + size; i++) {
          blocks[i] = id;
        }
        for(int i = r + 1; i < r + 1 + size; i++) {
          blocks[i] = EMPTY;
        }
      }
    } else {
      r--;
    }
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
