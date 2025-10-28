/*
 *	Basically this file takes both the traverse and bitree file and lets you build the tree, traverse the tree and a	also insert, delete, etc.
 */

# include <stdio.h>
# include <stdlib.h>
# include "bitree.h"
# include "../list.h"
# include "traverse.h"

/* 
 * 	Remember our tree stores void*data, so a pointer to some data, that means we need to send the 
 * 	pointer to int 10 instead of just the value 10 
 */

// simple helper to allocate the integers as pointers like mentioned above

static int *new_int(int value) {
	int *p = malloc(sizeof(int));
	if(!p) {
		// perror prints a more descriptive error/the type of error
		perror("malloc");
		// exit_failure returns 1 to the OS and stops immediate
		exit (EXIT_FAILURE);
	}

	*p = value;
	return p;
	/*
	 * Side note: this function returns a pointer so int *new_int() just a function where the type
	 * is pointer to int 
	 * */
}	
// destory function thats used 

static void destroy_int(void *data) {
	free (data);
}

// print function

static void print_list (const List *list) {
	const ListElmt *elem= list_head(list);
	// listelmt is the list node structure, elem is pointing to the first node aka the head
	while(elem != NULL) {
		printf( "%d ", *(int *)list_data(elem));
		elem = list_next(elem);
		/* 
		 * Basically this function is going to keep going until elem points to NULL
		 */
	}
	printf("\n");
}

int main(void) {

	BiTree tree;
	List out;
	
	// initialzie the tree
	// binary tree that has data that should not be freed destroy is NULL
	bitree_init(&tree, destroy_int);
	
	/*	bitree init has two arguments a tree and also a pointer to a function destory which takes
	 * 	void data as an argument, so when you declare a node and the data using malloc, you need to free the data 		 as well because of garbage, so the destroy should be set to a user defined function which frees the data 		  and also the structure itself (rem function does this)
	 */

	 // insert the root
	 if(bitree_ins_left(&tree, NULL, new_int(10))!=0) {fprintf(stderr,"root creation not sucessful\n");return 1;};
	 BiTreeNode *root =bitree_root(&tree);
	 if(bitree_ins_left(&tree,root, new_int(5))!=0) {fprintf(stderr,"node creation not sucessful\n");return 1;};
	 if(bitree_ins_right(&tree,root, new_int(20))!=0) {fprintf(stderr,"node creation not sucessful\n");return 1;};

	 if(bitree_ins_left(&tree,bitree_left(root),new_int(3))!=0) {fprintf(stderr,"node creation not sucessful\n");return 1;};
	 if(bitree_ins_right(&tree,bitree_left(root),new_int(7))!=0) {fprintf(stderr,"node creation not sucessful\n");return 1;};
	 if(bitree_ins_left(&tree,bitree_right(root),new_int(15))!=0) {fprintf(stderr,"node creation not sucessful\n");return 1;};


	  // PREORDER
    list_init(&out, NULL); // NULL destroy so we don't double-free tree data
    if (preorder(bitree_root(&tree), &out) != 0) { fprintf(stderr, "preorder failed\n"); return 1; }
    printf("Preorder:  ");
    print_list(&out);
    list_destroy(&out);

    // INORDER
    list_init(&out, NULL);
    if (inorder(bitree_root(&tree), &out) != 0) { fprintf(stderr, "inorder failed\n"); return 1; }
    printf("Inorder:   ");
    print_list(&out);
    list_destroy(&out);

    // POSTORDER
    list_init(&out, NULL);
    if (postorder(bitree_root(&tree), &out) != 0) { fprintf(stderr, "postorder failed\n"); return 1; }
    printf("Postorder: ");
    print_list(&out);
    list_destroy(&out);

    // Cleanup the entire tree (frees ints via destroy_int)
    bitree_destroy(&tree);
    return 0;
}







