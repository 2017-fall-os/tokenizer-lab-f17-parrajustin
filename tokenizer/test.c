#include <stdio.h>
#include "mytoc.h"

/** Clears any chars still in the input buffer */
void clearInputBuffer()
{
  while ( getchar() != '\n' );
}

/**
 * Reads input from the console and puts the input into s array with a max amount of chars as specified in limit, includes \0 into the array. The input is trimed of all leading and trailing spaces.
 * the nonAlphabet bool if true will allow non letters to be used in the input
 * @param s           the pointer to the start of the char array
 * @param limit       the length of the char array
 * @param nonAlphabet if non letters are allowed
 */
void readInput(char *s, int limit, bool nonAlphabet) {
  char c = getchar();
  int count = 0;

  // Used to get rid of trailing spaces
  bool endingSpaces = 0;
  int lastNonSpace = 0;

  while( ( ( !nonAlphabet && ( (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 32) ) || ( nonAlphabet && c >= 32 && c <= 126 ) ) && count < limit-1 ) {
    // makes sure the first char is a non space characther
    if( !(c == 32 && count == 0) ) {
      // used to keep track of the last non space to trim trailing spaces
      if( c != 32 ) {
        lastNonSpace = count;
        endingSpaces = false;
      }  else
        endingSpaces = true;

      // inputs the char into the char array
      s[count] = c;
      count++;
    }
    c = getchar();
  }

  // if the loop exits before the \n because the loop found a non accepted char value
  // this will get rid of all those remaining chars in the buffer
  if( c != 10 ) clearInputBuffer();

  // used to trim off extra spaces
  if( !endingSpaces )
    s[count] = '\0';
  else
    s[lastNonSpace+1] = '\0';
}

/**
 * Used to write the nodes in the binary tree in the order of parent -> left -> right
 * @param bt the binary tree node to write
 * @param f  the file where to write these nodes to
 */
void writeNode(BTree *bt, FILE *f) {
  // if the binary tree node is empty just exit
  if( bt == 0 ) return;

  fprintf(f, "%s\n", bt->name);
  writeNode(bt->left, f);
  writeNode(bt->right, f);
}

/**
 * Writes to the file specified by the user
 * @param bt the binary tree node to write
 */
void writeFile(BTree *bt) {
  // Prompt asking for file name
  printf("\nfile name to write to? ");
  char *p = (char *)malloc( sizeof(char) * ( 200 + 1 ) );
  readInput(p, 201, true); // read input, allow non a-zA-z_ characthers

  // check if user wants to exit
  char exitStr[5] = {'e','x','i','t','\0'};
  if( compare(p, exitStr) == 0 ) return; // the user chose to leave

  printf("Writing to file \"%s\"...\n", p);

  // write the binary tree
  FILE *f = fopen(p, "w");
  writeNode(bt, f);
  fclose(f);
}

void readFile() {
  // Prompt asking for file name
  printf("\nfile name to read? ");
  char *p = (char *)malloc( sizeof(char) * ( 200 + 1 ) );
  readInput(p, 201, true); // read input, allow non a-zA-z_ characthers

  // check if user wants to exit
  char exitStr[5] = {'e','x','i','t','\0'};
  if( compare(p, exitStr) == 0 ) return; // the user chose to leave

  printf("file to read: \"%s\"\n", p); // show the user their file

  // begin reading file
  FILE *fp;
  fp = fopen(p, "r");

  bool nodesExits = 1;
  char temp = '0';
  int count = 0;
  while( nodesExits ) {
    char *buf = (char *)malloc( sizeof(char) * ( 50 + 1 ) );
    count = 0;

    temp = (char)fgetc(fp);
    while( ( (temp >= 65 && temp <= 90) || (temp >= 97 && temp <= 122) || temp == 32 ) && count < 50 ) {
      buf[count] = temp;

      // prepare for next loop
      count++;
      temp = (char)fgetc(fp);
    }
    buf[count] = '\0'; // end string with null terminator


    if( count >= 1) {
      if( head == 0 ) {
        head = bTreeCreate();
        head->name = buf;
        head->parent = 0;
      } else {
        addBTreeNode(head, buf);
      }
    }

    if( temp == 10 ) continue;
    else nodesExits = false;

  }

  fclose(fp);
}

/**
 * Outputs the menu choices
 */
void menu() {
  printf("\n\n== Menu ==");
  printf("\na/A - add new employees");
  printf("\nr/R - remove employees");
  printf("\nc/C - clear employees");
  printf("\nl/L - list employees");
  printf("\nw/W - write employees to file");
  printf("\nf/F - file to read employees from");
  if( debugging ) {
    printf("\nh - print head");
  }
  printf("\ne/E - exit");
}

/**
 * Removes employees based on names provided by the user until exit is specified
 */
void removeEmployees() {
  char exitStr[5] = {'e','x','i','t','\0'};
  /**
   * unlike add employees p is declared out here because the array can be
   * overwritten since it won't be used somewhere else, only to specify which
   * node to be deleted
   */
  char *p = (char *)malloc( sizeof(char) * ( 100 + 1 ) );

  while( true ) {
    printf("? ");
    readInput(p, 101, false);

    // if the user has specified they want to exit
    if( compare(p, exitStr) == 0 ) {
      free(p);
      break;
    }

    if( head == 0 ) {
      continue; // if there is no head do nothing
    } else {
      head = removeBTreeNode(head, p);
    }
  }
}

/** Addes employees based on names provided by the user until exit is specified */
void addEmployees() {
  char exitStr[5] = {'e','x','i','t','\0'};

  while( true ) {
    char *p = (char *)malloc( sizeof(char) * ( 100 + 1 ) );
    printf("? ");
    readInput(p, 101, false);

    // if the user has specified they want to exit
    if( compare(p, exitStr) == 0 ) {
      free(p); // make sure to free the allocated memory
      break;
    } else if ( p[0] == 0 ) { // if the string the user specified is empty
      free(p); // make sure to free the allocated memory
      continue;
    }

    if( head == 0 ) { // if there is no head make one
      head = bTreeCreate();
      head->name = p;
      head->parent = 0;
    } else {
      addBTreeNode(head, p);
    }
  }
}

/**
 * Lists all employees by using the BTree printBTree method
 */
void listEmployees() {
  printf("\n Employee List:");
  if( head != 0 ) printBTree(head);
}

/**
 * handles the menu loop, it asks for the users response
 * @param ans the menuchoice variable from the main function
 */
void menuHandle( int *ans ) {
  printf("\nMenu Choice? ");
  *ans = getchar(); // Only gets the first char
  if( *ans != 10 ) clearInputBuffer(); // everything else is discarded

  // switch case that handles the different menu options
  switch( *ans ) {
    case 97: // a
    case 65: // A
      printf("\n\n== Adding employees ==");
      printf("\nto stop adding employees simply input \"exit\"\n");
      printf("only a-z, A-Z, and space are accepted, anything else will end the input\n");
      addEmployees();
      *ans = 0;
      break;

    case 99:
    case 67:
      printf("\n\n== Clearing employees ==");
      clearBTree(head);
      head = 0;
      *ans = 0;
      break;

    case 82: // R
    case 114: // r
      printf("\n\n== Removing employee ==");
      printf("\nto stop removing employees simply input \"exit\"\n");
      printf("only a-z, A-Z, and space are accepted, anything else will end the input\n");
      removeEmployees();
      *ans = 0;
      break;

    case 76: // L
    case 108: // l
      printf("\n\n== Listing employees ==");
      listEmployees();
      *ans = 0;
      break;

    case 69: // E
    case 101: // e
      printf("\n\n== Exiting ==\n");
      *ans = 1;
      break;

    case 87: // W
    case 119: // w
      printf("\n\n== Writing ==");
      printf("\ninput \"exit\" to exit writing choice.");
      writeFile(head);
      *ans = 0;
      break;

    case 70: // F
    case 102: // f
      printf("\n\n== Reading File ==");
      printf("\ninput \"exit\" to leave, max file name is 200 characthers");
      readFile();
      *ans = 0;
      break;

    case 104: // h
      if( debugging ) {
        printf("\n\n== Head ==");
        printf("\n %s \n", headStr(head));
        *ans = 0;
        break;
      }

    default:
      *ans = 0;
      menu();
      break;
  }
}

/**
 * the Main function that runs the whole program
 * @return default 0
 */
int main() {
  printf("ACME Solutions employee management...");

  menu();

  // menu loop that waits for inputs from the user
  int menuChoice = 0;
  while( menuChoice == 0 ) {
    menuHandle( &menuChoice );
  }

  return 0;
}
