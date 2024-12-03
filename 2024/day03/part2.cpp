#include <stdio.h>
#include <ctype.h>

const int MAX_LEN = 20'000;

int n, x, y;
char str[MAX_LEN];

int read_int(int &pos) {
  int ret = 0;
  while(pos < n && isdigit(str[pos])) {
    ret = ret * 10 + str[pos] - '0';
    pos++;
  }
  return ret;
}

int mul(int pos) {
  if(pos + 3 >= n ||
     str[pos] != 'm' ||
     str[pos + 1] != 'u' ||
     str[pos + 2] != 'l' ||
     str[pos + 3] != '(') {
    return -1;
  }

  pos += 4;
  x = read_int(pos);
  if(x == 0 || pos >= n || str[pos] != ',') {
    return -1;
  }
  pos++;
  y = read_int(pos);
  if(y == 0 || pos >= n || str[pos] != ')') {
    return -1;
  }

  return pos;
}

bool check_do(int pos) {
  if(pos + 3 >= n ||
     str[pos] != 'd' ||
     str[pos + 1] != 'o' ||
     str[pos + 2] != '(' ||
     str[pos + 3] != ')') {
    return false;
  }
  return true;
}

bool check_dont(int pos) {
  if(pos + 6 >= n ||
     str[pos] != 'd' ||
     str[pos + 1] != 'o' ||
     str[pos + 2] != 'n' ||
     str[pos + 3] != '\'' ||
     str[pos + 4] != 't' ||
     str[pos + 5] != '(' ||
     str[pos + 6] != ')') {
    return false;
  }
  return true;
}

int main() {
  char ch;
  int res = 0;
  int add = 1;
  while((ch = fgetc(stdin)) != EOF) {
    n = 0;
    do {
      str[n++] = ch;
    } while((ch = fgetc(stdin)) != '\n');

    int pos = 0;
    while(pos < n) {
      int new_pos = mul(pos);
      if(new_pos > -1) {
        res += add * (x * y);
        pos = new_pos;
      } else if(check_do(pos)) {
        add = 1;
        pos += 4;
      } else if(check_dont(pos)) {
        add = 0;
        pos += 7;
      } else {
        pos++;
      }
    }
  }

  printf("%d\n", res);

  return 0;
}
