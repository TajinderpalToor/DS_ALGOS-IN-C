/*

Linked lists are more efficient than arrays because they are dynamically allocated, the memory is allocated
at runtime, which is good becausse you dont know the size of data before compile tme alot 

Simple Linked List:
- indiivdual elements linked by a single pointer
- element:  data member and pointer (next pointer), element points to th next pointer (element that follows it)

- last element, next pointer is null known as tail
- first node/element is head
- traverse the list in one direction head to tail 

- the items look continous but are actually spread out cause using malloc 
- ouu this is cool you cant go backwards, if you do need to, and you anticipated it, you 
can remember the pointer values but theres better linkedin list options 

Interfaces of Linked List:

1. void list_int(List *list, void (*destroy)(void *data));

-> does not return a value
-> initilizes the linked list speciefied by list
-> must call this before you can do any other operation
-> the destroy argument provides a way to free dynamically allocate data when 
list_destroy is called - this is a paramter you must enter a value: if the data in the 
linkedid list is dynamically allocated using malloc, it should be set to free, so the 
data can be freed, if you dont need ti set freed (ie. not pointers), destroy should be 
set to NULL
- complexity == O(1)

2. list_destroy

void list_destroy(List *list);

-> destroys the linked list, no other functions after this can be called 
-> O(n) where n is the number of elements in the linked list 

3. list_ins_next

int list_ins_next(List *list, ListElm *element, const void *data)

-> 0 if inserting the element is good
-> -1 otherwise
-> inserts an element just after element in the linked list
->if element is null, insert it at the head of the list
-> complexity O(1)

4. list_rem_next

- 0 if removing is gucci, -1 otherwise
- removes the element just after the element mentioned
- if element is null, the element at head of the list is removed
- data points to the data stored in the element that was removed
- complexity = o1

5. list_size:

- returns number of elements
- complexity = o(1)

6. list_head:
- returns element at the head
- o1 complexity

7. list_tail:
- returns element at tail

8. list_is_tail:
- 1 if element is the tail, 0 otherwise

9. list_ is_tail:
- returns 1 if the elment is tail, 0 otherwise

10. list_data:
- returns data stored in the element 
- o1 complexity

11. list_next
- returns the next element 


Linked List Element:
- data member
- pointer to next element in the list 
- structure ListElmt = individual element in the LL
-  structure contains 5 things: size (number of elements in list), match:  not 
used by LL but datatypes that will be derivied later in LL, destroy, head 
pointer and tail pointer

- structures for the list elements and the list itseld


*/

# ifndef LIST_H
# define LIST_H

# include <stdlib.h>

/*******************************************					
* Define a structure for linked list elements                                  
*********************************************

/*

struct ListElmt_ is the actual structure type definition. In C, when defining a 
structure, it's common to give the structure a tag (in this case ListElmt_).
typedef allows you to create an alias for a type. After the typedef, you can use 
ListElmt as a shorthand for struct ListElmt_.

*/
typedef struct ListElmt_ {

	void	*data;
	struct ListElmt_ *next;
}ListElmt;

/*******************************************
* Define a structure for linked list.
*********************************************
/*
Match: used to compare data within the list, in certain implementations like 
custom data structures you use this function to check whether a given node 
matches some criteria, often for search or removing nodes 


*/

typedef struct List_ {

int	size;
int	(*match)(const void *key1, const void *key2);
void	(*destroy)(void *data);

ListElmt *head;
ListElmt *tail;

} List;

/*****************************************************************************
* *
* --------------------------- Public Interface --------------------------- *
* *
*****************************************************************************/

void list_init(List *list, void (*destroy)(void *data));

void list_destroy(List *list);

int list_ins_next(List *list, ListElmt *element, const void *data);

int list_rem_next(List *list, ListElmt *element, void **data);

#define list_size(list) ((list)->size)

#define list_head(list) ((list)->head)

#define list_tail(list) ((list)->tail)

#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)

#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)

#define list_data(element) ((element)->data)

#define list_next(element) ((element)->next)

#endif

/*
list_init:
- initilizes the linked list so it can be used in other operations 
- size of member is set to 0
- destroy set to destroy
- head and tail to NULL

list_destroy:
- the function passed as destroy to list_init is called once for each element 
- list_rem_next is called once for each element 

list_ins_next:
- inserts the element after the element specified, the call sets the new element 
to point to the data passed by the caller
- 2 cases: inserting at the head or elsewhere

1. Inserting Anywhere = so you have to first set the next pointer of the new 
element to point to the element it is coming before, then the next pointer of 
the element that comes before the new one to point to this new one 

2. Head: 
- no element that precedes the new element (comes before)
- set the next element of the new element to the current head and point the 
current head to the new element/head (reseting the head) - similar for tail

- for both increment sizze 

list_rem_next:
-  removes the element just after the element specified 
- 2 cases: remove head and removing other

1. Remove element from list:
- so to remove the element(elemenet specified + next), you must make the element 
specified point to next+1+1
- change size by decreasing size by 1


*/
