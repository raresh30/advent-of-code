#include <stdio.h>
#include <string.h>

const int MAX_N = 140;
const int MAX_M = 140;
const char BORDER = '#';

const int NDIR = 4;
int dlin[NDIR] = {-1, 0, 1, 0};
int dcol[NDIR] = {0, 1, 0, -1};

struct Region {
  int area, perimeter;
};

int n, m;
char mat[MAX_N + 2][MAX_M + 2];
char vis[MAX_N + 2][MAX_M + 2];

void read_input() {
  n = 0;
  while(scanf("%s", (mat[n + 1] + 1)) == 1) {
    n++;
  }
  m = strlen(mat[1] + 1);
}

void init_border() {
  for(int l = 0; l <= n; l++) {
    mat[l][0] = mat[l][m + 1] = BORDER;
  }
  for(int c = 0; c <= m; c++) {
    mat[0][c] = mat[n + 1][c] = BORDER;
  }
}

Region fill(int l, int c, char type) {
  vis[l][c] = 1;
  Region ret = {1, 0};
  for(int dir = 0; dir < NDIR; dir++) {
    int nl = l + dlin[dir];
    int nc = c + dcol[dir];
    if(mat[nl][nc] == type && !vis[nl][nc]) {
      Region x = fill(nl, nc, type);
      ret.area += x.area;
      ret.perimeter += x.perimeter;
    };
    ret.perimeter += (mat[nl][nc] != type);
  }
  return ret;
}

int main() {
  read_input();
  init_border();
  int res = 0;
  for(int l = 1; l <= n; l++) {
    for(int c = 1; c <= m; c++) {
      if(!vis[l][c]) {
        Region x = fill(l, c, mat[l][c]);
        res += x.area * x.perimeter;
      }
    }
  }
  printf("%d\n", res);

  return 0;
}
