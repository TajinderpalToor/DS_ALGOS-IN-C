// Chapter 6: Some more on Strings and Arrays of Strings:

# include <stdio.h>


/*

so you can delcare a string by two ways 

1. char my_name [] = "ted";

2. char *my_name="ted";


In the first option - array notation you are using 4 bytes of storage ( one byte for each character and then also an extra
byte for the null terminator 

In option 2 you are using the pointer notation, which basically needs to store the same 4 
bytes for the data and null terminator, but also needs to have data to store the ( N 
bytes) to store the pointer variable my_name, my_name is the same as myname[0]


b/c the array notation, a array is fixed it is constant not a variable
but in  the pointer notation my_name is a variable 



*/


// see what happens if the above declerations are done in a function instead globally  outside a function 

void my_function_A (char *ptr)

{

char a [] = "ABCDE";

}

void my_function_B ( char *ptr) {


char *cp= "FGHIJ";

}

/*

the result oif my_function_A the array will be store on the stack: the stack usually holds 
local variable, the contents of the array are considered data, and the data is local to 
the function which is stored on the stack

the result of my_function_B, the value of the pointer cp is data and will be stored on the 
stack, while the string FGHIJ that is being assigned to the pointer can be stored anywhere

// declaring something in a function without the static keyword are considered automatic 
variables automtic variables have the following properties:

The contents of the array a in the function my_function_A are stored in the stack because 
a is a local variable defined inside the function. In C, variables declared inside a 
function without the static keyword are considered automatic variables. Automatic 
variables have the following properties:

Lifetime and Scope: They are created when the function is called and destroyed when the 
function returns. Their scope is limited to the function in which they are declared.

Memory Storage: By default, these variables are stored in the stack. The stack is a 
specific region of memory used for storing function call frames, including local 
variables, return addresses, and other function-specific data.

Stack Allocation: Arrays declared inside a function, like char a[] = "ABCDE";, are 
automatically allocated on the stack. The size of the array (a) is determined at 
compile-time based on the initial value (ABCDE), which is 6 bytes in this case (5 
characters plus a null terminator \0).

Why Not Heap or Static Memory?
The stack allocation is different from the heap or static memory. For instance:

Heap Memory: Memory in the heap is explicitly allocated using functions like malloc and 
free and has to be managed manually.
Static Memory: If a were declared with the static keyword (static char a[] = "ABCDE";), it 
would be stored in the static data segment and retain its value between multiple function 
calls.
In contrast, since a is defined without static in the given function, it is stored in the 
stack, which is why its memory is automatically freed when the function exits.

A static variable in C is a variable that maintains its value for the lifetime of the 
program, even if it is defined inside a function. The static keyword can be used for both 
local and global variables, but its behavior differs slightly depending on the context. 
Let’s break down what it means for a variable to be static:

Characteristics of Static Variables
Persistence Across Function Calls:

When a static variable is declared inside a function, it is initialized only once, and it 
maintains its value between multiple function calls.
For example:
c
Copy code
void myFunction() {
    static int count = 0;  // Initialized only once
    count++;
    printf("%d\n", count);
}
Each time myFunction is called, the count variable will retain its previous value and 
increment by 1, rather than being reset to 0.
Storage in the Static Data Segment:

Static variables are stored in the static data segment (or data segment) of the memory, 
not on the stack.
This means that they have a fixed location in memory and are not created or destroyed with 
each function call, unlike automatic variables.
Default Initialization:

If not explicitly initialized, static variables are automatically set to 0 (for numerical 
variables) or NULL (for pointers).
Local Static Variables:

When a variable is declared static inside a function, its scope is still limited to that 
function, but its lifetime is extended to the entire duration of the program.
Example:
c
Copy code
void func() {
    static int x = 10;  // Visible only within func(), but retains its value across 
function calls
    printf("%d\n", x);
    x++;
}
Global Static Variables:

When the static keyword is used with a global variable, the variable’s scope is limited to 
the file in which it is defined.
It has internal linkage, meaning it cannot be accessed from other files (translation 
units), even though its lifetime is the entire program.
Example:
c
Copy code
static int globalVar = 100;  // Accessible only within this file
Why Use Static Variables?
Preserve State Across Function Calls:

Useful in scenarios where you want to keep track of values or states without using global 
variables.
Encapsulation:

For global static variables, it limits the visibility to the file, helping to prevent 
unwanted access or modification from other parts of the program.
Avoid Re-initialization:

Static variables inside a function are initialized only once. This reduces overhead and 
ensures that the variable’s state persists across function calls.

global static variables must be declared outside the function, you can not declare it 
inside a function 

so basically if I make a variable static within a function, then every time I call the 
function it will remember the value but if I dont say static then it will not have the 
value once the function finishes. but lets say I declare a static variable in a function, 
I need to use a accessor function to get the value and use it somehwere else. 

Static Variables Within a Function
When you declare a variable as static inside a function, it behaves differently from a 
regular local variable in the following ways:

Persistence Across Function Calls:

A static variable inside a function retains its value between multiple calls to that 
function.

For example:

c
Copy code
#include <stdio.h>

void incrementCounter() {
    static int counter = 0;  // Static variable retains its value across calls
    counter++;
    printf("Counter: %d\n", counter);
}

int main() {
    incrementCounter();  // Output: Counter: 1
    incrementCounter();  // Output: Counter: 2
    incrementCounter();  // Output: Counter: 3
    return 0;
}
Each time you call incrementCounter(), the static variable counter retains its value and 
increments by 1. This is because static ensures the variable's value persists across 
function calls.

Local Scope:

Even though the variable’s lifetime persists for the entire duration of the program, it 
remains local to the function where it was defined.
This means you cannot access the static variable directly from outside that function.
Default Initialization:

Static variables are initialized to 0 by default if you do not explicitly assign a value.
Regular Local Variables
In contrast, a regular local variable (without static) inside a function is created and 
destroyed every time the function is called:

Each function call reinitializes the variable, and the old value is lost when the function 
ends.

For example:

c
Copy code
#include <stdio.h>

void incrementCounter() {
    int counter = 0;  // Regular local variable, reinitialized every time
    counter++;
    printf("Counter: %d\n", counter);
}

int main() {
    incrementCounter();  // Output: Counter: 1
    incrementCounter();  // Output: Counter: 1
    incrementCounter();  // Output: Counter: 1
    return 0;
}
Each time incrementCounter() is called, the counter variable starts at 0 because it is a 
regular local variable, and the value does not persist between function calls.

Using Accessor Functions to Access a Static Variable
Since a static variable inside a function is not visible outside that function, you need a 
getter (accessor) function to access it or a setter function to modify it from other parts 
of your code. This technique allows you to encapsulate the static variable's access and 
control its visibility.

Example: Accessing a Static Variable Using an Accessor Function
Here’s a practical example:

c
Copy code
#include <stdio.h>

// Function with a static variable
void updateCounter() {
    static int counter = 0;  // Static variable, local to updateCounter()
    counter++;
    printf("Counter inside updateCounter(): %d\n", counter);
}

// Getter function to access the value of the static variable indirectly
int getCounterValue() {
    static int counter = 0;  // This variable retains its value 
    returing



f you have a global static variable and you modify it within a function, other functions 
in the same file can access and use the updated value.

*/

