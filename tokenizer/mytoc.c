#include <stdio.h>
#include <stdlib.h> 		/* for malloc */
#include <stdbool.h>    /* for bool */
#include "mytoc.h"

char ** mytoc(char *str, char delim) {
  // The length of the pointer array that contains each individual elment plus the null terminator
  int pointerArryLen = 0;
  // Specifies if the current element is being check, this is to stop a case where two or more delim chars are next to each other
  // ex: the delimiter is '0'
  // input: 0hello00world0test0    output -> hello,world,test instead of ,hello,,world,test,
  bool foundToken = false;

  printf("%s\n", str);
  
  // first lets count the number of tokens
  for (int i = 0; ; i++) {
    if (str[i] == '\0') { // if null terminator found exit
      if (foundToken) { // if it is hello\nworld\0 <- world should be counted
        pointerArryLen += 1;
      }
      break;
    }

    if (!foundToken && str[i] != delim) {
      foundToken = true;
    } else if (foundToken && str[i] == delim) {
      pointerArryLen += 1;
      foundToken = false;
    }
  }

  printf("%d test \n", pointerArryLen);

  char **tokensArry = (char **)malloc(sizeof(char *) * (pointerArryLen + 1)); // + 1 is for the null terminator
  int tokenIndex = 0;

  // now lets begin tokenizing 
  int tokenNum = 0;
  printf("Start\n");
  for (int i = 0, tokenStartIndex = -1; tokenNum < pointerArryLen; i++) {
    printf("%d %d %d\n", i, tokenStartIndex, tokenNum);
    if (str[i] != delim && tokenStartIndex == -1) {
      // first lets find a token and remember where the token starts
      tokenStartIndex = i;
    } else if ((str[i] == delim || str[i] == '\0') && tokenStartIndex != -1) {
      // here we have found a token where we are on the delimiator or the null terminator
      int length = i - tokenStartIndex;

      // malloc the token array
      printf("\tlen: %d\n", length);
      char *token = (char *)malloc(sizeof(char) * (length + 1)); // + 1 is for the null terminator

      for (int j = tokenStartIndex, index = 0; j < i; j++, index++) { // copy over the chars to the token 
        printf("\t%d\n", j);
        token[index] = str[j];
      }
      tokenNum++; // keeps track of the number of tokens we have done

      // add the token to the token array
      printf("\ttoken: %s\n", token);
      printf("\tindex: %d\n", tokenIndex);
      tokensArry[tokenIndex] = token;
      printf("\ttoken: %s\n", tokensArry[tokenIndex]);
      tokenIndex++;
      tokenStartIndex = -1;
      token[length] = '\0'; // add the null pointer to the token
    } else if (str[i] == '\0' && tokenStartIndex == -1) {
      // this shouldn't happen
      printf("Shouldn't Happen\n");
      break;
    }
  }
  tokensArry[pointerArryLen] = '\0';
  printf("End\n");

  return tokensArry;
}

