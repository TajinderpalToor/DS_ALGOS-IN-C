# include <stdlib.h>
# include <string.h>

#include "bistree.h"
static void destroy_right (Bistree *tree, BiTreeNode *node);

/*
 *
 * RL AND LR ROTATION ARE TWO STEP ROTATIONS
 * RR AND LL ARE SINGLE ROTATIONS
 */

// ROTATE LEFT -- this is either a LR rotation or LL rotation

static void rotate_left(BiTreeNode **node){

	BiTreeNode *left,
		   *grandchild;
	
	left = bitree_left(*node);
	if ((AvlNode *)bitree_data(left))->factor ==AVL_LFT_HEAVY) {

		// left heavy means a LL Rotation
		bitree_left(*node)=bitree_right(left);
		bitree_right(left);
		((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
		((AvlNode *)bitree_data(left)) ->factor = AVL_BALANCED;

	}

	// else do a LR rotation
	
	else {

		grandchild = bitree_right(left);
		bitree_right(left)=bitree_left(grandchild);
		bitree_left(grandchild) = left;
		bitree_left(*node)=bitree_right(grandchild);
		bitree_right(grandchild)=*node;

		// use switch case for the balance factor conditions
		
		case AVL_LFT_HEAVY:
		((AvlNode *)bitree_data(*node))->factor = AVL_RGT_HEAVY;
		((AvlNode *)bitree_data(left))->factor  = AVL_BALANCED;
		break;

		case AVL_BALANCED:
		((AvlNode *)bitree_data(*node))->factor = AVL_BALACNED;
		((AvlNode *)bitree_data(left))->factor  = AVL_BALANCED;
		break;

		case AVL_RGT_HEAVY:
		((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
		((AvlNode *)bitree_data(left))->factor  = AVL_LFT_HEAVY;
		break;

	}

	return;
}


// ROTATE RIGHT = EITHER A RR OR RL rotation

/*****************************************************************************

* *

* ----------------------------- rotate_right ----------------------------- *

* *

*****************************************************************************/

static void rotate_right(BiTreeNode **node) {

BiTreeNode *right,

 *grandchild;

right = bitree_right(*node);

if (((AvlNode *)bitree_data(right))->factor == AVL_RGT_HEAVY) {

 /**************************************************************************

 * *

 * Perform an RR rotation. *

 * *

 **************************************************************************/

 bitree_right(*node) = bitree_left(right);

 bitree_left(right) = *node;

 ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;

 ((AvlNode *)bitree_data(right))->factor = AVL_BALANCED;

 *node = right;

 }

else {


 /**************************************************************************

 * *

 * Perform an RL rotation. *

 * *

 **************************************************************************/

 grandchild = bitree_left(right);

 bitree_left(right) = bitree_right(grandchild);

 bitree_right(grandchild) = right;

 bitree_right(*node) = bitree_left(grandchild);

 bitree_left(grandchild) = *node;

 switch (((AvlNode *)bitree_data(grandchild))->factor) {

 case AVL_LFT_HEAVY:

 ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;

 ((AvlNode *)bitree_data(right))->factor = AVL_RGT_HEAVY;

 break;

 case AVL_BALANCED:

 ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;

 ((AvlNode *)bitree_data(right))->factor = AVL_BALANCED;

 break;

 case AVL_RGT_HEAVY:

 ((AvlNode *)bitree_data(*node))->factor = AVL_LFT_HEAVY;

 ((AvlNode *)bitree_data(right))->factor = AVL_BALANCED;

 break;

 }

 ((AvlNode *)bitree_data(grandchild))->factor = AVL_BALANCED;

 *node = grandchild;

}

return;

}

static void_destroy_let(BisTree *tree, BiTreeNode *node) {

	BiTreeNode	**position;

	// do not allow destruction of an empty table
	if (bitree_size(tree) == 0)
		return;

	// set the position for destroying
	
	if(node == NULL)
		position = &tree->root
	else
		position = &node->left;

	//destroy nodes
	
	if(*position !=NULL) {

		destroy_left(tree, *position);
		destroy_right(tree, *position);

		if (tree->destroy != NULL) {
			//page239

		}







