#include <stdio.h>

const int MAX_UPDATE = 1'000;
const int MAX_PAGE = 99;

struct Rule {
  int x, y;
};

bool active[MAX_UPDATE];
bool rule[MAX_PAGE][MAX_PAGE];
int n, sp;
int update[MAX_UPDATE], new_update[MAX_UPDATE];

int read_rule(Rule &x) {
  char ch = fgetc(stdin);
  if(ch == '\n') {
    return 0;
  }

  int a = (ch - '0') * 10 + (fgetc(stdin) - '0');
  fgetc(stdin);
  int b = (fgetc(stdin) - '0') * 10 + (fgetc(stdin) - '0');
  fgetc(stdin);

  x = {a, b};
  return 1;
}

int read_update() {
  char ch = fgetc(stdin);
  if(ch == EOF) {
    return 0;
  }

  n = 0;
  int x = (ch - '0') * 10 + (fgetc(stdin) - '0');
  update[n++] = x;
  while(fgetc(stdin) != '\n') {
    int x = (fgetc(stdin) - '0') * 10 + (fgetc(stdin) - '0');
    update[n++] = x;
  };

  return 1;
}

void dfs(int u) {
  active[u] = false;
  for(int v = 0; v <= MAX_PAGE; v++) {
    if(active[v] && !rule[v][u]) {
      dfs(v);
    }
  }
  new_update[sp++] = u;
}

void reorder() {
  for(int i = 0; i <= MAX_PAGE; i++) {
    active[i] = false;
  }
  for(int i = 0; i < n; i++) {
    active[update[i]] = true;
  }

  sp = 0;
  for(int i = 0; i < n; i++) {
    if(active[update[i]]) {
      dfs(i);
    }
  }
  for(int i = 0; i < n; i++) {
    update[i] = new_update[i];
  }
}

int main() {
  Rule r;
  while(read_rule(r)) {
    rule[r.x][r.y] = true;
  }

  int res = 0;
  while(read_update()) {
    bool ok = true;
    for(int i = 0; i < n; i++) {
      for(int j = i + 1; j < n; j++) {
        if(rule[update[j]][update[i]]) {
          ok = false;
        }
      }
    }
    if(!ok) {
      reorder();
      res += update[n / 2];
    }
  }

  printf("%d\n", res);

  return 0;
}
