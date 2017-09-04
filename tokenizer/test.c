#include <stdio.h>
#include <stdlib.h>
#include "mytoc.h"

/** Clears any chars still in the input buffer */
void clearInputBuffer() {
  while ( getchar() != '\n' );
}

/**
 * Reads input from the console and puts the input into s array with a max amount of chars as specified in limit, 
 * includes \0 into the array.
 * @param s           the pointer to the start of the char array
 * @param limit       the length of the char array
 */
void readInput(char *s, int limit) {
  char c = getchar();
  int count = 0;

  while (c >= 32 && count < limit - 1) {
    // inputs the char into the char array
    s[count] = c;
    count++;

    c = getchar();
  }

  // if the loop exits before the \n because the loop found a non accepted char value
  // this will get rid of all those remaining chars in the buffer
  if( c != 10 ) {
    clearInputBuffer();
  }

  s[count] = '\0';
}

char isExit(char *input) {
  if (input[0] == 'e' && input[1] == 'x' && input[2] == 'i' && input[3] == 't' && input[4] == '\0') {
    return 1;
  }

  return 0;
}

void freeUpArry(char **tokenArry) {
  for (int i = 0;;i++) {
    if (tokenArry[i] == (char *)0) {
      free(tokenArry);
      break;
    }

    free(tokenArry[i]);
  }
}

void testingLoop() {
  char *p = (char *)malloc( sizeof(char) * ( 200 + 1 ) );
  char *d = (char *)malloc( sizeof(char) * (1 + 1));

  printf("\nInput mode instructions:");
  printf("\n\t- String to tokenize is placed after the $ symbol, max 200 chars");
  printf("\n\t- Tokenizer delimiter is placed after the # symbol, only single char");
  printf("\n\t- if you delimiter consits of an empty string the default delimiter is \" \"");
  printf("\n\t- data input overflow is removed");
  printf("\n\t- input \"exit\" to leave the program\n");
  while (1) {
    
    printf("\n$ ");
    readInput(p, 201);

    if (isExit(p) == 1) {
      break;
    }

    printf("# ");
    readInput(d, 2);

    char **tokensArry;

    if (d[0] == '\0') {
      tokensArry = mytoc(p, ' ');
    } else {
      tokensArry = mytoc(p, d[0]);
    }

    for (int i = 0;;i++) {
      if (tokensArry[i] == (char *)0) {
        break;
      }
  
      char *token = tokensArry[i];
      printf("\ttoken %d: %s\n", i, token);
    }
    freeUpArry(tokensArry);
  }

  free(p);
}

void testCases() {
  printf("\tTest case: \"Hello my dog's name is Darwin.\"\n");
  char **tokensArry = mytoc("Hello my dog's name is Darwin.\0", ' ');
  for (int i = 0;;i++) {
    if (tokensArry[i] == (char *)0) {
      break;
    }

    char *token = tokensArry[i];
    printf("\ttoken %d: %s\n", i, token);
  }
  freeUpArry(tokensArry);
  
  printf("\n\tTest case: \"     Hello   World!   \"\n");
  tokensArry = mytoc("     Hello   World!   \0", ' ');
  for (int i = 0;;i++) {
    if (tokensArry[i] == (char *)0) {
      break;
    }

    char *token = tokensArry[i];
    printf("\ttoken %d: %s\n", i, token);
  }
  freeUpArry(tokensArry);
  
  printf("\n\tTest case: \"\"\n");
  tokensArry = mytoc("\0", ' ');
  for (int i = 0;;i++) {
    if (tokensArry[i] == (char *)0) {
      break;
    }

    char *token = tokensArry[i];
    printf("\ttoken %d: %s\n", i, token);
  }
  freeUpArry(tokensArry);
  
  printf("\n\tTest case: \"          \"\n");
  tokensArry = mytoc("          \0", ' ');
  for (int i = 0;;i++) {
    if (tokensArry[i] == (char *)0) {
      break;
    }

    char *token = tokensArry[i];
    printf("\ttoken %d: %s\n", i, token);
  }
  freeUpArry(tokensArry);
  
  printf("\n\tTest case: \" HelloWorld\"\n");
  tokensArry = mytoc(" HelloWorld\0", ' ');
  for (int i = 0;;i++) {
    if (tokensArry[i] == (char *)0) {
      break;
    }

    char *token = tokensArry[i];
    printf("\ttoken %d: %s\n", i, token);
  }
  freeUpArry(tokensArry);
}


int main() {
  printf("Justin Parra: tokenizer lab\n\n"); 
  
  testCases();
  testingLoop();

  return 0;
}
