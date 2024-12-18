#include <stdio.h>
#include <queue>

const int GRID_SIZE = 71;
const int CORRUPTED = 1;

const int NDIR = 4;
int dlin[NDIR] = {-1, 0, 1, 0};
int dcol[NDIR] = {0, 1, 0, -1};

struct Point {
  int l, c;
};

char grid[GRID_SIZE + 2][GRID_SIZE + 2];
int dist[GRID_SIZE + 2][GRID_SIZE + 2];
std::queue<Point> q;

void init_border() {
  for(int l = 0; l <= GRID_SIZE + 1; l++) {
    grid[l][0] = grid[l][GRID_SIZE + 1] = CORRUPTED;
  }
  for(int c = 0; c <= GRID_SIZE + 1; c++) {
    grid[0][c] = grid[GRID_SIZE + 1][c] = CORRUPTED;
  }
}

int find_min_path() {
  for(int l = 0; l <= GRID_SIZE + 1; l++) {
    for(int c = 0; c <= GRID_SIZE + 1; c++) {
      dist[l][c] = -1;
    }
  }
  q.push({1, 1});
  dist[1][1] = 0;
  while(!q.empty()) {
    Point top = q.front();
    q.pop();
    for(int dir = 0; dir < NDIR; dir++) {
      int nl = top.l + dlin[dir];
      int nc = top.c + dcol[dir];
      if(dist[nl][nc] == -1 && grid[nl][nc] != CORRUPTED) {
        dist[nl][nc] = dist[top.l][top.c] + 1;
        q.push({nl, nc});
      }
    }
  }
  return dist[GRID_SIZE][GRID_SIZE];
}

int main() {
  init_border();
  int l, c;
  while(find_min_path() != -1) {
    scanf("%d", &l);
    fgetc(stdin);
    scanf("%d", &c);
    grid[l + 1][c + 1] = CORRUPTED;
  }
  printf("%d,%d\n", l, c);

  return 0;
}