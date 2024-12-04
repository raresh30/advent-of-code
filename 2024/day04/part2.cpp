#include <stdio.h>

const int MAX_N = 140;
const int MAX_M = 140;

int n, m;
char mat[MAX_N][MAX_M];

int read_line() {
  char ch;
  int cnt = 0;
  while((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    mat[n][cnt++] = ch;
  }

  if(ch == EOF) {
    return 0;
  }
  m = cnt;
  return 1;
}

int is_xmas(int l, int c) {
  if(mat[l - 1][c - 1] == 'M' && mat[l + 1][c + 1] == 'S' &&
     mat[l - 1][c + 1] == 'M' && mat[l + 1][c - 1] == 'S') {
    return 1;
  }
  if(mat[l - 1][c - 1] == 'S' && mat[l + 1][c + 1] == 'M' &&
     mat[l - 1][c + 1] == 'M' && mat[l + 1][c - 1] == 'S') {
    return 1;
  }
  if(mat[l - 1][c - 1] == 'M' && mat[l + 1][c + 1] == 'S' &&
     mat[l - 1][c + 1] == 'S' && mat[l + 1][c - 1] == 'M') {
    return 1;
  }
  if(mat[l - 1][c - 1] == 'S' && mat[l + 1][c + 1] == 'M' &&
     mat[l - 1][c + 1] == 'S' && mat[l + 1][c - 1] == 'M') {
    return 1;
  }
  return 0;
}

int count() {
  int ret = 0;
  for(int l = 1; l < n - 1; l++) {
    for(int c = 1; c < m - 1; c++) {
      if(mat[l][c] == 'A') {
        ret += is_xmas(l, c);
      }
    }
  }
  return ret;
}

int main() {
  n = 0;
  while(read_line()) {
    n++;
  }

  int ans = count();
  printf("%d\n", ans);

  return 0;
}
