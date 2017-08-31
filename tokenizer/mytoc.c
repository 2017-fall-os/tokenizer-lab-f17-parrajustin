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
  bool checkingElement = false;
  
  // first lets count the number of tokens
  for (int i = 0; ; i++) {
    if (str[i] === '\0') { // if null terminator found exit
      if (checkingElement) { // if it is hello\nworld\0 <- world should be counted
        pointerArryLen += 1;
      }
      break;
    }

    if (!checkingElement && str[i] != delim) {
      checkingElement = true;
    } else if (checkingElement && str[i] == delim) {
      pointerArryLen += 1;
      checkingElement = false;
    }
  }

  char **tokensArry = (char **)malloc(sizeof(char) * (pointerArryLen + 1)); // + 1 is for the null terminator
  int tokenIndex = 0;

  // now lets begin tokenizing 
  int tokenNum = 0;
  for (int i = 0, startIndex = -1; tokenNum < pointerArryLen; i++) {
    if (str[i] != delim && startIndex == -1) {
      // first lets find a token and remember where the token starts
      startIndex = i;
    } else if ((str[i] == delim || str[i] == '\0') && startIndex != -1) {
      // here we have found a token where we are on the delimiator or the null terminator
      int length = i - startIndex;
      startIndex = -1;

      // malloc the token array
      char *token = (char *)malloc(sizeof(char *) * (length + 1)); // + 1 is for the null terminator
      for (int j = startIndex, index = 0; j < i; j++, index++) { // copy over the chars to the token 
        token[index] = str[j];
      }
      token[length] = '\0'; // add the null pointer to the token
      tokenNum++; // keeps track of the number of tokens we have done

      // add the token to the token array
      tokensArry[tokenIndex] = token;
      tokenIndex++;
    } else if (str[i] == '\0') {
      // this shouldn't happen
      printf("Shouldn't Happen\n");
    }
  }

  tokensArry[tokenIndex] = '\0';
}

