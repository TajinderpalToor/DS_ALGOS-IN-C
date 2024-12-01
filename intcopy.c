# include <stdio.h>


int main() {

int arrA [] = {25,50,75,60,40};
int arrB [] = {0,0,0,0,0};

printf("Below is Array B before copying elements into it");

for ( int i=0; i<5;i++){

printf("Array[%d] = %d\n",i,arrB[i]);

}

// now copy it

//pointer to the first element of arrB
int *p = arrB;
int *pA = arrA;

int j=0;
while ( j<5){

*p++ = *pA++;
j++;

}


printf("Below is the array after copying\n");

for(int k=0;k<5;k++){

printf("Array[%d] = %d\n",k,arrB[k]);

}


return 0;

}
