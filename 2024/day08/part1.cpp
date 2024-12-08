#include <stdio.h>
#include <ctype.h>

const int MAX_N = 1'000;
const int MAX_POINTS = 10'000;
const int MAXCH = 128;
const int NUM_FREQS = 62;

char ch2freq[MAXCH];
char freq_chars[NUM_FREQS + 1] =
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

struct Point {
  int l, c;
};

int n, m;
int num_points[NUM_FREQS];
Point points[NUM_FREQS][MAX_POINTS];
char vis[MAX_N][MAX_N];

void init_codes() {
  for(int i = 0; i < NUM_FREQS; i++) {
    ch2freq[(int)freq_chars[i]] = i;
  }
}

int read_line() {
  char ch = fgetc(stdin);
  if(ch == EOF) {
    return 0;
  }

  m = 0;
  do {
    if(ch != '.') {
      int f = ch2freq[(int)ch];
      points[f][num_points[f]++] = {n, m};
    }
    m++;
  } while(!isspace(ch = fgetc(stdin)));
  n++;

  return 1;
}

bool inside(Point x) {
  return x.l >= 0 && x.l < n && x.c >= 0 && x.c < m;
}

int main() {
  init_codes();
  n = 0;
  while(read_line());

  int res = 0;
  for(int f = 0; f < NUM_FREQS; f++) {
    for(int i = 0; i < num_points[f]; i++) {
      for(int j = 0; j < num_points[f]; j++) {
        if(i != j) {
          Point x = points[f][i];
          Point y = points[f][j];
          int dl = y.l - x.l,
              dc = y.c - x.c;
          Point antinode = {x.l + 2 * dl, x.c + 2 * dc};
          if(inside(antinode) && !vis[antinode.l][antinode.c]) {
            res++;
            vis[antinode.l][antinode.c] = 1;
          }
        }
      }
    }
  }

  printf("%d\n", res);

  return 0;
}