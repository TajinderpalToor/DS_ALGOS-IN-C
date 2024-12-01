// method 3 - you dont know the number of elements in each row, so you dont know cols so
//they must be determined at run time - to do this create an array of pointers and then
// allocate space for these rows and then point these pointers at each row

# include <stdio.h>
# include <stdlib.h>

int main(void) {

int nrows=5;
int ncols=10;
int row;
int **rowptr;
rowptr=malloc(nrows* sizeof(int *));
  
if(rowptr==NULL) 

{

puts("\nFailure to allocate room for row pointers.\n");
exit(0);

}

printf("\n\n\nIndex Pointer(hex) Pointer(dec) Diff.(dec)");

for (row = 0; row < nrows; row++)
{
rowptr[row] = malloc(ncols * sizeof(int));
if (rowptr[row] == NULL)
{
printf("\nFailure to allocate for row[%d]\n",row);
exit(0);
}
printf("\n%d %p %d", row, rowptr[row],
rowptr[row]);
if (row > 0)
printf(" %d",(int)(rowptr[row] - rowptr[row-1]));
}
return 0;





/*


okay so basically in that original code I sent you declare a pointer to a pointer int. 
because we are doing 2d arrays this pointer to pointer means we can point to an array of 
int which will point to another array of ints. now in this code you declare the pointer to 
pointer using int **row ptr; then after making sure it is not null. then you can either do 
row ptr[row] or *(rowptr + row). when you do rowptr+row. you are getting the address of 
the row-th element,
Search instead for okay so basically in that original code I sent you declare a pointer to 
a pointer int. because we are doing 2d arrays this pointer to pointer means we can point 
to an array of int which will point to another array of ints. now in this code you declare 
the pointer to pointer using int **rowptr; then after making sure it is not null. then you 
can either do rowptr[row] or *(rowptr + row). when you do rowptr+row. you are getting the 
address of the row-th element, specifically the first element, dereferencing will give you 
the value which is equivalent to rowptr[row].  after you do malloc which will soecify how 
much memory is needed for each row. you only need to do this malloc once. now these are 
the rows of the 2d, each row points to the first element of the array in that row. for 
each row you need to declare size,so have to do malloc 5 times.

*/



}
