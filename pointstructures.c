# include <stdio.h>
# include <string.h>


struct tag {

char lname[20];
char fname[20];
int age;
float rate;

};


struct tag my_struct; // declare the structure my_struct

int main (void) {

/*

struct tag {
	char lname[20]; // last name 
	char fname[20]; // first name 
	int age; // age 
	float rate; // e.g. 12.75 per hour 
};



// lets say there is a bunch of structures in a disk file, and you want to read each file and 
//print first/last name so that you can have a list of the different things on the disk, make a 
//function and pass a pointer to the structure in it

In the earlier versions of C, you were not able to pass the strcture, only a pointer to the 
structure 

*/



// fill in the struct
strcpy(my_struct.lname,"Jensen");
strcpy(my_struct.fname,"Ted");
printf("\n%s",my_struct.fname);
printf("%s\n",my_struct.lname);

// the data types structure is struct so make a pointer to that 

struct tag *st_ptr;
st_ptr= &my_struct;

/*


Structure Type: struct tag is the name of the structure type. Just like you can have an int or float variable, struct tag is the type for your structure variable.

Pointer Declaration: struct tag *st_ptr; declares a pointer variable st_ptr that can hold the address of a structure of type struct tag. The *st_ptr part means that st_ptr is a pointer capable of referencing a struct tag object.

Address of the Structure: The expression &my_struct gives you the memory address of the my_struct variable. The & operator is used to obtain this address.

Pointer Assignment: When you do:

c
Copy code
st_ptr = &my_struct;
you’re assigning the address of my_struct (which is &my_struct) to the pointer st_ptr. Now, st_ptr points to the memory location where my_struct is stored.


*/


/*

then doing, *st_ptr will dereference and give you the actual values of the structure
then you can use the .whatever to get the value 

*/
// below is the same as my_struct.age
int age=(*st_ptr).age;

// aklternative to the above is st_ptr -> 63;



return 0;

}

