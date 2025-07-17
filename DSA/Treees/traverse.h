/****************************************************
 *              traverse.h
 ****************************************************/

 #ifndef TRAVERSE_H
 #define TRAVERSE_H
 
 #include "bittree.h"   // Assumes your binary tree struct & functions are defined here
 #include "../list.h"     // List structure used to store traversal results
 
 /* Function prototypes for tree traversals */
 int preorder(const BiTreeNode *node, List *list);
 int inorder(const BiTreeNode *node, List *list);
 int postorder(const BiTreeNode *node, List *list);
 
 #endif // TRAVERSE_H
 