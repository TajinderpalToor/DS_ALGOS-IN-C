/***************************************************************
 * --------------------- traverse.c ----------------------------
 ***************************************************************/

#include "../list.h"
#include "traverse.h"

/* PREORDER: Node, Left, Right */
int preorder(const BiTreeNode *node, List *list) {
    if (!bitree_is_eob(node)) {
        /* insert current node's DATA */
        if (list_ins_next(list, list_tail(list), bitree_data(node)) != 0)
            return -1;

        if (!bitree_is_eob(bitree_left(node)))
            if (preorder(bitree_left(node), list) != 0)
                return -1;

        if (!bitree_is_eob(bitree_right(node)))
            if (preorder(bitree_right(node), list) != 0)
                return -1;
    }
    return 0;
}

/* INORDER: Left, Node, Right */
int inorder(const BiTreeNode *node, List *list) {
    if (!bitree_is_eob(node)) {
        if (!bitree_is_eob(bitree_left(node)))
            if (inorder(bitree_left(node), list) != 0)
                return -1;

        /* insert current node's DATA (not the list!) */
        if (list_ins_next(list, list_tail(list), bitree_data(node)) != 0)
            return -1;

        if (!bitree_is_eob(bitree_right(node)))
            if (inorder(bitree_right(node), list) != 0)
                return -1;
    }
    return 0;
}

/* POSTORDER: Left, Right, Node */
int postorder(const BiTreeNode *node, List *list) {
    if (!bitree_is_eob(node)) {
        if (!bitree_is_eob(bitree_left(node)))
            if (postorder(bitree_left(node), list) != 0)
                return -1;

        if (!bitree_is_eob(bitree_right(node)))
            if (postorder(bitree_right(node), list) != 0)   /* call RIGHT here */
                return -1;

        /* insert current node's DATA (not the list!) */
        if (list_ins_next(list, list_tail(list), bitree_data(node)) != 0)
            return -1;
    }
    return 0;
}
