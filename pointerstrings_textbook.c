#include <stdio.h>

int main() {
    /*
    In C, strings are arrays of characters. Arrays are pointers, so pointers and strings are similar.
    */

    char my_string[40];

    my_string[0] = 'T';
    my_string[1] = 'e';
    my_string[2] = 'd';
    my_string[3] = '\0';

    char strA[80] = "A string to be used for demonstration purposes";
    char strB[80]= "12345678901234567890123456789012345678901234567890";


    char *pA;  // Pointer to character type
    char *pB;  // Pointer to character type

    // Set pointers
    pA = strA;  // Point pA to the start of strA
    pB = strB;  // Point pB to the start of strB

    // Print the addresses of strA, pA, and strB
    printf("Address of strA: %p\n", (void*)strA);
    printf("Address of pA  : %p\n", (void*)pA);
    printf("Address of strB: %p\n", (void*)strB);
    printf("Address of pB  : %p\n", (void*)pB);
    



    // Print the contents of strA and pA
    puts(strA);
    puts(pA);

    putchar('\n');

    // Copy characters from strA to strB using pointers
    while (*pA != '\0') {
	printf("StrB before copy :");
	puts(strB);
	putchar('\n');
        *pB++ = *pA++;
	printf("strB after copy :");
	puts(strB);
    }
    *pB = '\0';  // Add null terminator at the end of strB

    // Print the contents of strB
    puts(strB);

    // Print the addresses of pointers after the copy
    printf("Address of pA after copy: %p\n", (void*)pA);
    printf("Address of pB after copy: %p\n", (void*)pB);

    return 0;  // Return 0 to indicate successful execution
}
/*
basically pa points to the first element then you assign this to the first element of pB, then 
you incrememnt both when you incrememnt, you are doing pA+1 which is the same as pA+1(1 byte for 
char) this now points to the second element in the string, and you do this till you traverse the 
string til you hit the null terminator, doing *pA will give you the value known as dereferencing
