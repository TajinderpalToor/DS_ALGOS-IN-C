# include <stdio.h>
# include <stdlib.h>
# include "bittree.h"
# include "../list.h"
# include "traverse.h"



/*
Function to compile
gcc BinaryTree_fullimplementation.c bitree.c ../list.c traverse.c -o bintree.exe

*/
// function to free integer data

void destroy(void *data){
    free(data);
}

// function to print the list
// honestly dont need this here becasue the linked list has it, should have made an external file with print in it

void print_list(List *list){
    ListElmt *element = list_head(list);
    while (element !=NULL){
        // convert the element which is a void* into a int* and then dereference to get the actual value
        printf("%d ", *(int *)list_data(element));
        element = list_next(element);
    }
    printf("\n");
}

// main function

int main(){
    BiTree tree;
    List list;

    // initialize the tree
    bitree_init(&tree,destroy);
    
    // allocate values for trees
    int *a = malloc(sizeof(int)); *a=1;
    int *b = malloc(sizeof(int)); *b=2;
    int *c = malloc(sizeof(int)); *c=3;
    int *d = malloc(sizeof(int)); *d=4;
    int *e = malloc(sizeof(int)); *e=5;


// Build the tree structure 

//       1
//     /   \
//    2     3
//   / \  
//  4   5

// forming the tree structure
bitree_ins_left(&tree, NULL, a); // root=1
bitree_ins_left(&tree, bitree_root(&tree),b); // left of root =2
bitree_ins_right(&tree, bitree_root(&tree),c); // right of root =3
bitree_ins_left(&tree, bitree_left(bitree_root(&tree)),d); // left of child 2 =4
bitree_ins_right(&tree, bitree_left(bitree_root(&tree)),e); // right of child 2 =4


// Traversals

// Preorder:

list_init(&list,NULL);
printf("Preorder: ");
preorder(bitree_root(&tree),&list);
print_list(&list);
list_destroy(&list);


// inorder
list_init(&list,NULL);
printf("Inorder: ");
inorder(bitree_root(&tree),&list);
print_list(&list);
list_destroy(&list);

// postorder
list_init(&list,NULL);
printf("Postorder: ");
postorder(bitree_root(&tree),&list);
print_list(&list);
list_destroy(&list);


}