#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "clist.h"

/*****************************************************************************
* ------------------------------ clist_init ------------------------------ *
*****************************************************************************/

void clist_init(CList *list, void (*destroy)(void *data)) {
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    return;
}

/*****************************************************************************
* ------------------------------ clist_destroy ---------------------------- *
*****************************************************************************/

void clist_destroy(CList *list) {
    void *data;

    // Remove each element
    while (clist_size(list) > 0) {
        if (clist_rem_next(list, list->head, &data) == 0 && list->destroy != NULL) {
            list->destroy(data);
        }
    }

    // No operations are allowed now, clear the list structure
    memset(list, 0, sizeof(CList));
    return;
}

/*****************************************************************************
* ------------------------------ clist_ins_next --------------------------- *
*****************************************************************************/

int clist_ins_next(CList *list, CListElmt *element, const void *data) {
    CListElmt *new_element;

    // Allocate storage for the new element
    if ((new_element = (CListElmt *)malloc(sizeof(CListElmt))) == NULL) {
        return -1;
    }

    // Insert element into the list (after the specified element)
    new_element->data = (void *)data;

    if (clist_size(list) == 0) {
        // Handle insertion when the list is empty
        new_element->next = new_element;
        list->head = new_element;
    } else {
        // Handle insertion when the list is not empty
        new_element->next = element->next;
        element->next = new_element;
    }

    // Adjust the size of the list
    list->size++;
    return 0;
}

/*****************************************************************************
* ------------------------------ clist_rem_next --------------------------- *
*****************************************************************************/

int clist_rem_next(CList *list, CListElmt *element, void **data) {
    CListElmt *old_element;

    // Do not allow removal from an empty list
    if (clist_size(list) == 0) {
        return -1;
    }

    // Remove the element from the list
    *data = element->next->data;

    if (element->next == element) {
        // There is only one element in the list
        old_element = element->next;
        list->head = NULL;
    } else {
        old_element = element->next;
        element->next = element->next->next;

        if (old_element == clist_head(list)) {
            list->head = old_element->next;
        }
    }

    // Free the storage allocated to the element
    free(old_element);

    // Reduce the size of the list
    list->size--;
    return 0;
}

/*****************************************************************************
* ------------------------------ data_destroy ----------------------------- *
*****************************************************************************/

void data_destroy(void *data) {
    free(data);
}

/*****************************************************************************
* ------------------------------ print_list ------------------------------- *
*****************************************************************************/

void print_list(CList *list) {
    CListElmt *current = list->head;

    if (current != NULL) {
        do {
            printf("(Address: %d | Data: %d | Next: %d) ->\n", 
                   (void *)current, *(int *)current->data, (void *)current->next);
            current = current->next;
        } while (current != list->head);
    }
}

/*****************************************************************************
* ------------------------------ main function ---------------------------- *
*****************************************************************************/

int main() {
    CList myList;
    int *data;

    // Initialize the list
    clist_init(&myList, data_destroy);

    // Add data to the circular linked list
    for (int i = 0; i <= 10; i++) {
        data = (int *)malloc(sizeof(int));
        if (data == NULL) {
            printf("Failed to allocate memory.\n");
            return 1;
        }
        *data = i;

        // Insert elements: for i == 0, pass NULL, otherwise, insert after head
        if (i == 0) {
            clist_ins_next(&myList, NULL, data); // Insert into an empty list
        } else {
            clist_ins_next(&myList, clist_head(&myList), data);
        }
    }

    // Print the list after insertion
    printf("List after insertion:\n");
    print_list(&myList);


    // Remove some elements from the circular linked list
    void *removed_data;
    for (int i = 0; i < 5; i++) {
        if (clist_rem_next(&myList, clist_head(&myList), &removed_data) == 0) {
            printf("\nRemoved element with data: %d\n", *(int *)removed_data);
            if (myList.destroy != NULL) {
                myList.destroy(removed_data);
            }
        } else {
            printf("Failed to remove element.\n");
        }
    }

    // Print the list after removal
    printf("\nList after removing 5 elements:\n");
    print_list(&myList);






    // Destroy the list
    clist_destroy(&myList);
    
    return 0;
}
