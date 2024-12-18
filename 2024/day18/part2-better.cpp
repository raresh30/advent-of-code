#include <stdio.h>

const int DATA_SIZE = 3450;
const int GRID_SIZE = 71;
const int CORRUPTED = 1;

const int NDIR = 4;
int dlin[NDIR] = {-1, 0, 1, 0};
int dcol[NDIR] = {0, 1, 0, -1};

struct Point {
  int l, c;

  bool operator ==(const Point &other) {
    return l == other.l && c == other.c;
  }

  bool operator !=(const Point &other) {
    return l != other.l || c != other.c;
  }
};

struct DSU {
  Point sef[GRID_SIZE][GRID_SIZE];

  void init() {
    for(int l = 0; l < GRID_SIZE; l++) {
      for(int c = 0; c < GRID_SIZE; c++) {
        sef[l][c] = {l, c};
      }
    }
  }

  Point find(Point x) {
    if(sef[x.l][x.c] == x) {
      return x;
    }
    return sef[x.l][x.c] = find(sef[x.l][x.c]);
  }

  void join(Point x, Point y) {
    Point sefx = find(x);
    Point sefy = find(y);
    if(sefx != sefy) {
      sef[sefx.l][sefx.c] = sefy;
    }
  }
};

int data_size;
Point data[DATA_SIZE];
char mat[GRID_SIZE][GRID_SIZE];
DSU dsu;

void read_data() {
  data_size = 0;
  int l, c;
  while(scanf("%d", &l) == 1) {
    fgetc(stdin);
    scanf("%d", &c);
    data[data_size++] = {l, c};
    mat[l][c] = CORRUPTED;
  }
}

int outside(int l, int c) {
  return l < 0 || c < 0 || l >= GRID_SIZE || c >= GRID_SIZE;
}

Point get_answer() {
  dsu.init();
  for(int l = 0; l < GRID_SIZE; l++) {
    for(int c = 0; c < GRID_SIZE; c++) {
      if(mat[l][c] != CORRUPTED) {
        for(int dir = 0; dir < NDIR; dir++) {
          if(!outside(l + dlin[dir], c + dcol[dir]) &&
             mat[l + dlin[dir]][c + dcol[dir]] != CORRUPTED) {
            dsu.join({l, c}, {l + dlin[dir], c + dcol[dir]});
          }
        }
      }
    }
  }

  int pos = data_size - 1;
  while(dsu.find({0, 0}) != dsu.find({GRID_SIZE - 1, GRID_SIZE - 1})) {
    int l = data[pos].l;
    int c = data[pos].c;
    mat[l][c] = 0;
    pos--;

    for(int dir = 0; dir < NDIR; dir++) {
      if(!outside(l + dlin[dir], c + dcol[dir]) &&
         mat[l + dlin[dir]][c + dcol[dir]] != CORRUPTED) {
        dsu.join({l, c}, {l + dlin[dir], c + dcol[dir]});
      }
    }
  }

  return {data[pos + 1].l, data[pos + 1].c};
}

int main() {
  read_data();
  Point ans = get_answer();
  printf("%d,%d\n", ans.l, ans.c);

  return 0;
}