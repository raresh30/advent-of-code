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

int main() {
  char ch;
  int res = 0;
  while((ch = fgetc(stdin)) != EOF) {
    n = 0;
    do {
      str[n++] = ch;
    } while((ch = fgetc(stdin)) != '\n');

    int pos = 0;
    while(pos < n) {
      int new_pos = mul(pos);
      if(new_pos > -1) {
        res += x * y;
        pos = new_pos;
      } else {
        pos++;
      }
    }
  }

  printf("%d\n", res);

  return 0;
}