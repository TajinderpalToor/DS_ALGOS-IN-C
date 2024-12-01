/*****************************************************************************
* *
* ------------------------------- dlist.c -------------------------------- 
*
* *
*****************************************************************************/

# include <stdlib.h>
# include <string.h>
# include "dlist.h"
# include <stdio.h>

/*****************************************************************************
* *
* ------------------------------ dlist_init ------------------------------ 
*
* *
*****************************************************************************/

void dlist_init(DList *list, void (*destroy)(void *data)) {

// initialize the list 

/*
DList has a function called destroy but we are storing a pointer to a 
function destroy and it returns void and accepts void * data as a paramter

*/

list ->size=0;
list ->destroy=destroy;
list ->head=NULL;
list ->tail=NULL;

return;

}

/*****************************************************************************
* *
* ---------------------------- dlist_destroy ----------------------------- 
*
* *
*****************************************************************************/

void dlist_destroy(DList *list) {

void	*data;

//remove each element

while(dlist_size(list)>0) {

/*
data is a pointer which has the address of where data is stored, &data 
would then get the address of this pointer which then makes it a double 
pointer
which is what this function is taking 

 */

if (dlist_remove(list,dlist_tail(list), (void **)&data) == 0 && 
list->destroy !=NULL) {

// call the user defined function to free data
list->destroy(data);

}

}

// no operations are allowed now

memset(list,0,sizeof(DList));

return;

}

/*****************************************************************************
* *
* ---------------------------- dlist_ins_next ---------------------------- 
*
* *
*****************************************************************************/


int dlist_ins_next(DList *list, DListElmt *element, const void *data) {

DListElmt *new_element;

// do not allow null element unless list is empty.
// null allocates to head

if(element ==NULL && dlist_size(list) !=0){
return -1;
}

// allocate storage for the element 
if((new_element=(DListElmt *)malloc(sizeof(DListElmt)))== NULL){
/*
// tried allocating storage for the new element but it was null
//ie. didnt work 
// otherwise your gucci
// you define the malloc to new elment and then check if it equals null
// even if it is not equal to null your malloc still is defined outside the 
//if 

*/
return -1;

}

/*****************************************************************************
* *
* Insert the new element into the list. *
* *
*****************************************************************************/
// dont need to cast here
new_element -> data = (void*)data;

if (dlist_size(list)==0) {
// insert into empty list 

list ->head = new_element;
list->head->prev = NULL;
list ->head ->next=NULL;
list->tail = new_element;

}

else {
// the list is not empty 

new_element ->next = element->next;
new_element ->prev=element;

if(element->next ==NULL){
// inserting to the tail
list->tail=new_element;

}

else {

element->next->prev = new_element;

}
 element->next = new_element;

}
// adjust the size of the list to account for insertion

list -> size++;

return 0;

}





/*****************************************************************************
* *
* ---------------------------- dlist_ins_prev ---------------------------- 
*
* *
*****************************************************************************/

int dlist_ins_prev(DList *list, DListElmt *element, const void *data) {

DListElmt	*new_element;

// Do not allow a NULL element unless the list is empty 

if (element == NULL && dlist_size(list) !=0) {
	return -1;
}

// allocate storage to be managed by abstract datatype 

if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL) {
	return -1;

}

// insert new element into the list

new_element ->data = (void *)data;

// handle insertion into empty list

if (dlist_size(list) ==0) {

list->head=new_element;
list->head->prev = NULL;
list->head->next=NULL;
list ->tail = new_element;


}

else {

// handle insert anywhere into the list

new_element->next=element;
new_element->prev=element->prev;


// insert into head

if(element->prev==NULL){
list->head = new_element;

}

else{
element->prev->next=new_element;
}

element->prev = new_element;
}

// adjust the size

list->size++;

return 0;

}

/*****************************************************************************
* *
* ----------------------------- dlist_remove ----------------------------- 
*
* *
*****************************************************************************/

int dlist_remove(DList *list, DListElmt *element, void **data) {

// do not allow removal from an empty list or NULL element

if (element == NULL || dlist_size(list) ==0) {
	return -1;
}

//remove the element from the list.

*data= element->data;

if (element == list->head) {
// handle removal from the head of the list

list->head= element ->next;
if (list->head ==NULL){
// if once you remove head the list becomes empty the head and tail must be 
// null
list ->tail = NULL;
}

else {
element ->next->prev=NULL;
}

}

else {

// handle removal from somewhere other than list

element->prev->next = element ->next;

if (element->next == NULL) {

// if the element being removed is the tail
list->tail=element->prev;
}

else {
element->next->prev = element->prev;
}

}
// free the storage allocated by the abstract datatype

free (element);

list ->size--;

return 0;
}

void print_list(DList *list){
    DListElmt *current = list->head;
    while(current != NULL){
        //printf("<-(Prev: %p | Address: %p | Data: %d | Next: %p) ->\n",(void *)current->prev,(void *)current,*(int *)current->data,(void *)current->next);
        printf("<-(Prev: %d | Address: %d | Data: %d | Next: %d) ->\n",(int *)current->prev,(int *)current,*(int *)current->data,(int *)current->next);

		current=current->next;
    }
}
// need to make a user defined destroy function

void data_destroy(void *data) {
    free(data);
}

int main() {

DList myList;
DListElmt *element;
int *data;


dlist_init(&myList,data_destroy);

// adding data to the LL

for(int i=0;i<=10;i++){
    data = (int *) malloc(sizeof(int));
    *data=i;
	if(data == NULL) {
		printf("Failed to allocate memory.\n");
		return 1;
	}

	if(i==0){
		// insert at the head
		    dlist_ins_next(&myList,NULL,data);
	}
	else {
		// insert aftert the current tail
		dlist_ins_next(&myList,dlist_tail(&myList),data);

	}

}
printf("List after Insertion\n");
print_list(&myList);

// remove the elements

while(dlist_size(&myList)>4){
	element = dlist_tail(&myList);
	if(element!=NULL){
		dlist_remove(&myList,element,(void **)&data);
		printf("Removed element: %d\n",*data);
		free(data);
	}

}

//print the list
printf("List After Removal\n");
print_list(&myList);
printf("\n");

dlist_destroy(&myList);
print_list(&myList);
return 0;

}