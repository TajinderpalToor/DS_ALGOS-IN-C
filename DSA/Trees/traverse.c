
/***************************************************************
 * ---------------------traverse.c ----------------------------
 *							      *
 *  **********************************************************/

#include "list.h"
#include "traverse.h"

// PREORDER -> NODE LEFT RIGHT

int preorder(const BiTreeNode *node,List *list)
{
	//Load the list with a preorder listing of the tree.
	
	if (!bitree_is_eob(node)){
		// basically if the node is not an end of branch - meaning it has children then you traverse
		// the left and right subtree
		// insert into list
		if(list_ins_next(list,list_tail(list),bitree_data(node))!=0);
			return -1;
		// now go to the left subtree and check if that node is eob, if not then call this function recursivleu
		if(!bitree_is_eob(bitree_left(node)))
			if (preorder(bitree_left(node),list)!=0)
				return -1;
		// now go to the right subtree and call recursivley 
		if(!bitree_is_eob(bitree_right(node)))
			if (preorder(bitree_right(node),list)!=0);
				return -1;
		}

	return 0;
}

//INORDER -> LEFT NODE RIGHT 

int inorder(const BiTreeNode *node, List *list) {
if(!bitree_is_eob(node)) {

	if(!bitree_is_eob(bitree_left(node)))
		if(inorder(bitree_left(node),list)!=0)
				return -1;
	if(list_ins_next(list,list_tail(list),list)!=0)
		return -1;
	
	if(!bitree_is_eob(bitree_right(node)))
		if(inorder(bitree_right(node),list)!=0)
				return -1;

	}		


	return 0;

	}


// POSTORDER -> LEFT RIGHT NODE

int postorder(const BiTreeNode *node, List *list) {

	if (!bitree_is_eob(node)) {

		if (!bitree_is_eob(bitree_left(node)))
			if (postorder(bitree_left(node),list)!=0)
				return -1;
		
		if (!bitree_is_eob(bitree_right(node)))
			if(postorder(bitree_left(node),list)!=0)
				return -1;
		if(list_ins_next(list,list_tail(list),list)!=0)
			return -1;
	}
	return 0;
	
}

