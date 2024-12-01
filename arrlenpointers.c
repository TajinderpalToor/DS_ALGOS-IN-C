
# include <stdio.h>

int main(){
/*
arr = pointer to the first element of the array. ex = int*
&arr = pointer to the entire array. ex = (int(*)[5])

&arr +1 = points to the memory location right after the array, not the same as pointing to an individual 
element, by dereferencing you get the first element past the end of the array, which is a normal integer int*



arr → pointer to the first element of the array (int *)
&arr → pointer to the entire array (int (*)[5])

Since &arr is a pointer to the entire array, &arr + 1 points to the memory location immediately after the array.

*(&arr + 1) - arr gives the number of elements between these two pointers, which is exactly the length of the array.

arr:

arr is an array name that decays to a pointer to its first element when used in most expressions (like function calls or pointer arithmetic).
For example, if you have int arr[] = {2, 3, 4, 5};, then arr decays into a pointer of type int *, pointing to the first element of the array (arr[0]).
Its value is the memory address of arr[0].
&arr:

&arr is a pointer to the entire array. Its type is int (*)[4] if arr has 4 elements.
Although &arr points to the same memory location as arr, it is treated as a single unit pointing to the whole array, not just the first element.
The type and semantics of &arr are different from arr. &arr is of type int (*)[4], whereas arr (or &arr[0]) is of type int *.

arr (or &arr[0]) is of type int * and behaves like a pointer to the first element.
&arr is of type int (*)[4] (for an array of 4 ints) and is treated as a pointer to an array.

- so basically arr is the pointer to the first element so technically similar to arr[0], also this is a type int* (pointer to an element), now &arr points to the whwhole array, so like its type is not pointer to an element, instead int (*) [4] if there are 4 elements. they will have the same address, b/c arr points to first elelement and &arr is the whole array starting at first element . &arr+1 points to the entire array plus the size of the element ( example. if the array is 4 elelements of int the pointer moves the size of the array plus 4 bytes for int) instead arr+1, which will point to arr[1]. also if your array has 4 elements, then &arr+1 will point to arr + 4. which is the fifth element, b/c four elements is 0-3. so then because it points to the element after the array this is not an pointer to an element, by dereferncing it becomes a pointer to an element which points to memory location one spot after array, if you subtract this from first element memory location you can get size

Yes, &arr + 1 is the address right after the entire array. However, in order to perform pointer arithmetic to compute the array length, you need to dereference it (*(&arr + 1)) to turn it into a pointer to an element of the array, rather than a pointer to the array itself.

Why Dereference? (*(&arr + 1)):

When you use *(&arr + 1), you’re converting the pointer to the entire array into a regular pointer to an element (int *). After dereferencing, *(&arr + 1) gives you a pointer to the first element past the end of the array, which is just a normal integer pointer (int *).
Without dereferencing, &arr + 1 is still a pointer to an array (int (*)[5]), and pointer arithmetic operations with an int (*)[5] and an int * are not compatible.
*/
int arr [ ] = {2,3,4,5};
printf("%d\n",arr); // pointer to first element int *
printf("%d\n",&arr); // pointer to the entire array (int (*) [])

printf("%d\n", (&arr +1)); // points to the memory location right after the array
printf("%d\n", *(&arr +1)); //dereferencing changes it to a pointer to an element 

printf(*(&arr + 1) - arr);





}
