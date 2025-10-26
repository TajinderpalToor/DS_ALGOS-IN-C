/*****************************************************************************
 * 
* *
* ------------------------------- bitree.c ------------------------------- *
* *
*****************************************************************************/

# include <stdlib.h>
# include <string.h>
# include "bitree.h"

// bitree_init - initalize function

void bitree_init(BiTree *tree, void (*destroy)(void *data)) {
    // 1. initialzie the tree
        
        tree -> size=0;
        tree -> destroy = destroy;
        tree -> root = NULL;

        return;
}

void bitree_destroy(BiTree *tree){

    // remove all the nodes from the tree - you can use left or right and set to NULL
    bitree_rem_left(tree,NULL);

    // no operations are allowed now so memset
    memset (tree,0,sizeof(BiTree));
    
    return;
}
// insert left function

int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data) {

    // the new node thats going to be inserted
    BiTreeNode *new_node,**position;

    // Determine where to insert the node

    if (node ==NULL){
        
        // insert at the root
        // check if the tree has stuff already
        if(bitree_size(tree)>0)
            return -1;
        // tree->root is a pointer, & gives you the pointer of the pointer
        // double pointer so we can change values later of the original
        position = &tree->root;
    }

    else {

        // only allow for insertion at the end of branch
        if (bitree_left(node) != NULL)
            return -1;
        
        position = &node ->left;
    }

    // allocate storage for the node
    // ----------------------------------------------------
    /*
    Basically malloc (size of node) gives space on the heap but returns void* then cast it
    */
    if ((new_node= (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL)
        return -1;
    // ----------------------------------------------------

    // insert the node into the tree
    // malloc returns the pointer to the first block of memory allocated

    new_node -> data  = (void *)data;
    new_node -> left  = NULL;
    new_node -> right = NULL;
    *position = new_node;

    // adjust size of the tree

    tree->size++;
    return 0;

}

int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data) {

BiTreeNode *new_node, **position;

// where to insert the node

if(node == NULL) {

    if (bitree_size(tree)>0)
        return -1;
    position = &tree->root;
}

else {
    
    // insert at the end of the branch

    if(bitree_right(node) !=NULL)
        return -1;

    position = &node->right;
}

// allocate storage

if ((new_node=(BiTreeNode *)malloc(sizeof(BiTreeNode)))==NULL)
    return -1;

// insert the node into the tree

new_node->data = (void *)data;
new_node->left = NULL;
new_node->right = NULL;
*position = new_node;

// adjust the size of the tree

tree->size++;

return 0;

}

// bitree_rem_left

void bitree_rem_left(BiTree *tree, BiTreeNode *node) {

    BiTreeNode **position;
    
    // no removal from empty tree
    if(bitree_size(tree)==0);
    return;

    // determine where to remove nodes
    if (node ==NULL)
        position =&tree->root;
    else
        position =&node->left;

    // remove the nodes 

    if(*position !=NULL){
        
        // if the position has a value remove both the left and right trees of the left subtree
        bitree_rem_left(tree, *position);
        bitree_rem_right(tree, *position);

        // use the destroy function
        if (tree->destroy !=NULL){
            tree->destroy((*position)->data);
        }
        free(*position);
        *position=NULL;

        // adjust the size
        tree->size--;
    }
    return;
}


void bitree_rem_right(BiTree *tree, BiTreeNode *node) {

    BiTreeNode **position;
    
    // no removal from empty tree
    if(bitree_size(tree)==0);
    return;

    // determine where to remove nodes
    if (node ==NULL)
        position =&tree->root;
    else
        position =&node->right;

    // remove the nodes 

    if(*position !=NULL){
        
        // if the position has a value remove both the left and right trees of the left subtree
        bitree_rem_left(tree, *position);
        bitree_rem_right(tree, *position);

        // use the destroy function
        if (tree->destroy !=NULL){
            tree->destroy((*position)->data);
        }
        free(*position);
        *position=NULL;

        // adjust the size
        tree->size--;
    }
    return;
}

// merging two binary trees

int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data) {


}

// continue from traversal
// do an expression tree
