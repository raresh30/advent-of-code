#include <stdio.h>

const int MAX_N = 140;
const int MAX_M = 140;

int n, m;
char mat[MAX_N][MAX_M];

const int LEN = 4;
char xmas[] = "XMAS";

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

int count_orizontal() {
  int ret = 0;
  for(int l = 0; l < n; l++) {
    for(int c = 0; c <= m - LEN; c++) {
      if(mat[l][c] == xmas[0] &&
         mat[l][c + 1] == xmas[1] &&
         mat[l][c + 2] == xmas[2] &&
         mat[l][c + 3] == xmas[3]) {
        ret++;
      }

      if(mat[l][c] == xmas[3] &&
         mat[l][c + 1] == xmas[2] &&
         mat[l][c + 2] == xmas[1] &&
         mat[l][c + 3] == xmas[0]) {
        ret++;
      }
    }
  }
  return ret;
}

int count_vertical() {
  int ret = 0;
  for(int c = 0; c < m; c++) {
    for(int l = 0; l <= n - LEN; l++) {
      if(mat[l][c] == xmas[0] &&
         mat[l + 1][c] == xmas[1] &&
         mat[l + 2][c] == xmas[2] &&
         mat[l + 3][c] == xmas[3]) {
        ret++;
      }
      if(mat[l][c] == xmas[3] &&
         mat[l + 1][c] == xmas[2] &&
         mat[l + 2][c] == xmas[1] &&
         mat[l + 3][c] == xmas[0]) {
        ret++;
      }
    }
  }
  return ret;
}

int count_diagonal() {
  int ret = 0;

  for(int l = 0; l <= n - LEN; l++) {
    for(int c = 0; c <= m - LEN; c++) {
      if(mat[l][c] == xmas[0] &&
         mat[l + 1][c + 1] == xmas[1] &&
         mat[l + 2][c + 2] == xmas[2] &&
         mat[l + 3][c + 3] == xmas[3]) {
        ret++;
      }
      if(mat[l][c] == xmas[3] &&
         mat[l + 1][c + 1] == xmas[2] &&
         mat[l + 2][c + 2] == xmas[1] &&
         mat[l + 3][c + 3] == xmas[0]) {
        ret++;
      }
    }
  }

  for(int l = 0; l <= n - LEN; l++) {
    for(int c = LEN - 1; c < m; c++) {
      if(mat[l][c] == xmas[0] &&
         mat[l + 1][c - 1] == xmas[1] &&
         mat[l + 2][c - 2] == xmas[2] &&
         mat[l + 3][c - 3] == xmas[3]) {
        ret++;
      }
      if(mat[l][c] == xmas[3] &&
         mat[l + 1][c - 1] == xmas[2] &&
         mat[l + 2][c - 2] == xmas[1] &&
         mat[l + 3][c - 3] == xmas[0]) {
        ret++;
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

  int ans = count_vertical() + count_orizontal() + count_diagonal();
  printf("%d\n", ans);

  return 0;
}