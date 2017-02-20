#include "tokenizer.h"
#include <stdlib.h>

const CLTokenType CL_TOKEN_TYPE_FUNCTION = 0;
const CLTokenType CL_TOKEN_TYPE_VALUE = 1;
const CLTokenType CL_TOKEN_TYPE_EXPRESSION = 2;

char* clips_get_substring(char* exp, int start, int end) {
  char* returnstr = malloc(sizeof(char)*(end-start+2));
  strncpy(returnstr,exp + start, end - start + 1);
  returnstr[end-start+1] = '\0';
  return returnstr;
}

char* clips_strip_whitespace(char* exp) {
  int startedText = 0;
  while (exp[startedText] == ' ' || exp[startedText] == '\t') {
    startedText++;
  }
  int endText = strlen(exp)-1;
  while (exp[endText] == ' ' || exp[endText] == '\t') {
    endText--;
  }
  char* r = clips_get_substring(exp,startedText,endText);
  return r;
}

char* clips_substring_expression(char* exp) {
  char* stripped = clips_strip_whitespace(exp);
  return clips_strip_whitespace(clips_get_substring(stripped,1,strlen(stripped) - 2));
}

int clips_match(char* exp,int index) {
  if ((strlen(exp) <= index + 1) && (index < 0)) {
    return -1;
  }
  if (exp[index] != '('){
    return -2;
  }
  int returnIndex = -3;
  int brackets = 1;
  int dquotes = 0;
  int squotes = 0;
  for (int i = index+1; i < strlen(exp); i++) {
    char temp = exp[i];
    if(temp == '\\'){
      i++;
      continue;
    }
    if(temp == '\"'){
      dquotes = !dquotes;
    }
    if(temp == '\''){
      squotes = !squotes;
    }
    if (!dquotes && !squotes){
      if(temp == '(')
	brackets += 1;
      if(temp == ')')
	brackets += -1;
    }
    if (brackets == 0) {
      returnIndex = i;
      break;
    }
  }
  return returnIndex;
}

int clips_get_single_token(char* exp) {
  if (!strcmp(exp,"")) {
    return -1;
  }
  int dquotes = 0;
  int squotes = 0;
  int i = 0;
  while (i <= strlen(exp)){
    char temp = exp[i];
    if (temp == '\0') {
      break;
    }
    if (temp == '(') {
      if (!dquotes && !squotes) {
	i = clips_match(exp, i) + 1;
	break;
      }
    }
    if (temp == ' ') {
      if (!dquotes && !squotes) {
	break;
      }
    }
    if(temp == '\"'){
      dquotes = !dquotes;
    }
    if(temp == '\''){
      squotes = !squotes;
    }
    i++;
  }
  return i;
}

/*
add 3 4 5 5 6 "ksndvnkjbdf dfknvkdfvd fv"
*/

int clips_tokenize(char* exp,CLToken* tokens) {
  int end = 0;
  CLToken t;
  int count = 0;
  while(1){
    end = clips_get_single_token(exp);
    if (end < 0) {
      break;
    }
    char* tempToken = clips_get_substring(exp, 0, end-1);
    t.token = tempToken;
    if (count == 0) {
      t.type = CL_TOKEN_TYPE_FUNCTION;
    } else {
      if (tempToken[0] == '(') {
	t.type = CL_TOKEN_TYPE_EXPRESSION;
      } else {
	t.type = CL_TOKEN_TYPE_VALUE;
      }
    }
    tokens = realloc(tokens, sizeof(CLToken) * (count+1));
    tokens[count] = t;
    exp = exp + end + 1;
    count++;
  }
  printf("Returning Token\n");
  return count;
}
