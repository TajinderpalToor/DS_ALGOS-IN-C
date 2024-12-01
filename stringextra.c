# include <stdio.h>

    char *my_strcpy(char dest[], char source[])
    {
        int i = 0;
        while (source[i] != '\0')
        {
            dest[i] = source[i]; // line 9
            i++;
        }
        dest[i] = '\0';
        return dest;
    }


/*

Line 9 = is the same as *(dest + i) = *(source + i)
also instead of while(*source[i] !='\0') is the same as just while(*source)

// the above is another way to copy the string, using array notation instead of pointers 
// source[i] would give you the same value as *(p+i)
// pointer arithmetic is the same as array indexing 

// so this is an addition function, which in c is commutateive ( so a+b is the same as b+a)
//therefore *(i+a) should be the same as *(a+i)

// but then *(i+a) could have some from i[a] so test this 

int main(){
// you will see that from the bottom the other way is gucci to so then i[a] = a[i], and *(i+a) 
// same as *(a+i)

char a[20]="00000000000000";
int i;

a[3]='x';

4[a]='y';

puts(a);



}
