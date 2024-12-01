# include <stdio.h>
# include <stdlib.h>

int main (void) {

    int **rptr; // double pointer to rptr

    int *aptr; // single pointer to aptr

    int *testptr;

    int k;

    int nrows = 5;
    int ncols=8;
    int row,col;

 // allocate the memory for the entire array

    aptr= malloc(nrows*ncols*sizeof(int));
    if(aptr=NULL){
        puts("\nFailure to allocate room for the array");
        exit (0);
    }

    // allocate the memory for the pointers to the rows
    // basically rptr is a double pointer, each pointer points to anotehr pointer which is the column valeues basically
    rptr = malloc(nrows*sizeof(int));

    if(rptr=NULL){
        puts("\nFailure to allocate room for the pointers");
        exit (0);
    }

    /*
    Now point the pointers. also when you do malloc you are assigning memory but it also makes a variable to the 
    first byte in the memory you assigned. in the below: aptr is the memory of the first byte of the array, so that location
    plus k*numcols you get the stuff for the first row. ex.

    so you are basically starting at the begining of the array, then adding the memory of the cols
    
    rptr[0] = aptr + 0*ncols(ncols=8) = aptr[0]
    rptr[1] = aptr + 1*ncols(ncols=8) = aptr[8]
    rptr[0] = aptr + 2*ncols(ncols=8) = aptr[16]
    */



}