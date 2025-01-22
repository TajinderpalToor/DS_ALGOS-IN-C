// implementation of chained hash tables header file with key value

/*

In this the key value pairs will be the nodes of the linkedlist, so the data section will point to a keyvaluepair struct which will house the key and value 

*/

/*****************************************************************************
* *
* ------------------------------- chtbl.h -------------------------------- *
* *
*****************************************************************************/

# ifndef CHTBL_HKEY
# define CHTBL_HKEY

# include <stdlib.h>
# include "../list.h"



/*****************************************************************************
* *
* Define a structure for key value pairs*
* *
*****************************************************************************/
typedef struct keyvaluepair {

    void *key; //pointer to key
    void *value; //pointer to value
} keyvaluepair;




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

int chtbl_insert(CHTbl *htbl, void *key, void *data);

int chtbl_remove(CHTbl *htbl, void **data);

int chtbl_lookup(const CHTbl *htbl, void *key);

#define chtbl_size(htbl) ((htbl)->size)
#endif