#include <stdio.h>

const int MAX_UPDATE = 1'000;
const int MAX_PAGE = 99;

struct Rule {
  int x, y;
};

bool rule[MAX_PAGE + 1][MAX_PAGE + 1];
int n;
int update[MAX_UPDATE];

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
    if(ok) {
      res += update[n / 2];
    }
  }

  printf("%d\n", res);

  return 0;
}