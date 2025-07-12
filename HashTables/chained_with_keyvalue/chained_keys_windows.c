# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "../list.h"
# include "chtblKey.h"

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

   htbl->buckets=buckets;
   htbl->h=h;
   htbl->match=match;
   htbl->destroy=destroy;
   // initialize the number of elements in the table 
   htbl->size=0;

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

   

   for(i=0;i<htbl->buckets;i++){
    list_init(&htbl->table[i],destroy);
   }

  
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

int chtbl_insert(CHTbl *htbl,void *key, void *value){

    int bucket;
    bucket=htbl->h(key) % htbl->buckets;

   // check if the key is in the linkedlist.. ie. traverse the list
   ListElmt *element = list_head(&htbl->table[bucket]);

   while(element!=NULL){
    keyvaluepair *pair = (keyvaluepair *)list_data(element);
    if(htbl->match(pair->key,key)){
        //if true key already exsists update value
        pair -> value=value;
        return 0;
    }
    element=list_next(element);
   }
   // key does not exsist in that linkedlist 
   keyvaluepair *newpair = (keyvaluepair *)malloc(sizeof(keyvaluepair));
   if(newpair ==NULL){
    return -1; // memory not created properly
   }
   newpair->key=key;
   newpair->value=value;
    // insert the data into the bucket
    if((list_ins_next(&htbl->table[bucket],NULL,newpair))!=0){
        // insert failed
        free(newpair);
        return -1;
    }
    htbl->size++;
    return 0;
}

// chtbl lookup

void *chtbl_lookup(const CHTbl *htbl, void *key){
    int bucket;
    // hash the key 
    bucket=htbl->h(key) %htbl->buckets;

// search for the data in the bucket
ListElmt *element = list_head(&htbl->table[bucket]);
while (element !=NULL){
    keyvaluepair *pair = (keyvaluepair *)list_data(element);
    if(htbl->match(pair->key,key)){
        return pair-> value;
    }
    element = list_next(element);
    }
// data not found 
return NULL;
}


// user defined hash function
/*
you need to do this because, it lets you keep the code flexible, if you just made the mod hash function in here and you change the buckets variable, it
will maybe messs up the mapping, this way keeping them two seperate functions you can allow for correct memory stuff

*/

// removal

int chtbl_remove(CHTbl *htbl, void *key) {
    int bucket = htbl->h(key) % htbl->buckets;
    ListElmt *element = list_head(&htbl->table[bucket]);
    ListElmt *prev = NULL;

    // Traverse the bucket to find the key
    while (element != NULL) {
        keyvaluepair *pair = (keyvaluepair *)list_data(element);
        if (htbl->match(pair->key, key)) {
            // Key found, remove it
            void *data = NULL;
            if (list_rem_next(&htbl->table[bucket], prev, &data) == 0) {
                if (htbl->destroy != NULL) {
                    htbl->destroy(data);
                }
                htbl->size--;
                return 0;
            } else {
                return -1; // Removal failed
            }
        }
        prev = element;
        element = list_next(element);
    }

    return -1; // Key not found
}


// Define hash and match functions for strings
int string_hash(const void *key) {
    const char *str = (const char *)key;
    int hash = 0;
    while (*str) {
        hash = (hash * 31 + *str) % 1000000007;
        str++;
    }
    return hash;
}
// match function
int string_match (const void *key1, const void *key2){
    /* convert to an integer pointer and then dereference to get the int value and then compare*/
        return strcmp((const char *)key1, (const char *)key2) == 0;
}

// destroy pair 
void destroy_pair(void *data) {
    keyvaluepair *pair = (keyvaluepair *)data;
    free(pair->key);
    free(pair->value);
}

// Function to print the hash table
void chtbl_print(const CHTbl *htbl, void (*print_pair)(const keyvaluepair *)) {
    printf("Hash Table (size = %d, buckets = %d):\n", htbl->size, htbl->buckets);

    for (int i = 0; i < htbl->buckets; i++) {
        printf("Bucket %d: ", i);

        ListElmt *element = list_head(&htbl->table[i]);
        while (element != NULL) {
            keyvaluepair *pair = (keyvaluepair *)list_data(element);
            print_pair(pair); // Call the user-provided function to print the key-value pair
            element = list_next(element); // Move to the next node
        }

        printf("\n");
    }
}

 void print_key_value_pair(const keyvaluepair *pair) {
    printf("(%s -> %s) ", (char *)pair->key, (char *)pair->value);
 }

int main() {

// declare the hash table
CHTbl htbl;

// total number of buckets in the hash table
int buckets =5;

// initalize the hash table - doesnt return 0 then it fails to intialize

if(chtbl_init(&htbl, buckets, string_hash, string_match,destroy_pair)!=0){
    fprintf(stderr,"Failed to initialize\n");
    return EXIT_FAILURE;
}

// insert  key - value pairs  
chtbl_insert(&htbl,strdup("Name"),strdup("TajinderpalToor"));
chtbl_insert(&htbl,strdup("Age"),strdup("28"));
chtbl_insert(&htbl,strdup("Country"),strdup("Canada"));
chtbl_insert(&htbl,strdup("Sex"),strdup("Male"));


//print the hash table 
chtbl_print(&htbl, print_key_value_pair);

//lookup a key
char *key ="Name";
printf("\nLooking up '%s': %s\n", key, (char *)chtbl_lookup(&htbl, key));

// Remove a key
printf("\nRemoving 'Age'\n");
chtbl_remove(&htbl, "Age");
chtbl_print(&htbl, print_key_value_pair);

// Destroy the hash table
chtbl_destroy(&htbl);

return 0;


}