#include <stdio.h>
#include <ctype.h>

const int MAX_N = 100;
const int BORDER = -1;
const int UNKNOWN = -1;
const int NDIR = 4;

int n, m;
char mat[MAX_N + 2][MAX_N + 2];
int cnt[MAX_N + 2][MAX_N + 2];

int dlin[NDIR] = {-1, 0, 1, 0};
int dcol[NDIR] = {0, 1, 0, -1};

int read_line() {
  char ch = fgetc(stdin);
  if(ch == EOF) {
    return 0;
  }

  m = 0;
  do {
    mat[n + 1][m + 1] = ch - '0';
    m++;
  } while(!isspace(ch = fgetc(stdin)));
  n++;

  return 1;
}

void init_border() {
  for(int l = 0; l <= n + 1; l++) {
    mat[l][0] = mat[l][m + 1] = BORDER;
  }
  for(int c = 0; c <= m + 1; c++) {
    mat[0][c] = mat[n + 1][c] = BORDER;
  }
}

void init_cnt() {
  for(int l = 1; l <= n; l++) {
    for(int c = 1; c <= m; c++) {
      cnt[l][c] = UNKNOWN;
    }
  }
}

int dfs(int l, int c, int x) {
  if(x == 9) {
    cnt[l][c] = 1;
  }
  if(cnt[l][c] != UNKNOWN) {
    return cnt[l][c];
  }
  int ret = 0;
  for(int dir = 0; dir < NDIR; dir++) {
    if(mat[l + dlin[dir]][c + dcol[dir]] == x + 1) {
      ret += dfs(l + dlin[dir], c + dcol[dir], x + 1);
    }
  }
  cnt[l][c] = ret;
  return ret;
}

int main() {
  n = 0;
  while(read_line());

  init_border();
  init_cnt();
  int sum = 0;
  for(int l = 1; l <= n; l++) {
    for(int c = 1; c <= m; c++) {
      if(mat[l][c] == 0) {
        sum += dfs(l, c, 0);
      }
    }
  }

  printf("%d\n", sum);

  return 0;
}
