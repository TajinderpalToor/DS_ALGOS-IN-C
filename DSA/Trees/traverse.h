/*****************************************************************************
 * *                                                                            *
 * * ------------------------------ traverse.h -------------------------------- *
 * *                                                                            *
 * *****************************************************************************/

#ifndef TRAVERSE_H
#define TRAVERSE_H
#include <stdlib.h>
#include "list.h"
#include "bitree.h"   /* for BiTreeNode and bitree_is_eob, bitree_left/right */

	/* Load the list with a preorder listing of the tree rooted at node. */
	int preorder(const BiTreeNode *node, List *list);

	/* Load the list with an inorder listing of the tree rooted at node. */
	int inorder(const BiTreeNode *node, List *list);

	/* Load the list with a postorder listing of the tree rooted at node. */
	int postorder(const BiTreeNode *node, List *list);

#endif /* TRAVERSE_H */

