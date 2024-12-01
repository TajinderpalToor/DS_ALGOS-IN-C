# include <stdlib.h>

# include "list.h"
# include "stack.h"

/*

we are implementing the stack using linked lists so can use those functions 

*/


// stack push

int stack_push(Stack *stack,const void *data){

    // push the data onto the stack
    // insert at the head 
    return list_ins_next (stack,NULL,data);

}

// stack pop

int stack_pop (Stack *stack, void **data) {
    // pop the data off the stack - LIFO = so remove the head
    // top of stack is the head, bottom is the tail, so when adding to the top you are technically creating a new head each time 

    return list_rem_next(stack,NULL,data);
}

// linkedlist functions
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"


// Initialize list -using list_init

void list_init(List *list, void (*destroy)(void *data)) {

// arrow is another way to do pointers, dereferencing and then getting value 

list ->size=0;
list ->destroy=destroy;
list -> head = NULL;
list -> tail = NULL;

return;

}

// do list_destroy

void list_destroy(List*list){

void	*data;

// remove each elemenet

while(list_size(list)>0){

/*
int list_rem_next(List *list, ListElmt *element, void **data);

if *element is NULL the data pointed to the head of the list is remvoed which 
means the element is gone and it should equal 0 meaning it was succesfful

// if destroy is set to null ( destroy in the init function) then it means you 
should not free the data, so to destroy this should not be null

-- you need a double pointer in list_rem_next because if you did a single pointer 
it just points to the address of that pointer so need a double pointer to get the 
actual pointer 

so the basically **data, points to the pointer where the *data is held, by doing 
** you can get the actual data pointer to be able to modify the value 

- the double pointer points holds the value of the address of the pointer, then 
by double pointing we can get the value that is held in the address of the 
pointer 


*/
if(list_rem_next(list,NULL,(void **)&data)==0 && list->destroy!=NULL)
{

// call a user defined function which is passed to list_init for destroy

list -> destroy(data);

}
}

// no operations allowed now 
memset(list,0,sizeof(List));
return;

}

int list_ins_next(List *list, ListElmt *element, const void *data) {

ListElmt    *new_element;

// allocate storage for the element 

/*

malloc(sizeof(ListElmt))== allocates size for a pointer to hold single listelmt
then the listelmt* infront is to cast the void* pointer to a structure listelmt* type
*/

if ((new_element = (ListElmt *)malloc(sizeof(ListElmt)))== NULL)
{
    // return -1 because if malloc is null it is unsucessful
    return -1;
}
//assigning new element  to our linked list
new_element -> data = (void *)data;

if (element == NULL){
    // this is for a head so insert into head
    if(list_size(list)==0){
        list -> tail=new_element;
    }
    new_element->next=list->head;
    list->head=new_element;
}
else{
    // if you are inserting anywhere else

    if (element-> next == NULL){
        // if the element we gave where we insert after is the tail
        list -> tail = new_element;
         new_element->next = NULL; 
    }
    //otherwise
    new_element->next=element->next;
    element->next=new_element;
    
}
list->size++;
return 0;
}

int list_rem_next(List *list,ListElmt *element, void**data){
    // basically each element stores a pointer to the data instead of the actual data itself
    /*
    by doing the above it is good for memory and flexibility because each node doesnt need to store the emtire data type
    if we used a single pointer you would jsut get the address of the data but then if you used a double pointer you can get to the data itself
    
    we pass the **data so you can access it later, as long as you remember the element you deleted you can always
    
    
    */

   ListElmt *old_element;

   // do not allow removal from an empty list

   if(list_size(list)==0){
    return -1;
   }
    // remove the element from the list

    if (element ==NULL){
        // handle removal from head of list
        *data = list->head->data;
        old_element = list->head;
        list->head=list->head->next;

        if(list_size(list)==1){
            list->tail=NULL;
        }
    }

    else{
        // if the element specified is the tail that means there is no next
        // therefore you cant delete something that is not there

        if (element -> next == NULL){
            return -1;
        }

        *data = element->next->data;
        old_element=element->next;
        element->next=(element->next)->next;

        if(element->next ==NULL){
            list->tail = element;
        }
    }

    free(old_element);

    //adjust size 
    list ->size--;
    return 0;
}

// need to make a print function 

void print_list(List *list){
    ListElmt *current = list->head;
    while(current != NULL){
        printf("Data: %d \n",*(int*)current->data);
        current=current->next;
    }
}
// need to make a user defined destroy function

void data_destroy(void *data) {
    free(data);
}


int main () {

Stack myStack;
int *data;

// initialize the stack
list_init(&myStack,data_destroy);

//push data to the stack

printf("Pushing elements onto the stack -LIFO\n");
printf("\n");
for (int i=1;i<=5;i++){
    data = (int *)malloc(sizeof(int));
    if (data == NULL) {
        printf("Memory allocation failed.\n");
        stack_destroy(&myStack);
        return -1;
    }

    *data = i *10;

    if (stack_push(&myStack,data) !=0){
        printf("Failed to push data onto the stack.\n");
        free(data);
        stack_destroy(&myStack);
        return -1;
    }
    printf("Pushed: %d\n",*data);
}
printf("\n");
// print the stack
print_list(&myStack);

// popping elements 
printf("\n");

printf("Popping elements from the stack - LIFO\n");
stack_pop(&myStack, (void **)&data);
printf("Popped: %d\n", *data);

stack_pop(&myStack, (void **)&data);
printf("Popped: %d\n", *data);

printf("\n");
// print the stack
print_list(&myStack);








} 