#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

/* -------------------------------------------------------------------------- */
/* Initialization / Destruction                                               */
/* -------------------------------------------------------------------------- */

void list_init(List *list, void (*destroy)(void *data)) {
    list->size    = 0;
    list->destroy = destroy;
    list->head    = NULL;
    list->tail    = NULL;
}

void list_destroy(List *list) {
    void *data;

    /* Remove each element starting from the head */
    while (list_size(list) > 0) {
        if (list_rem_next(list, NULL, &data) == 0 && list->destroy != NULL) {
            /* If a user-provided destroy function exists, use it on the payload */
            list->destroy(data);
        }
    }

    /* Clear the structure */
    memset(list, 0, sizeof(List));
}

/* -------------------------------------------------------------------------- */
/* Insertion / Removal                                                        */
/* -------------------------------------------------------------------------- */

int list_ins_next(List *list, ListElmt *element, const void *data) {
    ListElmt *new_element = (ListElmt *)malloc(sizeof(ListElmt));
    if (!new_element) return -1;

    new_element->data = (void *)data;

    if (element == NULL) {
        /* Insert at head */
        new_element->next = list->head;
        list->head = new_element;

        if (list->size == 0) {
            /* If the list was empty, tail also points to the new element */
            list->tail = new_element;
        }
    } else {
        /* Insert after the given element */
        new_element->next = element->next;
        element->next = new_element;

        if (new_element->next == NULL) {
            /* If we inserted at the end, update tail */
            list->tail = new_element;
        }
    }

    list->size++;
    return 0;
}

int list_rem_next(List *list, ListElmt *element, void **data) {
    ListElmt *old_element;

    if (list_size(list) == 0) {
        /* Nothing to remove */
        return -1;
    }

    if (element == NULL) {
        /* Remove from head */
        old_element = list->head;
        *data = old_element->data;
        list->head = old_element->next;

        if (list_size(list) == 1) {
            /* List is now empty */
            list->tail = NULL;
        }
    } else {
        /* Can't remove after the tail (no next element) */
        if (element->next == NULL) {
            return -1;
        }

        old_element = element->next;
        *data = old_element->data;
        element->next = old_element->next;

        if (element->next == NULL) {
            /* Removed the last element, fix tail */
            list->tail = element;
        }
    }

    free(old_element);
    list->size--;
    return 0;
}

/* -------------------------------------------------------------------------- */
/* Debug / Utilities                                                          */
/* -------------------------------------------------------------------------- */

/* Integer-specific print helper (useful for your traversal output testing) */
void print_list(List *list) {
    ListElmt *current = list->head;
    while (current != NULL) {
        printf("(Address:%p Data:%d Next:%p) -> ",
               (void *)current,
               *(int *)current->data,
               (void *)current->next);
        current = current->next;
    }
    printf("NULL\n");
}

/* Example destroy function if the list owns heap-allocated ints */
void data_destroy(void *data) {
    free(data);
}
