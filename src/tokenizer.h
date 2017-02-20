#include <stdio.h>
#include <string.h>

typedef int CLTokenType;

typedef struct CLToken CLToken;

struct CLToken {
  char* token;
  CLTokenType type;
};

typedef struct CLExpression CLExpression;

struct CLExpression {
  CLToken* tokens;
  int count;
};

int clips_match(char*,int);
char* clips_substring_expression(char*);
char* clips_strip_whitespace(char*);
char* clips_get_substring(char*, int, int);
int clips_tokenize(char*,CLToken*);
