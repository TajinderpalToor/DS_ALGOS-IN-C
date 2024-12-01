#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int x_dim=16;
int y_dim=5;
int z_dim=3;

int main (void) {

char *space;
char ***Arr3D;

int y,z;

/*

ptrdiff_t is a signed integer type defined in the <stddef.h> header (which is included in 
your code). It is used to represent the difference between two pointers.

Purpose: The primary purpose of ptrdiff_t is to hold the result of pointer subtraction 
(i.e., the difference between two pointers). Since pointer arithmetic can result in 
negative values (for example, if the first pointer points to an element that comes after 
the second pointer in memory), ptrdiff_t is signed to accommodate these cases.
Usage: It is particularly useful when you want to determine how many elements are between 
two pointers or to compute the index differences in an array.

*/
ptrdiff_t diff;

// set aside space for the entire array itself
// the below will make a continous block of memory of 240 char blocks (16*5*3)

space = malloc(x_dim*y_dim*z_dim*sizeof(char));

/*
 next allocate space for an array of pointers where there are3 pointers
the first one is a row of pointers, where each point to the first element of a 2d array

3d - array is z number of 2d arrays, so basically the way the ***Arr3D works is that it first points to an array of pointers 
( number of z dimensions), each of these memory spots points to a 2d array, which is the first element in that array 
arr3d[0][0], this will point to the first row which is a 1d array, then you can just use pointer arithmetic to traverse the 
specfic 2d array

*/
Arr3D=malloc(z_dim*sizeof(char **));
/*
for each of the array of pointers (z dimension) assign the pointer to the first row of the 2d array
*/

for (z=0;z<z_dim;z++){
Arr3D[z]= malloc (y_dim *sizeof(char*));

// pointer to the first element of each row in the array space origianlly located

/*

Arr3D[z][y] = space + (z * (X_DIM * Y_DIM) + y * X_DIM);

Formula Breakdown:
z * (X_DIM * Y_DIM):

Purpose: This calculates the starting position (offset) of layer z in the continuous block space.
Why:
In a 3D array, each "layer" or "slice" (2D array) has X_DIM * Y_DIM elements.
So, for layer z, the memory offset is calculated by multiplying z by the total number of elements in each 2D array.
Example:
If X_DIM = 3 and Y_DIM = 3, each 2D array has 9 elements (3 rows × 3 columns).
For z = 0, the offset is 0 * 9 = 0 (the first layer starts at element 0).
For z = 1, the offset is 1 * 9 = 9 (the second layer starts at element 9).
This tells you where each 2D array (layer) starts in the block of memory space.
y * X_DIM:

Purpose: This calculates the starting position of row y within the current layer z.
Why:
In each 2D array (layer), you have Y_DIM rows, and each row has X_DIM elements.
So, to find the start of row y in layer z, you need to skip over y * X_DIM elements from the start of the layer.
Example:
If X_DIM = 3, each row has 3 elements.
For y = 0, the offset is 0 * 3 = 0 (the first row starts at element 0 of the layer).
For y = 1, the offset is 1 * 3 = 3 (the second row starts at element 3 of the layer).
This tells you where each row starts within the layer.
Full Formula:
z * (X_DIM * Y_DIM): This shifts the pointer to the start of layer z in the block space.
y * X_DIM: This shifts the pointer further to the start of row y within that layer.
Result: The expression space + (z * (X_DIM * Y_DIM) + y * X_DIM) gives the starting address of row y in layer z within the 
continuous memory block space.
Example with Concrete Values:
Let’s say:

X_DIM = 4 (each row has 4 elements)
Y_DIM = 3 (each layer has 3 rows)
Z_DIM = 2 (there are 2 layers)
The continuous memory block space holds 4 * 3 * 2 = 24 elements.

For z = 0 (Layer 0):
The offset for the start of layer 0 is 0 * (4 * 3) = 0.
Now, within layer 0:
For y = 0, the offset for row 0 is 0 * 4 = 0. So, Arr3D[0][0] points to space + 0.
For y = 1, the offset for row 1 is 1 * 4 = 4. So, Arr3D[0][1] points to space + 4.
For y = 2, the offset for row 2 is 2 * 4 = 8. So, Arr3D[0][2] points to space + 8.
For z = 1 (Layer 1):
The offset for the start of layer 1 is 1 * (4 * 3) = 12.
Now, within layer 1:
For y = 0, the offset for row 0 is 0 * 4 = 0. So, Arr3D[1][0] points to space + 12.
For y = 1, the offset for row 1 is 1 * 4 = 4. So, Arr3D[1][1] points to space + 16.
For y = 2, the offset for row 2 is 2 * 4 = 8. So, Arr3D[1][2] points to space + 20.
Summary:
Arr3D[z][y] points to the start of row y in layer z.
The formula shifts the pointer through the continuous memory space based on the number of elements in previous layers (z) 
and rows (y).
Once you have these pointers, you can access elements using pointer arithmetic for the individual elements of each row.


so basically ***arr3d, first pointer points to an array of pointers, now were left with a double pointer. this double 
pointer points to a  2d array(dimensions of each layer), now this 2d array pointer leaves a single pointer which points to a 
1d array representing the columns






 */
for (y=0;y<y_dim;y++){

Arr3D[z][y] = space + (z*(x_dim*y_dim)+ y*x_dim);
}
}

/* And, now we check each address in our 3D array to see if
the indexing of the Arr3d pointer leads through in a
continuous manner */
for (z = 0; z < z_dim; z++)
{
printf("Location of array %d is %p\n", z, *Arr3D[z]);
for ( y = 0; y < y_dim; y++)
{
printf(" Array %d and Row %d starts at %p", z, y,
Arr3D[z][y]);
diff = Arr3D[z][y] - space;
printf(" diff = %d ",diff);
printf(" z = %d y = %d\n", z, y);
}
}
return 0;


}