// MULTI DIMENSIONAL ARRAYS

/*

char multi [5][10] = an array named multi with 5 elements, where each element is array of 
10 characters

multi[0] = {'0','1','2','3','4','5','6','7','8','9'}
multi[1] = {'a','b','c','d','e','f','g','h','i','j'}
multi[2] = {'A','B','C','D','E','F','G','H','I','J'}
multi[3] = {'9','8','7','6','5','4','3','2','1','0'}
multi[4] = {'J','I','H','G','F','E','D','C','B','A'}

note: multi [0] = "0123456789" -> this is not true because if it was it would be a string, 
and you would need /0 which would mean you would need 11 characters 

multi + 1 is would take you to a, because the compiler knows its 10 collumns long so +1 
would take you to a, +2 would take you to A, +3 would take you to 0. the formula is 
10*sizeof(char) = 10*1 = 10, if it would be int, it would be 10*sizeofint = 10*2=20

to get to the second element in the 4th row you would do in pointer notation 
*(*(multi+3)+1) --- A same as *(*(multi + row) + col)


multi itself is a pointer to multi[0] which is an arryay of 10 elements (first row)
so to get multi[0][0] you would need to dereference this

to explain A now:

*(multi+3) = gives you the 3rd row, then you derfernence it to get multi[3][0] address, 
then add 1 which moves to next address, then derefernce this to get value

*(multi+3) is same as &multi[3][0]

*/

int main () {

int tmp [5][10];

//assign value
for(int i=0;i<5;i++){

for (int j=0;j<10;j++){

*(*(tmp+i)+j)=i*j;

}

}

// print value

for(int i=0;i<5;i++){

for (int j=0;j<10;j++){

  printf("%d",tmp[i][j]);

}

printf("\n");

}


printf("%d",tmp[0][0]);

tmp[0][0]=10;

printf("%d", *(*(tmp+1)));

}
