// pointer is also 4 bytes

// **q is a pointer to pointer, but the type has to match the first like if p is a pointer that points to an int, q must also be an int, pointer to pointer to pointer is ***z

# include <stdio.h>

int main(){

    int x;
    x=10;
    int *p=&x;

    //pointer to pointer
    int **q;
    q=&p;

    //pointer to pointer to pointer
    int ***r;
    r= &q;

    printf("The address of variable  'x' is %p\n", (void*)p);
    printf("The value of variable  'x' is is %d\n", *p);

    printf("The address of  'pointer p' is %p\n", (void*)q);
    printf("The value of 'pointer p' is is %p\n", *q);

    printf("The address of  'pointer q' is %p\n", (void*)r);
    printf("The value of 'pointer q' is is %p\n", *r);


    // dereferencing using the pointers -- change the variable x value using q(pointer to pointer)

    **q=699;
        printf("The value of  'x' after dereferencing using **q is %d\n",**q);

    // dereferencing using the pointer to pointer to pointer

    ***r=500;

    printf("The value of 'x' after dereferencing using ***r is %d\n", ***r);
    return 0;
}