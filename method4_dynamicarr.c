/*

In this method we allocate a block of memory to hold the whole array first. We then
create an array of pointers to point to each row. Thus even though the array of pointers is
being used, the actual array in memory is contiguous. The code looks like this:

method 3 used 1 malloc call for the rows and 5 for the columns
*/

# include <stdio.h>
# include <stdlib.h>

int main (void) {

int **rptr;
int *aptr;
int *testptr;

int k;
int nrows=5;
int ncols=8;
int row,col;

// allocate the memory for the array - the entire thing

/*
basically the below is going to allocate all the memory needed for the array
also when you do malloc, you return a pointer to the first byte of the memory allocated

*/
aptr = malloc (nrows*ncols*sizeof(int));

if (aptr ==NULL){

puts("\nFailure to allocate room for the array");
exit(0);
}

// allocate the room for the pointers to the rows - using the memory space we
// decalred above, allocate room for the pointers to the rows


rptr = malloc(nrows*sizeof(int *));

if(rptr == NULL) {

puts("\nFailure to allocate room for pointers");
exit(0);
}

/*

so basically aptr is a continous block of memory that is not organized into rows and 
cols. by declaring room for pointers using the rptr=malloc() code, you can then point 
these pointers to the parts of aptr

aptr: This is a contiguous block of memory. It contains all the elements of your 2D array 
in a flat, one-dimensional layout. However, it doesn't inherently "know" about rows and 
columns — it's just a sequence of memory locations holding the array elements in a 
continuous manner. For example, if you have a 5x8 array, it is laid out as a sequence of 
40 integers (or whatever data type you're using).

rptr: This is an array of pointers, where each pointer corresponds to the beginning of a 
row in your conceptual 2D array. By allocating memory for these pointers, you are 
creating a structure that allows you to access the 1D block (aptr) as if it were a 2D 
array.

so rptr is going to be an array of pointers where each element is a pointer which will 
point to the aptr to declare rows

the below will just specify memory for the pointers but you still need to put values into 
this space

int ** is usally for a pointer to pointer, but it can also be an array of pointers 
pointing to other pointers for each element, also it can be a single pointer which points 
to an array of pointers

*/



// point the array of pointers to actual pointers using aptr

/*
the below code in the loop is basically going this
rptr[0]=aptr[0] + ncols(8*0) = aptr[0]
rptr[1] = aptr [0] +ncols(8*1)= aptr[8]


therefore aptr, is techncillay just seeting aside memory for us to put the actual values 
of the array in
not the pointers themself like what rptr is doing


*/
for (k=0;k<nrows;k++){
	rptr[k]= aptr+(k*ncols);
}

// illistrate how the row pointers are incremented

printf("\n \n Illistrating how row pointers are incremented");
printf("\n\nIndex Pointer(hex) Diff.(dec)");

for (row=0; row <nrows; row++){

// the below is going to print the address of the row 
printf("\n%d	%p", row,rptr[row]);

//the below is going to show the difference between addresses remember rptr[x] is the
// pointer to the first elemet of the second row 

if (row>0)
	printf("	%d",(rptr[row]-rptr[row-1]));

}


// print the array
printf("\n\nAnd now we print out the array\n");
for (row=0;row<nrows;row++){
	for (col=0; col<ncols;col++){
	
	rptr[row][col]= row+col;
	printf("%d",rptr[row][col]);
}
        putchar('\n');
}
 puts("\n");

/* and here we illustrate that we are, in fact, dealing with
a 2 dimensional array in a contiguous block of memory. */
printf("And now we demonstrate that they are contiguous in memory\n");
testptr = aptr;
for (row = 0; row < nrows; row++)
{
for (col = 0; col < ncols; col++)
{
printf("%d ", *(testptr++));
}
putchar('\n');
}
return 0;
 
}
