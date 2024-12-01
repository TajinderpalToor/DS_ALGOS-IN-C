# include <stdio.h>

int main() {
/*
In C, strings are arrays of characters,  arrays are pointers so therefore pointers and strings are similar 
we also will learn how and when pointers can and should be passed to functions

Also in C. the array of characters which is a string, it is terminated using a binary zero character (\0)



*/




char my_string[40];

my_string[0] = 'T';
my_string[1] = 'e';
my_string[2] = 'd';
my_string[3] = '\0';

// \0 is called null not NULL and the two are different 
// NULL you have to define at the top nul you dont 


//can also define like this 

//char my_string[40] = {'T', 'e', 'd', '\0',};    
//char my_string[40] = "Ted";

// when you add the double quotation marks, you dont need to add the \0 character at the end, the compiler sets aside however many long memory blocks


char strA[80] ="A string to be used for demonstration purposes";
char strB[80];

char *pA; // pointer to type character
char *pB ;// pointer to type charcte

printf("%s\n", strA);

// puts() is another way to use printf, but puts is good for printing strings char by char until the 
//null terminator is hit, prints the newline (\n) automatically, returns non negative value or eof 
//is returned

//     int puts(const char *s);  puts takes a char pointer as argument 

pA=strA;
printf("%s\n",pA);
/*
 // point pA at string A, remember the string A is the same as the first element memory 
location, kinda like arr=arr[0] are both the same, this case they are both char*, because str[0] is 
the same as str ( remember this from the array thing) 
so in the above you are copying the pointer of str, which is same as str[0] and is a char*, pointer 
to element, putting this in a char* pointer
*/

pB=strB;

putchar('\n');

/*

++x is a pre incrememnt
x++ is a post incrememnt 

so *pB++=*pA++; would first use the corrent value and do *pb=*pa, then would incrememnt both
if it was ++*pb=++*pa; then you would incrememnt first instead of using the current value 

*/

// while the character pointed by pA is not the null terminator 
while(*pA != '\0'){

*pB++=*pA++;

}

*pB='\0';
printf("%s\n", strB);

// the above is just basically a string copy function
return 0;
}
