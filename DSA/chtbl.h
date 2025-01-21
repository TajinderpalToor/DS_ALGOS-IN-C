// implementation of chained hash tables header file

/*
- CHTb1 is the chained hash table data structure
- consists of six members: buckets; h,match and destroy are members used to ecapsualte the functions 
passed to chtbl_init, size is number of elements in table and table is the array of buckets 

*/

/*****************************************************************************
* *
* ------------------------------- chtbl.h -------------------------------- *
* *
*****************************************************************************/

# ifndef CHTBL_H
# define CHTBL_H

# include <stdlib.h>
# include "list.h"

/*****************************************************************************
* *
* Define a structure for chained hash tables. *
* *
*****************************************************************************/

typedef struct CHTbl_ {
    int buckets;
    
    int (*h)(const void *key);
    int (*match)(const void *key1,const void *key2);
    void (*destroy)(void *data);

    int size;
    List *table; // array of linked lists (buckets) - declared in list.h
} CHTbl;


/*****************************************************************************
* *
* --------------------------- Public Interface --------------------------- *
* *
*****************************************************************************/
int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key), int
 (*match)(const void *key1, const void *key2), void (*destroy)(void *data));

void chtbl_destroy(CHTbl *htbl);

int chtbl_insert(CHTbl *htbl, const void *data);

int chtbl_remove(CHTbl *htbl, void **data);

int chtbl_lookup(const CHTbl *htbl, void **data);

#define chtbl_size(htbl) ((htbl)->size)
#endif