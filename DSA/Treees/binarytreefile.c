/*
    This is the file that takes the bitree file and the traverse file
    it has the main file
*/

#include <_stdio.h>
#include <stdlib.h>
#include <traverse.h>
#include <bittree.h>
#include <list.h>

// print function used in traversal list

void print_tree(List *list){

    ListElmt *element = list_head(list);
    while (element != NULL) {
        printf("%d ", *(int *)list_data(element));
        element = list_next(element);
    }
    printf("\n");

}

int main() {
    
}