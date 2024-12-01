# include <stdlib.h>
# include <string.h>
# include "clist.h"

/*****************************************************************************
* *
* ------------------------------ clist_init ------------------------------ *
* *
*****************************************************************************/

void clist_init(CList *list,void (*destroy)(void *data)){
    /*****************************************************************************
* *
* Initialize the list. *
* *
*****************************************************************************/

list ->size=0;
list ->destroy=destroy;
list -> head =NULL;

return;

}

// client destroy

void clist_destroy(CList *list){
    void    *data;

    //remove each element 
    while(clist_size(list)>0){

        if(clist_rem_next(list,list->head,(void **)data)==0 && list->destroy !=NULL){
            list->destroy(data);
        }

    }

    // no operations now
    memset(list,0,sizeof(CList));
    return;
}

int clist_ins_next(CList *list, CListElmt *element, const void *data){
    CListElmt   *new_element;

    // allocate storage for the element 

    if((new_element)=(CListElmt *)malloc(sizeof(CListElmt))==NULL){
        return -1;
    }

    // insert element into the list (ie. after the specified element)

    new_element->data = (void*)data;

    //handle insertion when the list is empty
    if(clist_size(list)==0){
    new_element->next=new_element;
    list->head = new_element;
    }

    else {
      // handle insertion when the list is not empty
      new_element->next=element->next;
      element->next=new_element;  
    }

    // adjsut the size of the list 
    list->size++;
    return 0;
}

/*****************************************************************************
* *
* ---------------------------- clist_rem_next ---------------------------- *
* *
*****************************************************************************/

int clist_rem_next(CList *list, CListElmt *element, void **data){

    CListElmt       *old_element;

    //do not allow remove from an empty list 

    if(clist_size(list)==0){
        return -1;
    }

    //remove the element from the list

    *data=element->next->data;

    // remove the element, if there is only one element in the list
    // head points to itself head is the tail too

    if (element->next == element) {
        old_element=element->next;
        list->head=NULL;
    }

    else{
        old_element=element->next;
        element->next=element->next->next;
        if(old_element ==clist_head(list)){
            list->head = old_element->next;
        }
    }

    // free the storage 
    free(old_element);

    //reduce the size
    list->size--;
    return 0;

}

// user defined function

void data_destroy(void *data) {
    free(data);
}

// printlist function 

void print_list(CList *list){
    CListElmt *current = list->head;
    while(current != NULL){
        //printf("<-(Prev: %p | Address: %p | Data: %d | Next: %p) ->\n",(void *)current->prev,(void *)current,*(int *)current->data,(void *)current->next);
        printf("(Address: %d | Data: %d | Next: %d) ->\n",(int *)current,*(int *)current->data,(int *)current->next);

		current=current->next;
    }
}

int main() {

    CList myList;
    CListElmt *element;
    int *data;

    clist_init(&myList,data_destroy);
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
                clist_ins_next(&myList,NULL,data);
        }
        else {
            // insert aftert the current tail
            clist_ins_next(&myList,clist_tail(&myList),data);

        }

}
printf("List after Insertion\n");
print_list(&myList);



}