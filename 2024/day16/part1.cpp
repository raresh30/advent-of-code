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

int min_points[MAX_N][MAX_M][NDIR];
int n, m;
Point start, end;
char mat[MAX_N][MAX_M];
std::priority_queue<State> pq;

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
          if(min_points[nl][nc][dd] == 0 ||
             p < min_points[nl][nc][dd]) {
            min_points[nl][nc][dd] = p;
            pq.push({nl, nc, dd, p});
          }
        }
      }
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
  int res = INF;
  for(int d = 0; d < NDIR; d++) {
    int p = min_points[end.l][end.c][d];
    if(p > 0 && p < res) {
      res = p;
    }
  }
  printf("%d\n", res - 1);

  return 0;
}