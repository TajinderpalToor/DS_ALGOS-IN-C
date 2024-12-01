// Chapter 8 - Pointers and Dynamic Allocation of Memory

# include <stdio.h>
# include <stdlib.h>
# define COLS 5
/*

allocate memory using malloc() or calloc()
this way you can use a section of memory for stuff and then release it when you dont need 
it

malloc or calloc return a pointer, can be a char (older versions) or void ( newer c 
compilers)

it can be hard to do dynamic allocation the array at first so this lesson teaches that. 
dynamic allocation is when memory is allocated at runtime and its size can be changed 
later in the program 

when dynamically allocating arrays, you only need to know the first dimension at compile 
time


*/ 

typedef int RowArray[COLS]; // datatype RowArray which is 5 elements 
RowArray *rptr; // pointer to the above so pointer to an array of 5 integers, pointer to 5 
//integers so it is of type int(*)[5] 

int main(void) {

// Method 1 : remember rptr is a pointer, but the array rptr is also a pointer
// ex. arr 
int nrows=10;
int row, col;
rptr= malloc(nrows*COLS*sizeof(int)); // this can help us make a 2d array, 10 rows each 
//with 5 cols

for (row=0;row<nrows;row++){

for (col =0;col<COLS;col++){

// below is equivalent to the pointer notation which is *(*(rptr + row) + col)
rptr[row][col] =17;

}

}

/*
int (*xptr)[COLS]; = a pointer to an array of sizze 3
int *xptr[COLS]; = an array of pointers, if the array has a b and c, this will result in
(&a,&b,&c)


*/

// method 3 - you dont know the number of elements in each row, so you dont know cols so 
//they must be determined at run time - to do this create an array of pointers and then 
// allocate space for these rows and then point these pointers at each row



 return 0;



}
