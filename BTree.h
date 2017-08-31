/**
 * This Header file is based on code provided by Dr. Freudenthal
 */
#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

/**
 * The Binary Search Tree structure
 */
typedef struct BTree_s {
  struct BTree_s *left;
  struct BTree_s *right;
  struct BTree_s *parent;
  char *name;
} BTree;

BTree *head;
bool debugging;
bool allowDuplicates;

/**
 * Sets up the head
 */
void init();

/**
 * A debugging test to get the head of the tree
 * @param  bt the head of the tree
 * @return    the char string
 */
char *headStr(BTree *bt);

/**
 * Compare two strings ending with '\0' where 0 means equality, 1 means a comes before, and -1 means b comes before
 * Not cap sensitive
 * @param  a first string
 * @param  b second string
 * @return   0 means a == b, 1 a comes before b, -1 b comes before a
 */
char compare(char *a, char *b);

/**
 * Create BTree struct
 * @return BTree structure
 */
BTree *bTreeCreate();

/**
 * Free memory associated with this binary tree
 * @param bt the head of the tree
 */
void freeBTreeNode(BTree *bt);

/**
 * Free the BTree of all memory
 * @param bt the root of the BTree to destroy
 */
void clearBTree(BTree *bt);

/**
 * Finds the rightmost child
 * @param  bt the root of the brach to find the child
 * @return    the right most child
 */
BTree *findMax(BTree *bt);

/**
 * Removes the node with the s string
 * the code for this remove is based on the psuedocode from https://en.wikipedia.org/wiki/Binary_search_tree
 * @param  bt the root of the tree
 * @param  s  the string of the node to remove
 * @return    the new root
 */
BTree *removeBTreeNode(BTree *bt, char *s);

/**
 * Add a binary tree node head being the root and s being the employee name
 * @param head the root node
 * @param s    the string for the employee
 */
void addBTreeNode(BTree *head, char *s);

/**
 * print out the binary tree starting with bt as the head
 * @param bt the root node
 */
void printBTree(BTree *bt);

#endif // BTREE_H_INCLUDED
