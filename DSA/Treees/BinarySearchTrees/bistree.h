// binary search tree header file

// the define is basically so the compiler doesnt keep compiling and reprocessing
// this header file multiple times

#ifndef BISTREE_H
#define BISTREE_H

#include "../bittree.h"

// define balance factors 
// remmember +1/-1 is good and 0 is perfectly balanced

#define AVL_LEFT_HEAVY 1 
#define AVL_RIGHT_HEAVY -1
#define AVL_BALANCED 0

// define a structure for the notes
/*
This is going to be data, factor and hidden

the hidden is basically when you delete we dont remove from memory, you just hide it 
so its not considered it calcualtions or need to rebalance
in real life you would remove the node and rebalance 
the hidden is just skipped when searching this tree
*/

typedef struct AVlNode_ {

    void  *data;
    int   hidden;
    int   factor;
} AvlNode;

// implement binary search trees as binary trees

typedef BiTree BisTree;

// public interface 

void bistree_init(BisTree *tree, int (*compare)(const void *key1, const void
*key2), void (*destroy)(void *data));

void bistree_destroy(BisTree *tree);

int bistree_insert(BisTree *tree, const void *data);

int bistree_remove(BisTree *tree, const void *data);

int bistree_lookup(BisTree *tree, void **data);

#define bistree_size(tree) ((tree)->size)
#endif