# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "list.h"
# include "chtbl.h"

int chtbl_init (CHTbl *htbl, int buckets, int (*h)(const void *key), int (*match)(const void *key1, const void *key2),void (*destroy)(void*data)){

    /*
    Function Paramters:

    CHTbl *htbl : pointer to the hash table structure being initialized - so you can modify the entire structure
    int buckets: number of buckets where each is a linkedlist  
    int (*h)(const void *key): pointer to the hash function
    int (*match)(const void *key1, const void *key2):  pointer to the match function to check if keys are the same for collisions
    void (*destroy)(void *data): deallocation function when elements are removed 
    */

   int i;

   if((htbl->table = (List*)malloc(buckets *sizeof(List)))==NULL){
    /*
     allocate memory for the array of buckets(sizeof list is the total memory size depedning on the elements and data type chosen)
     if cant alloate the memory return -1

     CHTbl *htbl - *htbl is a pointer to the hashtable structure 
     also in chtbl table is a array of linkedlists that points to first element 
     you dont need to use pointers, but better to because we are changing values of the hashtable 
    */
    return -1;
   }

   // initalize the buckets

   htbl->buckets=buckets;

   for(i=0;i<htbl->buckets;i++){
    list_init(&htbl->table[i],destroy);
   }

   // encapsulate the functions

   htbl->h=h;
   htbl->match=match;
   htbl->destroy=destroy;

   // initialize the number of elements in the table 
   htbl->size=0;
   return 0;

}

// destroy function

void chtbl_destroy(CHTbl *htbl){

    int i;

    // destroy each bucket

    for(i=0;i<htbl->buckets;i++){
        list_destroy(&htbl->table[i]);
    }

    // free the storage for the hash table
    free(htbl->table);

    // clear the structure 

    memset(htbl,0,sizeof(CHTbl));

    return;
}

// insertion into hashtable

int chtbl_insert(CHTbl *htbl,const void *data){

    void    *temp;
    int bucket;
    int retval;

    /*
    data is a const void* type so do assign temp to data you need to 
    cast because temp is void*
    */

   // if data is already in the table then do nothing
   temp=(void *)data;

   if(chtbl_lookup(htbl, &temp)==0){
    return 1;
   }

   // hash the key 

    bucket=htbl->h(data) % htbl->buckets;

    // insert the data into the bucket

    if((retval=list_ins_next(&htbl->table[bucket],NULL,data))==0){
        htbl->size++;
    }

    return retval;

}

// chtbl_remove

int chtbl_remove(CHTbl *htbl, void **data){

    ListElmt    *element;
    ListElmt    *prev;

    int         bucket;

    // hash the key 

    bucket = htbl->h(*data) % htbl->buckets;

    //search for the data in the bucket 

    for(element=list_head(&htbl->table[bucket]);element !=NULL;element=list_next(element)){

        // traverse the list 
        // use double pointer because you may remove head 
        if (htbl->match(*data,list_data(element))){
            // remove the data from the bucket

            if(list_rem_next(&htbl->table[bucket],prev,data)==0){
                // NEED A DOUBLE POINTER HERE B/C MAY DELETE VALUE SO NEED TO MODIFY IT
                htbl->size--;
                return 0;
            }

            else{
                return -1;
            }
        }
            prev = element;

    }
    
    // return that the data was not found
    return -1;
}

// chtbl lookup

int chtbl_lookup(const CHTbl *htbl, void **data){

    ListElmt    *element;
    int         bucket;

    // hash the key 
    bucket=htbl->h(*data) %htbl->buckets;

// search for the data in the bucket

for (element = list_head(&htbl->table[bucket]); element !=NULL;element=list_next(element)){

    if(htbl->match(*data,list_data(element))){
        //pass back the data from the table
        *data = list_data(element);
        return 0;
    }
}

// data not found 
return -1;
}


// user defined hash function
/*
you need to do this because, it lets you keep the code flexible, if you just made the mod hash function in here and you change the buckets variable, it
will maybe messs up the mapping, this way keeping them two seperate functions you can allow for correct memory stuff

*/


int hash_function(const void *key){
    // cast the key to a int pointer and then dereference it to get the actual int value
    return *(int *)key;

}


// main function

int match_function (const void *key1, const void *key2){
    /* convert to an integer pointer and then dereference to get the int value and then compare*/
    return *(int*)key1 == *(int *)key2;
}

void destroy_function(void *data){
    free(data);
}


// Function to print the hash table
void print_hash_table(const CHTbl *htbl, void (*print_data)(const void *data)) {
    printf("Hash Table (size = %d, buckets = %d):\n", htbl->size, htbl->buckets);
    for (int i = 0; i < htbl->buckets; i++) {
        printf("Bucket %d: ", i);
        ListElmt *element = list_head(&htbl->table[i]);
        while (element != NULL) {
            print_data(list_data(element)); // Call the user-defined print function
            element = list_next(element);
        }
        printf("\n");
    }
}

// User-defined print function for integers
void print_int(const void *data) {
    printf("%d -> ", *(int *)data); // Print integer data
}
 
int main() {

// declare the hash table
CHTbl htbl;

// total number of buckets in the hash table
int buckets =10;

// initalize the hash table

if(chtbl_init(&htbl, buckets, hash_function, match_function,destroy_function)!=0){
    // doesnt return 0 then it fails to intialize

// chtbl *htbl is a pointer to type chtbl, therefore to get the pointer value do &htbl
// function name is a pointer itself, kinda like how array name is a pointer

fprintf(stderr,"Failed to initialize\n");
return EXIT_FAILURE;
}

// insert elements 

int *data1=malloc(sizeof(int));
*data1=42;
if(chtbl_insert(&htbl,data1)!=0){
    fprintf(stderr,"Failed to Insert the data");
    free(data1);
}


int *data2=malloc(sizeof(int));
*data1=41;
if(chtbl_insert(&htbl,data2)!=0){
    fprintf(stderr,"Failed to Insert the data");
    free(data2);
}


int *data3=malloc(sizeof(int));
*data3=111;
if(chtbl_insert(&htbl,data3)!=0){
    fprintf(stderr,"Failed to Insert the data");
    free(data3);
}

//print the hash table 
print_hash_table(&htbl, print_int);


}