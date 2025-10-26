/*

Interface for Binary Trees:

bitree_init:
    - initializes the tree, must be called before the tree is used
    - destroy = way to free dynamically allocated memory
    - dynamically allocated memory, set destroy to free
    - destroy should be user defined function if data contains several dynamically 
      allocated members

bitree_destroy:

bitree_ins_left:
    - return value: 0 if insert sucessful, -1 if not
    - insert a node as the left child of the node specified (x), if x null then insert
      as root, if left child of x esists return -1
      
bitree_ins_right: same as above but inserting right child

bitree_rem_left:
    - remove the subtree of the left child
    - if the node is NULL then the enture tree is removed
    - destroy function thrown into init function is used and removes node by node

bitree_rem_right:
    - same as above but on the right child

bitree_is_eob:
    - 1 if the node is end of  branch

bitree_is_leaf:
    - 1 if the node is a leaf

*/


/*****************************************************************************
* *
* ------------------------------- bitree.h ------------------------------- *
* *
*****************************************************************************/
#ifndef BITREE_H
#define BITREE_H
#include <stdlib.h>
/*****************************************************************************
* *
* Define a structure for binary tree nodes. *
* *
*****************************************************************************/
typedef struct BiTreeNode_ {
void *data;
struct BiTreeNode_ *left;
struct BiTreeNode_ *right;
} BiTreeNode;
/*****************************************************************************
* *
* Define a structure for binary trees. *
* *
*****************************************************************************/
typedef struct BiTree_ {
int size;
int (*compare)(const void *key1, const void *key2);
void (*destroy)(void *data);
BiTreeNode *root;
} BiTree;
/*****************************************************************************
* *
* --------------------------- Public Interface --------------------------- *
* *
*****************************************************************************/
void bitree_init(BiTree *tree, void (*destroy)(void *data));
void bitree_destroy(BiTree *tree);
int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data);
int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data);
void bitree_rem_left(BiTree *tree, BiTreeNode *node);
void bitree_rem_right(BiTree *tree, BiTreeNode *node);
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data);
#define bitree_size(tree) ((tree)->size)
#define bitree_root(tree) ((tree)->root)
#define bitree_is_eob(node) ((node) == NULL)
#define bitree_is_leaf(node) ((node)->left == NULL && (node)->right == NULL)
#define bitree_data(node) ((node)->data)
#define bitree_left(node) ((node)->left)
#define bitree_right(node) ((node)->right)
#endif