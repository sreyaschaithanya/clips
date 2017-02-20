#include <stdio.h>
#include "tokenizer.h"


int main(int argc, char *argv[]) {
  char* exp = "(+ 9 8)";
  CLToken* t;
  int count = clips_tokenize(clips_substring_expression(exp), t);
  printf("%s, %d\n",t[0].token,sizeof(t));
  for (int i = 0; i < count ;i++){
    printf("%s --- TYPE --- %d\n",t[i].token, t[i].type);
  }
  return 0;
}
