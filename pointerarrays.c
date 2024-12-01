# include <stdio.h>


int main () {

// need to identify the type of variable that a pointer points to, so that the compiler knows how many bytes to copy into the location pointer by 
// the pointer 

//pointer arithmetic, when you do ptr+1, your not adding one your going to the next memory location. so for example if you have integer, that is 
// 4 bytes so ptr+1 is the current pointer address plus 4 bytes, so that is why the type is important 

// lets say you have 10 memory locations of 4 bytes, ptr+1 would take you to the next block in the memory, these 10 memory locations in a row are 
// basically the same as an array 

int my_array [ ] ={1,23,17,4,-5,100};

// use the above theory to test the pointers in here ( should be 4 bytes apart)

int *ptr;
ptr  = & my_array[0];
//printf(" %d \n", *ptr);

//print the array

printf("Below is the Value of the Arrays");

for(int i=0;i<6;i++){
	printf("my_array[%d] = %d\n",i,my_array[i]);
}




// print the value of the array using dereferencing 
printf("The value of the array using pointer dereferencing is:");

for ( int i=0;i<6;i++){
	printf("my_array[%d] using ptr + %d equals %d\n",i,i,*(ptr+i));
}

}

// ptr=&my_array[0] is the same as ptr=my_array, this means that the name of the array is a pointer, the name of the array can 
then be thought of as the address of the first element


