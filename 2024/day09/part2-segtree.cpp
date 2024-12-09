#include <stdio.h>
#include <algorithm>

const int MAX_LEN = 200'000;
const int MAX_BLOCKS = 9 * MAX_LEN;
const int EMPTY = -1;
const int MAX_ST_SIZE = (1 << 18);

struct SegTree {
  int n;
  int st[2 * MAX_ST_SIZE];

  void init(int n, int chunks[]) {
    this->n = (1 << (32 - __builtin_clz(n - 1)));
    for(int i = 0; i < n; i++) {
      st[i + this->n] = chunks[i];
    }
    for(int i = this->n - 1; i >= 0; i--) {
      st[i] = std::max(st[2 * i], st[2 * i + 1]);
    }
  }

  void shrink(int pos, int delta, int real_pos[]) {
    real_pos[pos] += delta;
    pos += n;
    st[pos] -= delta;
    pos /= 2;
    while(pos > 0) {
      st[pos] = std::max(st[2 * pos], st[2 * pos + 1]);
      pos /= 2;
    }
  }

  int allocate(int size) {
    int node = 1;
    int x = -1;
    while(node < n) {
      node = 2 * node;
      if(std::max(x, st[node]) < size) {
        x = std::max(x, st[node]);
        node++;
      }
    }
    if(std::max(x, st[node]) < size) {
      return -1;
    }
    return node - n;
  }
};

char data[MAX_LEN];
int blocks[MAX_BLOCKS];

int real_pos[MAX_LEN];
int chunks[MAX_LEN];
SegTree st;

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

void init_chunks(int nb) {
  int cnt = 0;
  int nch = 0;
  for(int i = 0; i < nb; i++) {
    if(blocks[i] == EMPTY) {
      cnt++;
    } else {
      if(cnt > 0) {
        real_pos[nch] = i - cnt;
        chunks[nch++] = cnt;
      }
      cnt = 0;
    }
  }
  if(cnt > 0) {
    real_pos[nch] = nb - cnt;
    chunks[nch++] = cnt;
  }

  st.init(nch, chunks);
}

int find_chunk(int size, int max_pos) {
  int pos = st.allocate(size);
  if(pos == -1 || real_pos[pos] > max_pos) {
    return -1;
  }
  int ret = real_pos[pos];
  st.shrink(pos, size, real_pos);
  return ret;
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
      ret += blocks[i] * (long long)i;
    }
  }
  return ret;
}

int main() {
  int n = read_line();
  int nb = compute_blocks(n);
  init_chunks(nb);
  compress_blocks(nb);
  long long sum = get_checksum(nb);
  printf("%lld\n", sum);
  
  return 0;
}
