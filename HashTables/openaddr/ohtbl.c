# include <stdlib.h>
# include <string.h>

#include "ohtbl.h"

// reserve a sentinel memory addres for vacated elements

static char vacated;

// ohtbl_init

int ohtbl_init(OHTbl *htbl, int positions, int (*h1)(const void *key), int
 (*h2)(const void *key), int (*match)(const void *key1, const void *key2),
 void (*destroy)(void *data)) {

    int i;

    //allocate space for the hash table
    if ((htbl->table = (void **)malloc(positions * sizeof(void *))) == NULL) {
        return -1;
    }

    //initalize each position

    htbl->positions =positions;

    for(i=0;i<htbl->positions;i++){
        htbl->table[i]=NULL;
    }

    htbl->vacated = &vacated;

    // encapsulate the functions
    htbl->h1=h1;
    htbl->h2=h2;
    htbl->match=match;
    htbl->destroy=destroy;
 
 // initalize the number of elements in the table

 htbl->size=0;
 return 0;
 
 }

 // destroy function

 void ohtbl_destroy(OHTbl *htbl){
    int i;

    if(htbl->destroy!=NULL){
        // call user defined function to free dynamically allocated storage

        for(i=1;i<htbl->positions;i++){
            if(htbl->table[i]!=NULL && htbl->table[i]!= htbl->vacated){
                htbl->destroy(htbl->table[i]);
            }
        }
    }

    // free the storage allocated
    free(htbl->table);

    memset(htbl,0,sizeof(OHTbl));
    return;
 }

 //ohtbl_insert

 int ohtbl_insert(OHTbl *htbl,const void *data){

    void *temp;
    int position;
    int i;

    // do not exceed the number of positions
    if(htbl->size == htbl->positions){
        return -1;
    }

    //do nothing if the data is in the table
    temp=(void *)data;

    if(ohtbl_lookup(htbl,&temp)==0){
        return -1;
    }

    // use double hashing to hash the key

    for(i=0;i<htbl->positions;i++){

        position= ( htbl->h1(data)+(i*htbl->h2(data))) %htbl->positions;

        if(htbl->table[position]==NULL || htbl->table[position]==htbl->vacated){
            //insert the data into the table
            htbl->table[position]=(void *)data;
            htbl->size++;
            return 0;
        }

        // return that the hash functions were selecteed incorrectly
        return -1;
    }
 }

 //ohtbl remove

int ohtb_remove(OHTbl *htbl,void **data){
    
int position;
int i;

// use double hashing to hash they key
for (i=0;i<htbl->positions;i++){
    position =(htbl->h1(*data) + (i *htbl->h2(data)))%htbl->positions;

    if(htbl->table[position]==NULL){
        //return that the data was not found
        return -1;
    }

    else if (htbl->table[position]==htbl->vacated){
        // search beyond vacated positions
        continue;
    }

    else if (htbl->match(htbl->table[position],*data)){
        *data =htbl->table[position];
         htbl->table[position]=htbl->vacated;
         htbl->size--;
         return 0;
    }

    // data was not found
    return -1;
}

}

//ohtbl lookup

int ohtbl_lookup(const OHTbl *htbl, void **data){
    int position;
    int i;

    //use double hashing to hash the key

    for(i=0;i<htbl->positions;i++){
        position = (htbl->h1(*data) + (i*htbl->h2(*data))) % htbl->positions;

        if(htbl->table[position]==NULL){
            // return that the data was not found
            return -1;
        }
    
        else if(htbl->match(htbl->table[position],*data)) {
            // pass back the data from the table
            *data =htbl->table[position];
            return 0;
        }
    
    }

    //return that the data was not found
    return -1;
}