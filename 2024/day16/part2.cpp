#include <stdio.h>
#include <ctype.h>
#include <queue>

const char WALL = '#';
const char EMPTY = '.';
const int MAX_N = 141;
const int MAX_M = 141;
const int INF = 2'000'000'000;

const int TURN_COST = 1'000;

const int NDIR = 4;
int dlin[NDIR] = {-1, 0, 1, 0};
int dcol[NDIR] = {0, 1, 0, -1};

struct Point {
  int l, c;
};

struct State {
  int l, c, dir, points;
};

struct Pos {
  int l, c, dir;
};

int min_points[MAX_N][MAX_M][NDIR];
int n, m;
Point start, end;
char mat[MAX_N][MAX_M];
char mark[MAX_N][MAX_M];
std::priority_queue<State> pq;

std::vector<int> prev[MAX_N][MAX_M][NDIR];
std::queue<Pos> q;

bool operator<(const State &a, const State &b) {
  return min_points[a.l][a.c][a.dir] > min_points[b.l][b.c][b.dir];
}

void dijkstra() {
  pq.push({start.l, start.c, 1, 1});
  min_points[start.l][start.c][1] = 1;
  while(!pq.empty()) {
    State top = pq.top();
    pq.pop();
    int l = top.l;
    int c = top.c;
    int d = top.dir;
    int score = top.points;
    if(score == min_points[l][c][d]) {
      for(int dir = 0; dir < NDIR; dir++) {
        int dd = (d + dir) % NDIR;
        int nl = l + dlin[dd];
        int nc = c + dcol[dd];
        if(mat[nl][nc] == EMPTY) {
          int p = min_points[l][c][d] + 1;
          if(dir == 1 || dir == 3) {
            p += TURN_COST;
          } else if(dir == 2) {
            p += 2 * TURN_COST;
          }
          if(min_points[nl][nc][dd] == 0) {
            min_points[nl][nc][dd] = p;
            prev[nl][nc][dd].push_back(d);
            pq.push({nl, nc, dd, p});
          } else if(p < min_points[nl][nc][dd]) {
            prev[nl][nc][dd].clear();
            prev[nl][nc][dd].push_back(d);
            min_points[nl][nc][dd] = p;
            pq.push({nl, nc, dd, p});
          } else if(p == min_points[nl][nc][dd]) {
            prev[nl][nc][dd].push_back(d);
          }
        }
      }
    }
  }
}

int compute_min_path() {
  int ret = INF;
  for(int dir = 0; dir < NDIR; dir++) {
    int p = min_points[end.l][end.c][dir];
    if(p > 0 && p < ret) {
      ret = p;
    }
  }
  return ret;
}

void mark_points(int min_path) {
  int l = end.l;
  int c = end.c;
  for(int dir = 0; dir < NDIR; dir++) {
    if(min_points[l][c][dir] == min_path) {
      q.push({l, c, dir});
    }
  }
  while(!q.empty()) {
    Pos top = q.front();
    q.pop();
    mark[top.l][top.c] = 1;
    for(int x : prev[top.l][top.c][top.dir]) {
      int dd = (top.dir + 2) % NDIR;
      q.push({top.l + dlin[dd], top.c + dcol[dd], x});
    }
  }
}

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
  n++;
  return 1;
}

int main() {
  n = 0;
  while(read_line());

  dijkstra();
  int x = compute_min_path();
  mark_points(x);

  int res = 0;
  for(int l = 0; l < n; l++) {
    for(int c = 0; c < m; c++) {
      res += mark[l][c];
    }
  }
  printf("%d\n", res);

  return 0;
}