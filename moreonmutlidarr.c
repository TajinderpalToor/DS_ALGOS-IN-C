// chapter 7


/*


Yes, when working with 2D arrays in C, it's true that you are not required to specify the 
number of rows in a function parameter, but you must specify the number of columns. This 
is because in a 2D array, each row is treated as a contiguous block of memory. If the 
number of columns is known, the compiler can correctly calculate the position of any 
element using pointer arithmetic.



*/

// CHAPTER 8 - POINTERS TO ARRAYS

/*

lets say you have an array p;

in the below you are passing a pointer to the array, specifically the first element 
void a_func( int *p)

or

void a_func(int p[ ] ) - it is the same as passing the pointer to the first element 
because c counts p as the pointer as the first element which is same as p[]


passing p[i] is the same as *(p+i)


b/c when working with two dimensional pointers your type is usually something special. for 
example a[5][10], a[0] would point to an array of 10 integers, so you must have a type to 
that element of 10 integers, you can use typedef

for example

typedef int Array[10]; -- Array becomes a data tyope for an array of 10 integers

Therefore:

Array myarr == myarr is an array of 10 integers
Array arr2d[5] == arr2d is an array of 5 arrays of 10 integers each 

Array *p1d == pointer to an array of 10 integers
because the above gives an array of 10 integers you can assign it to arr2d, because arr2d 
points to arr2d[0] which is 10 integers

p1d=&arr2d[0] or p1d = arr2d

you dont need the typedef keyword you can do 

int (*p1d)[10]

*/
