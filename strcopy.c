# include <stdio.h>

// strcopy - myversion

char *my_strcpy(char *destination, char *source){

	char *p=destination;
	while (*source != '\0'){
	  *p++=*source++;

	}
	*p='\0';
	return destination;

}

int main() {

char strA[80]= "hellohellohellohello";
char strB[80] = "emptyemptyempty";

printf("Below is the destination string before copying\n");
puts(strB);
puts("\n");

my_strcpy(strB,strA);

printf("This is the result after copying\n");
puts(strB);


return 0;

}
