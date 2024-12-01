#include  <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// declare the structure of the node - ie each node has a 
// data

struct node {

int data;
int key;

// the line  below is the  pointer to another struct node which is the next one
struct node*next;

};

// initially the linked list is empty so the head doesnt point to anything

struct node*head=NULL;
struct node*current=NULL;

void printlist(){

// -> allows you to access the member variables of a struct when you have
// a pointer to that struct 

// so if you have a struct and the list is initally empty you have the
//head pointing to it , so create a pointer that has the adress of the
// head because iniitally it is empty  and this will be null initially because there is nothing in it

struct node *ptr=head;

printf("\n[");

// start from the head and stop at the tail which points to null

while(ptr!=NULL){
printf("(%d,%d)",ptr->key,ptr->data);

ptr=ptr->next;
}

printf("]");

}

// insert into linked list at the first spot

void insertFirst(int key, int data){

// create a link, ie. the new node
// to be able to acess the items of the struct we have to create a pointer to it 

//create the pointer to this new node by first declaring some memory using
//  malloc and then converting the type
struct node *newnode=(struct node*)malloc(sizeof(struct node));

newnode-> key=key;
newnode->data=data;

// now since this is the first node it must point to the old
//first node which is the old head

newnode->next=head;
head=newnode;
}

//deletefirst

struct node* deletefirst(){

//deleting the first  link which is the head so save the  reference 
// to this link

struct node*tempLink=head;

// since deleting the first node, the second node is now the head,
// which is the next of our current head 

head=head->next;

//return deleted link
return tempLink;

}

// is list emoty, ie. no head

bool isEmpty(){
return head==NULL;
}

// get length of the linkedlist

int length() {

int length=0;
struct node *current;

for(current=head;current!=NULL;current->next){
length++;
}

return length;
}


// delete link given a key

struct node* delete(int key){

// start from first key - ie. first key is the head so current = head
// no previous

struct node* current=head;
struct node* previous=NULL;

// if list empty

if (head=NULL){
return NULL;
}

//navigating through the list 

while(current->key!=key){

// if it is last node -- ie. we traversed and did not find the key at all
if (current->next == NULL) {
return NULL;
}

else {

// store reference to the current link, current is now the previous 

previous=current;

//move to next link which is now the current
current=current->next;

}

}

if (current==head){
// if the certain key you want to delete is the head, the second link is now the head

head=head->next;

}

else{
// if not the head and the desired key is  the current one, link the previous 
//node to the  currents(deleting) nodes  next node

previous->next=current->next;
}

return current;
}


void reverse(struct node** head_ref){

// so ** is a pointer to a pointer, so the first pointer stores the address of the variable, the second pointer (ie. the pointer to the pointer 
//has the adress of the pointer) so we can use the second pointer(ie. **) to change the adress of that adress

struct node* prev=NULL;
struct node*current = *head_ref;
struct node* next;

while(current !=NULL){

next= current->next;
current-> next=prev;
prev=current;
current=next;
}
*head_ref=prev;




}
void main(){

insertFirst(1,10);
insertFirst(2,20);
insertFirst(3,30);
insertFirst(4,1);
insertFirst(5,40);
insertFirst(6,56);
printf("Original List: ");
 //print list
 printlist();

while(isEmpty()){
struct node *temp=deletefirst();
printf("\nDeleted Value:");
printf("(%d,%d)",temp->key,temp->data);
}
printf("\nList after deleting all items:");
printlist();
}



