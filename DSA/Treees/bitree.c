
# include <string.h>
# include <stdlib.h>

# include "bittree.h"

/* -------------------------
    bitree_init
**------------------------ */

void bitree_init( BiTree *tree, void(*destroy)(void *data)) {

    //initialize the binary tree

    // set size of tree to zero
    // destroy to destroy
    // root to null

    tree->size =0;
    tree->destroy=destroy;
    tree->root=NULL;

    return;
}


/* -------------------------
    bitree_destroy
**------------------------ */

void bitree_destroy(BiTree *tree) {

    // remove all the nodes from the tree
    // you could also do remove right here as well
    /*
    so null is the root, and tree is the binary tree itself
    so start at root and remove all left from the tree
    */

   // clear the structure 
   //the below set all the stuff in bitree like size, compare, etc to 0 or NULL
   memset(tree,0,sizeof(BiTree));
   return;
}

/* -------------------------
    bitree_ins_left
**------------------------ */

int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data) {

    BiTreeNode  *new_node, **position;

    // determine where to insert the node

    if (node == NULL){
        // allow insertion at root only if an empty tree
        if(bitree_size(tree)>0)
            return -1;
        position = &tree->root;
    }    

    else {
        // normally allow insertion only at the end of a branch

        if (bittree_left(node) != NULL)
            // node already has a left child so return -1
            return -1;
        position = &node->left;  

    }

        // allocate storage for the node

        if((new_node =(BiTreeNode *)malloc(sizeof(BiTreeNode)) == NULL))
            return -1;
        
        // insert the node into the tree.
        new_node->data = (void *)data;
        new_node->left = NULL;
        new_node->right = NULL;
        *position=new_node;

        // adjust the size of the tree 

        tree->size++;
        return 0;

}

int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data) {
    
    BiTreeNode  *new_node, **position;

    // determine where to insert the node

    if( node==NULL){
        // allow insert at root only if there is no other nodes

        if(bitree_size(tree)>0){
            return -1;
        }

        position = &tree->root;
    }

    else {
        // normal insertion if right of node is not already full

        if(bitree_right(node)!=NULL)
            return -1;
        position = &node->right;
    }

    //allocate storage for the node
    
        if((new_node =(BiTreeNode *)malloc(sizeof(BiTreeNode)) == NULL))
            return -1;

    // insert the new node into the tree

    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    tree->size++;
    return 0;

}

void bitree_rem_left(BiTree *tree, BiTreeNode *node){

    BiTreeNode  **position;

    // do not allow removal from an empty ree

    if(bitree_size(tree)==0)
        return;

    // determine where to remove the nodes

    if(node = NULL)
        position=&tree->root;
    
    else
        position=&node->left;
    
    // remove the nodes

    if (*position !=NULL) {
        
        // call the function recursivley to remove the left and right child of it

        bitree_rem_left(tree,*position);
        bitree_rem_right(tree,*position);
    
        if(tree->destroy !=NULL){
            // call the user defined function to free dynamically allocated data
            tree->destroy((*position)->data);
        }

        free(*position);
        *position=NULL;

        //adjust the size
        tree->size--;    
    }
    return;
}

void bitree_rem_right(BiTree *tree, BiTreeNode *node){

    BiTreeNode  **position;

    // do not allow removal from an empty ree

    if(bitree_size(tree)==0)
        return;

    // determine where to remove the nodes

    if(node = NULL)
        position=&tree->root;
    
    else
        position=&node->right;
    
    // remove the nodes

    if (*position !=NULL) {
        
        // call the function recursivley to remove the left and right child of it

        bitree_rem_left(tree,*position);
        bitree_rem_right(tree,*position);
    
        if(tree->destroy !=NULL){
            // call the user defined function to free dynamically allocated data
            tree->destroy((*position)->data);
        }

        free(*position);
        *position=NULL;

        //adjust the size
        tree->size--;    
    }
    return;
}

/*****************************************************************************
* *
* ----------------------------- bitree_merge ----------------------------- *
* *
*****************************************************************************/
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void
 *data) {
/*****************************************************************************
* *
* Initialize the merged tree. *
* *
*****************************************************************************/
bitree_init(merge, left->destroy);
/*****************************************************************************
* *
* Insert the data for the root node of the merged tree. *
* *
*****************************************************************************/
if (bitree_ins_left(merge, NULL, data) != 0) {
 bitree_destroy(merge);
 return -1;
}
/*****************************************************************************
* *
* Merge the two binary trees into a single binary tree. *
* *
*****************************************************************************/
bitree_root(merge)->left = bitree_root(left);
bitree_root(merge)->right = bitree_root(right);
/*****************************************************************************
* *
* Adjust the size of the new binary tree. *
* *
*****************************************************************************/
merge->size = merge->size + bitree_size(left) + bitree_size(right);
/*****************************************************************************
* *
* Do not let the original trees access the merged nodes. *
* *
*****************************************************************************/
left->root = NULL;
left->size = 0;
right->root = NULL;
right->size = 0;
return 0;
}

//page 221 for traversal