/*****************************************************************************
* *
* ------------------------------- bistree.c ------------------------------ *
* *
*****************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "bistree.h"
static void destroy_right(BisTree *tree, BiTreeNode *node);


//Rotate Left
/* rotate left is a LR and LL rotation. if you are left heavy then you are LL
if you are right heavy then LR*/

static void rotate_left(BiTreeNode **node) {
    BiTreeNode *left,*grandchild;
    left = bitree_left(*node);

    /*
    so the node itself just has right left, pointer and the data is a pointer or reference
    to a AVL Node, the avl node is what keeps factor, data and hidden
    this allows the tree to be more flexible
    */

   /*
   So the  if is just asking if the balance factor is left heavy which is +1 so its a 
   left left rotation

   other wise it is right heavy so LEFT right rotation
   */
    if (((AvlNode *)bitree_data(left))->factor == AVL_LEFT_HEAVY)
    
        {
            //LL ROTATION
            //left pointer of A to right child of left 
            bitree_left(*node)=bitree_right(left);
            // right pointer of left to A
            bitree_right(left)=*node;

            // both the node and left are balanced
            ((AvlNode *)bitree_data(*node))->factor=AVL_BALANCED;
            ((AvlNode *)bitree_data(left))->factor=AVL_BALANCED;
        }

    else {
            // LR rotation
            grandchild = bitree_right(left);
            // do a left right rotation
            //1.right child of left = left child of grandchild
            bitree_right(left)= bitree_left(grandchild);
            // 2. left child of grandchild = left 
            bitree_left(grandchild)=left;
            // 3. left  child of A = right child of grandchild
            bitree_left(*node)=bitree_right(grandchild);
            // 4. the right child of grandchild to node
            bitree_right(grandchild)=*node;

            // inspect the grandchild of the node
            /*
             inspecting the grandchild will tell us if the tree grew
             to the right or to the left
            */

           // the switch below gets the factor of the grandchild
           switch(((AvlNode *)bitree_data(grandchild))->factor){
           // case 1 is its left heavy - do LR rotation
            case AVL_LEFT_HEAVY:
                ((AvlNode *)bitree_data(*node))->factor = AVL_RIGHT_HEAVY;
                ((AvlNode *)bitree_data(left))->factor = AVL_BALANCED;
                break;
            
            case AVL_RIGHT_HEAVY:
                ((AvlNode *)bitree_data(left))->factor = AVL_LEFT_HEAVY;
                ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
                break;

            case AVL_BALANCED:
                ((AvlNode *)bitree_data(left))->factor = AVL_LEFT_HEAVY;
                ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
                break;

           }
            ((AvlNode *)bitree_data(grandchild))->factor = AVL_BALANCED;
            *node = grandchild;
    }

    return;
}

// rotate right 


static void rotate_right(BiTreeNode **node) {
    BiTreeNode *right,*grandchild;
    right = bitree_right(*node);


    if (((AvlNode *)bitree_data(right))->factor == AVL_RIGHT_HEAVY)
    
        {
            //RR ROTATION
            //right pointer of A to left child of right 
            bitree_right(*node)=bitree_left(right);
            // left pointer of right to A
            bitree_left(right)=*node;

            // both the node and left are balanced
            ((AvlNode *)bitree_data(*node))->factor=AVL_BALANCED;
            ((AvlNode *)bitree_data(right))->factor=AVL_BALANCED;
        }

    else {
            // RL rotation
            grandchild = bitree_left(right);
            // do a right left rotation
            //1.left child of right = right child of grandchild
            bitree_left(right)= bitree_right(grandchild);
            // 2. right child of grandchild = right 
            bitree_right(grandchild)=right;
            // 3. right  child of A = left child of grandchild
            bitree_right(*node)=bitree_left(grandchild);
            // 4. the left child of grandchild to node
            bitree_left(grandchild)=*node;


           // the switch below gets the factor of the grandchild
           switch(((AvlNode *)bitree_data(grandchild))->factor){

            case AVL_LEFT_HEAVY:
                ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
                ((AvlNode *)bitree_data(right))->factor = AVL_RIGHT_HEAVY;
                break;
            
            case AVL_RIGHT_HEAVY:
                ((AvlNode *)bitree_data(*node))->factor = AVL_LEFT_HEAVY;
                ((AvlNode *)bitree_data(right))->factor = AVL_BALANCED;
                break;

            case AVL_BALANCED:
                ((AvlNode *)bitree_data(right))->factor = AVL_LEFT_HEAVY;
                ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
                break;

           }
            ((AvlNode *)bitree_data(grandchild))->factor = AVL_BALANCED;
            *node = grandchild;
    }

    return;
}

// destroy left

static void destroy_left(BisTree *tree, BiTreeNode *node){

    BiTreeNode      **position;

    //do not allow destruction of empty tree
    if(bistree_size(tree)==0)
        return;

    // determine where to destroy nodes
    if (node ==NULL)
        position = &tree->root;
    else
        position = &node->left;
    
    // destroy the nodes

    // destroy the nodes

    if(*position !=NULL){

        destroy_left(tree, *position);
        destroy_right(tree, *position);

        if(tree->destroy !=NULL){
            //call a user defined function to free dynamically allocated data
            tree->destroy(((AvlNode *)(*position)->data)->data);
        }

        // free the avl data in the node, then free the node itself
        free((*position)->data);
        free(*position);
        *position=NULL;

        // adjust the size
        tree->size--;
    }

    return;
}


static void destroy_right(BisTree *tree, BiTreeNode *node){

    BiTreeNode      **position;

    //do not allow destruction of empty tree
    if(bistree_size(tree)==0)
        return;

    // determine where to destroy nodes
    if (node ==NULL)
        position = &tree->root;
    else
        position = &node->right;
    
    // destroy the nodes
    if(*position !=NULL){

        destroy_left(tree, *position);
        destroy_right(tree, *position);

        if(tree->destroy !=NULL){
            //call a user defined function to free dynamically allocated data
            tree->destroy(((AvlNode *)(*position)->data)->data);
        }

        // free the avl data in the node, then free the node itself
        free((*position)->data);
        free(*position);
        *position=NULL;

        // adjust the size
        tree->size--;
    }

    return;
}

// insert page 242