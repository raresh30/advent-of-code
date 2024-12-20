#include <stdio.h>
#include <ctype.h>
#include <queue>
#include <algorithm>

const int MAX_N = 141;
const int MAX_M = 141;
const int INF = 2'000'000'000;

const int MAX_CHEAT = 20;

const char WALL = '#';
const char EMPTY = '.';
const int IMPOSSIBLE = -1;

const int NDIR = 4;

int dlin[NDIR] = {-1, 0, 1, 0};
int dcol[NDIR] = {0, 1, 0, -1};

struct Point {
  int l, c;
};

int n, m;
char mat[MAX_N][MAX_M];
int dist[MAX_N][MAX_M];
Point start, end;
std::queue<Point> q;

int read_line() {
  char ch = fgetc(stdin);
  if(ch == EOF) {
    return 0;
  }
  m = 0;
  do {
    if(ch == 'S') {
      start = {n, m};
      ch = EMPTY;
    } else if(ch == 'E') {
      end = {n, m};
      ch = EMPTY;
    }
    mat[n][m++] = ch;
  } while(!isspace(ch = fgetc(stdin)));
  return 1;
}

void init_dist() {
  for(int l = 0; l < n; l++) {
    for(int c = 0; c < m; c++) {
      dist[l][c] = IMPOSSIBLE;
    }
  }
}

void compute_distances(Point x) {
  dist[x.l][x.c] = 0;
  q.push(x);
  while(!q.empty()) {
    Point p = q.front();
    q.pop();
    for(int dir = 0; dir < NDIR; dir++) {
      int nl = p.l + dlin[dir];
      int nc = p.c + dcol[dir];
      if(mat[nl][nc] == EMPTY && dist[nl][nc] == IMPOSSIBLE) {
        dist[nl][nc] = dist[p.l][p.c] + 1;
        q.push({nl, nc});
      }
    }
  }
}

int outside(int l, int c) {
  return l < 0 || c < 0 || l >= n || c >= m;
}

int res;
void compute_cheats(int l, int c) {
  for(int ll = std::max(0, l - MAX_CHEAT); ll <= std::min(n - 1, l + MAX_CHEAT); ll++) {
    int d = abs(ll - l);
    for(int cc = c - (MAX_CHEAT - d); cc <= c + (MAX_CHEAT - d); cc++) {
      if(!outside(ll, cc) && mat[ll][cc] != WALL && dist[ll][cc] != IMPOSSIBLE) {
        int cheat = abs(ll - l) + abs(cc - c);
        int time = cheat + dist[ll][cc] + (dist[start.l][start.c] - dist[l][c]);
        int save = dist[start.l][start.c] - time;
        if(save >= 100) {
          res++;
        }
      }
    }
  }
}

int main() {
  n = 0;
  while(read_line()) {
    n++;
  }
  init_dist();
  compute_distances(end);
  res = 0;
  for(int l = 0; l < n; l++) {
    for(int c = 0; c < m; c++) {
      if(mat[l][c] != WALL && dist[l][c] != IMPOSSIBLE) {
        compute_cheats(l, c);
      }
    }
  }
  printf("%d\n", res);

  return 0;
}