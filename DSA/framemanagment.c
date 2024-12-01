/*
Frame Managment -> Example Use of Linked Lists 

linked lists is found the in the way some systems support 
virtual memory in computers

virtual memory = mapping of address spoaces that 
allows a process to exucute wihtout 
being completley in physical memory

virtual memory is good, processes can make use of address spance
that is much larger than physical memory will allow.

also multiple proccesses can share the memory of the system while running
concurrently

Virtual Addresses:
- seem like physical addresses to the process but the system 
must translare before using 

- Address translation takes place using a page 
table and is fast due to dedicated hardware

- each process has its on page table that maps virtual address
pages to frames in physical memory 

- when process references a particular virtual address, 
the appropriate entry in its page table is inspected to determine in 
which physical page the frame resides 

Address Managment of Frames:

- Has Two Functions: alloc_frame and free_frame 

- both these functions employ a linked list to maintain the 
frames that are avaiable to be allocated

alloc_frame:
- retrieved the number of a free frame from a list of avaiable frames
- given a specific page, this number is placed in the page table to indicate in which physical 
frame the page resides to 

free_frame:
- accepts a frame number and places it back into the list of
available frames once a page has been removed from physical memory



got it so basically every process has virtual addresses, these virtual addresses must be translated to physical addresses

each process has a virtual memory which basically has a page number and the virtual address associated with that page number

then you reference the page table, this page table has page entries and each entry tells you which physical memory frame has the virtual address

ex. in virtual memory: page 0 = A
in page table, page 0 has 51

so in physical memory frame 51 must have A


but lets say then you have something in virtual memory like page entry 40 has E, when you go to the page table and entry page 40, but there is no frame there it gets a page fault

so to handle this we must see an available frame to assign it, this is done using the alloc_frame method. so we keep popping frames until one is succusful. we pop because this means its not avaiable anymore

 free frame push the frame that is avaiable now back in

*/
#include <stdio.h>
# include <stdlib.h>
# include "frames.h"
# include "list.h"
#include <string.h>

void list_init(List *list, void (*destroy)(void *data)) {

// arrow is another way to do pointers, dereferencing and then getting value 

list ->size=0;
list ->destroy=destroy;
list -> head = NULL;
list -> tail = NULL;

return;

}

int alloc_frame(List *frames) {
    int     frame_number;
    int     *data;

    if(list_size(frames) ==0) {
        // no frames avaiable
        return -1;
    }

    else {
        // if the below function has a paramter element=null then you are removing
        //the head is being removed 
        // but remember if list_rem_next is -1 if unsucessful 

        if(list_rem_next(frames,NULL, (void**)&data)!=0){
            // frame could not be retrieved 
            return -1;
        }
    
        else {
            frame_number = *data;
            free(data);
        }
    }
    return frame_number;
}

int free_frame(List *frames, int frame_number) {

int         *data;

//allocate storage for the frame number.

if((data=(int *)malloc(sizeof(int)))==NULL){
    return -1;
}

// put the frame back in the lists of available frames

*data=frame_number;

if(list_ins_next(frames,NULL,data)!=0){
    return -1;
}

return 0;

}

void print_frames(List *frames) {
    ListElmt *element = list_head(frames);
    int *data;

    printf("Available frames: ");
    while (element != NULL) {
        data = list_data(element);
        printf("%d ", *data);
        element = list_next(element);
    }
    printf("\n");
}

void list_destroy(List*list){

void	*data;

// remove each elemenet

while(list_size(list)>0){

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

int main() {
    // initialize the list of frames
    List frames;
    list_init(&frames,free);

    // add some frames to the list - numbered 1 to 5
    for (int i=0; i<=5;i++) {
        // assing memory using malloc and convert it to int pointer
        int *frame = (int *)malloc(sizeof(int));
        *frame=i;
        list_ins_next(&frames,NULL,frame);
    }
    // print the list of frames - initial
    printf("initial ");
    print_frames(&frames);

    // Test: Allocate a frame
    int frame_number = alloc_frame(&frames);
    printf("Allocated frame: %d\n", frame_number);
    print_frames(&frames);

    // Test: Allocate another frame
    frame_number = alloc_frame(&frames);
    printf("Allocated frame: %d\n", frame_number);
    print_frames(&frames);

    // Test: Free a frame
    printf("Freeing frame 4...\n");
    free_frame(&frames, 4);
    print_frames(&frames);

    // Test: Free another frame
    printf("Freeing frame 5...\n");
    free_frame(&frames, 5);
    print_frames(&frames);

    // Destroy the list when done
    list_destroy(&frames);

    return 0;
}
