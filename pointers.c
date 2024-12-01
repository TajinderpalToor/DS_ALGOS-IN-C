#include <stdio.h>

int main() {
    int a;
    int *p;
    a=10;
    p = &a;
    
    // print the address of a
    printf("The address of variable  'a' is %p\n", (void*)p);


    // print the value of a

        printf("The value of variable  'a' is %d\n", *p);


    // below is dereferencing -- changing the value of the variable that pointer is pointing to using the pointer

    *p=12;

    printf("The value of variable  'a' after dereferencing is %d\n", *p);



    //changing the value of a using another integer

    int b=69;
    // address of b

    int *p1=&b;
    *p=b;
    printf("The address of variable  'b' is %p\n", (void*)p1);
    printf("The value of variable  'a' is %d\n", *p);

    // you can do pointer atithmetic, so p+1 is going to be the address of p plus 1 times how many ever bytes are in an integer(or whatever datatype you have), you can only do addition or subtraction

    printf("The size of integer is %zu bytes\n",sizeof(int));
    printf("Address of p is : %p\n",(void*)p);
    printf("The address of p+1 is %p\n:",(void*)(p+1));
  
  // you can reach any address, but a 

  // generic pointer type - does not identify with a certain pointer type 

  void *p5;
  p5=p; // this is valid we dont need to do any casting because p5 is a void pointer so it takes any datatype
  // for void pointers, since it is not attached to any datatype you cant dereference (*p5 wont work to get value), so can only get addresses
  
    return 0;
}
