/*

elements are linked by two pointers 

each element has three parts: pointer to previous | next pointer | data

head of list: prev pointer = NULL
tail of list: next pointer = NULL

from tail to head direction (ie. going backwards) -> use the prev pointer
from head to tail direction (ie. going forward) ->  use the next pointer

more flexible than the other way, better way to remove elements 

dlist_init :
void dlist_init(DList * list, void (*destroy)(void*data));
return value = none;

initialize the double linked list, destroy argument is a user defined 
function when dlist_destroy is called 

dlist_destroy:

void dlist_destroy(DList *list);
return none

calls the destroy function in dlsit_init and removed elements

dlist_ins_next:
int dlist_ins_next(DList *list, DListElmt *element, const void *data);

returns 0 if gucci, -1 if not 

insert element after the one specified 

new element has a pointer to data, so it remains valid till the element is 
in the list

dlist_ins_prev:

int dlist_ins_prev(DList *list, DListElmt *element, const void *data);

0 if gucci, -1 if not 

insert element just before the element specified 

dlist_remove:
int dlist_remove(DList *list, DListElmt *element, void **data);

0 if gucci, -1 if not 
removes the element specified
data points to the data stored stored in the element when removed 

 

*/
