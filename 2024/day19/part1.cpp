#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

const int MAX_DICT_SIZE = 1'000;
const int MAX_WORD_LEN = 50;
const int MAX_STR_LEN = 10'000;

int dict_size;
int word_len[MAX_DICT_SIZE];
char *dict[MAX_DICT_SIZE];

char word[MAX_WORD_LEN];

int len;
char str[MAX_STR_LEN];
char pref[MAX_STR_LEN + 1];

int read_word() {
  char ch;
  int len = 0;
  while(isalpha(ch = fgetc(stdin))) {
    word[len++] = ch;
  }
  word_len[dict_size] = len;
  fgetc(stdin);
  dict[dict_size] = (char *)malloc(len * sizeof(char));
  for(int i = 0; i < len; i++) {
    dict[dict_size][i] = word[i];
  }
  dict_size++;

  return ch == ',';
}

void read_dict() {
  dict_size = 0;
  while(read_word());
}

int read_str() {
  char ch = fgetc(stdin);
  if(ch == EOF) {
    return 0;
  }
  len = 0;
  do {
    str[len++] = ch;
  } while(isalpha(ch = fgetc(stdin)));
  return 1;
}

int main() {
  read_dict();
  int res = 0;
  while(read_str()) {
    pref[0] = 1;
    for(int i = 1; i <= len; i++) {
      pref[i] = 0;
      for(int j = 0; j < dict_size; j++) {
        if(i - word_len[j] >= 0 && pref[i - word_len[j]] > 0) {
          int k = 0;
          while(k < word_len[j] && str[i - word_len[j] + k] == dict[j][k]) {
            k++;
          }
          if(k >= word_len[j]) {
            pref[i] = 1;
          }
        }
      }
    }
    res += pref[len];
  }
  printf("%d\n", res);

  return 0;
}