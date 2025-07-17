/****************************************************
 *              Traverse.c
*****************************************************/

/*
PreOrder Traversal Node Left Right - visit root, traverse left, traverse right, insert at tail
Inorder Traversal Left Node Right
PostOrder Traversal Left Right Node
*/

# include "../list.h"
# include "traverse.h"

// Preoder

int preorder (const BiTreeNode *node, List *list) {

    // preorder listing of the tree so node left right 
    
    if (!bitree_is_eob(node)) {
        // the current node is not null so keep traversing 
        // eob = end of branch = basically it is node, ex. D is a parent but has no children
        // left of D is eob and right of D is eob
    
        // basically current node exsists, so insert it into the tail of the list
        // if this didnt work it wont equal 0 so return -1

        if (list_ins_next(list,list_tail(list),bitree_data(node))!=0)
            return -1;
        
        // for the below, you still gotta check if the left node is traversable and if it is
        // recursivley do it and keep adding it to the tail 

        if(!bitree_is_eob(bitree_left(node)))
            if (preorder(bitree_left(node), list)!=0)
                return -1;
        
        if(!bitree_is_eob(bitree_right(node)))
            if (preorder(bitree_right(node), list) !=0)
                return -1;

    }
    return 0; 
}

int inorder (const BiTreeNode *node, List *list){
// left node right 
if(!bitree_is_eob(node)){
// going to recursivley keep going left till the last left node 
    if (!bitree_is_eob(bitree_left(node)))
        if (inorder(bitree_left(node),list)!=0)
            return -1;
    
    if (list_ins_next(list,list_tail(list),bitree_data(node))!=0)
        return -1;

    if (!bitree_is_eob(bitree_right(node)))
        if (inorder(bitree_right(node),list)!=0)
            return -1;

}
return 0; 
} 

/// PostOrder = Left Right Node

int postorder (const BiTreeNode *node, List *list){

    // load the list with postorder 

    if(!bitree_is_eob(node)){

        if(!bitree_is_eob(bitree_left(node)))
            if (postorder(bitree_left(node), list) !=0)
                return -1;
        
        if(!bitree_is_eob(bitree_right(node)))
            if (postorder(bitree_right(node), list) !=0)
                return -1;
        
        if (list_ins_next(list,list_tail(list),bitree_data(node))!=0)
            return -1;

    }
    return 0; 
}


