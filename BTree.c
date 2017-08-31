#include <stdio.h>
#include <stdlib.h> 		/* for malloc */
#include <stdbool.h>    /* for bool */
#include "BTree.h"

/**
 * Sets up the head
 */
void init() {
  head = 0; // default head
  debugging = 0; // if debugging mode is enabled
  allowDuplicates = 0; // if duplicates are allowed
}

 /**
  * A debugging test to get the head of the tree
  * @param  bt the head of the tree
  * @return    the char string
  */
char *headStr(BTree *bt) {
  if( bt == 0 ){
    char *temp = {'\0'};
    return temp;
  }
  else return bt->name;
}

/**
 * Compare two strings ending with '\0' where 0 means equality, 1 means a comes before, and -1 means b comes before
 * Not cap sensitive
 * @param  a first string
 * @param  b second string
 * @return   0 means a == b, 1 a comes before b, -1 b comes before a
 */
char compare(char *a, char *b) {
  if( a[0] == 0 || b[0] == 0 ) {
    if( a[0] == 0 && b[0] == 0)
      return 0;
    else if( a[0] == 0 )
      return 1;
    else
      return -1;
  }

  // get rid of capital letters
  char tempA = ( a[0] < 97? a[0] + 32: a[0] );
  char tempB = ( b[0] < 97? b[0] + 32: b[0] );

  if( tempA == tempB )
    return compare(a+1, b+1);
  else if( tempA < tempB )
    return 1;
  else
    return -1;
}

/**
 * Create BTree struct
 * @return BTree structure
 */
BTree *bTreeCreate()
{
  BTree *bt = (BTree *)malloc(sizeof(BTree));
  bt->left = bt->right = 0;
  return bt;
}

/**
 * Free memory associated with this binary tree
 * @param bt the head of the tree
 */
void freeBTreeNode(BTree *bt) {
  free(bt->name);
  free(bt);
}

/**
 * Free the BTree of all memory
 * @param bt the root of the BTree to destroy
 */
void clearBTree(BTree *bt) {
  if( bt == 0 ) return; // if this node is empty

  if( bt->left != 0 ) // clear left nodes
    clearBTree(bt->left);
  if( bt->right != 0 ) // clear right nodes
    clearBTree(bt->right);

  //finally clear this node
  freeBTreeNode(bt);
}

/**
 * Finds the rightmost child
 * @param  bt the root of the brach to find the child
 * @return    the right most child
 */
BTree *findMax(BTree *bt) {
  if( bt->right == 0 ) {
    return bt;
  } else {
    return findMax(bt->right);
  }
}

/**
 * Removes the node with the s string
 * the code for this remove is based on the psuedocode from https://en.wikipedia.org/wiki/Binary_search_tree
 * @param  bt the root of the tree
 * @param  s  the string of the node to remove
 * @return    the new root
 */
BTree* removeBTreeNode(BTree *bt, char *s) {
  if( bt == 0 ) return 0; // bt is empty return pointer to nothing
  char compareTest = compare(s, bt->name);

  if( compareTest > 0 ) { // is the string lexicographically before
    BTree *temp = removeBTreeNode(bt->left, s);

    // needed incase the child is modified
    bt->left = temp;
    if( temp != 0 )
      temp->parent = bt;
    return bt;
  } else if( compareTest < 0 ) { // is the string lexicographically after
    BTree *temp =  removeBTreeNode(bt->right, s);

    // needed incase the child is modified
    bt->right = temp;
    if( temp != 0 )
      temp->parent = bt;
    return bt;
  } else { // this node is the one to be deleted
    if( bt->left != 0 && bt-> right != 0 ) { // this node has both children
      BTree *temp = findMax(bt->left); // get the rightmost left child

      // replace both node's names
      bt->name = temp->name;
      char *p = (char *)malloc( sizeof(char) * ( 1 + 1 ) );
      p[0] = 'a';
      p[1] = '\0';
      temp->name = p;

      bool check = compare(bt->name, temp->parent->name) == 0; // if true this is the left child, otherwise it is the right
      BTree *parent = temp->parent;
      temp = removeBTreeNode(temp, temp->name);

      if( check ) {
        parent->left = temp;
      } else {
        parent->right = temp;
      }

      return bt;
    } else if( bt->left != 0 ) { // node only has the left child
      BTree *temp = bt->left;
      freeBTreeNode(bt);
      return temp;
    } else if( bt->right != 0 ) { // node only has the right child
      BTree *temp = bt->right;
      freeBTreeNode(bt);
      return temp;
    } else { // node has no children
      freeBTreeNode(bt);
      return 0;
    }

  }

  return 0;
}

/**
 * Add a binary tree node head being the root and s being the employee name
 * @param head the root node
 * @param s    the string for the employee
 */
void addBTreeNode(BTree *bt, char *s) {
  char c = compare(bt->name, s);

  if( !allowDuplicates && c == 0 ) return;

  if( c <= 0 ) {
    if( bt->left != 0 )
      addBTreeNode(bt->left, s);
    else {
      BTree *node = bTreeCreate();
      node->name = s;
      node->parent = bt;

      bt->left = node;
    }
  } else {
    if( bt->right != 0 )
      addBTreeNode(bt->right, s);
    else {
      BTree *node = bTreeCreate();
      node->name = s;
      node->parent = bt;

      bt->right = node;
    }
  }
}

/**
 * print out the binary tree starting with bt as the head
 * @param bt the root node
 */
void printBTree(BTree *bt) {
  if( bt->left != 0 ) {
    printBTree(bt->left);
  }

  printf("\n - %s", bt->name);

  if( bt->right != 0 ) {
    printBTree(bt->right);
  }
}
