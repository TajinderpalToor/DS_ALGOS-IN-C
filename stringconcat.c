# include <stdio.h>

//making my own version of the strcat() function, which basically takes two strings and concats 
//them into the destination string, make sure the destination string is large enough for this 



// string length

int stringLen( char* arr){

int len=0;

while (*arr !='\0'){
len++;
arr++;

}

return len;
}

int main(){


char strA[20]="hellohellohello";
char strB[50]="byebyebyebyebyebyebyebyebyebyebyebye";
printf("Length is %d\n ", stringLen(strB));
printf("Total String size is: %d\n", sizeof(strB));


// find the length of both arrays 

int len_strA=stringLen(strA);
int len_strB=stringLen(strB);

if (len_strA+len_strB <= sizeof(strB)){

char* ptrB=&strB[len_strB];
char* ptrA=strA;

while(*ptrA != '\0') {

*ptrB++= *ptrA++;

}

puts(strB);
}

else {

printf("The Concact is not possible");

}

}
