#include <stdlib.h>
#include <string.h>
#include "ohtbl.h"

// reserve a sentinel memory address for vacated elements
// had a key kalue value pair removed

static char     vacated;

// ohtbl_init

int ohtbl_init(OHTbl *htbl, int positions, int (*h1)(const void *key), int
(*h2)(const void *key), int (*match)(const void *key1, const void *key2),void (*destroy)(void *data)){

    int i;

    // allocate space for the hash table
    //htbl-> table is a pointer, and each data is a pointer so need pointer to pointer
    if((htbl->table=(void**)malloc(positions * sizeof(void*)))==NULL)
        return -1;

    // initalize the positions
    htbl->positions = positions;
    for (i=0;i<htbl->positions;i++){
        htbl -> table[i] = NULL;
        }
    // set the vacated member to the sentinel memory address reserved for this 
    htbl->vacated = &vacated;

    //encapsulate the functions
    htbl->h1=h1;
    htbl->h2=h2;
    htbl->match = match;
    htbl->destroy = destroy;

    // initalize the number of elements in the table

    htbl->size=0;
    return 0;
}

// destroy function 



