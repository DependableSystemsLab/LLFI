#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main ()
{
 //  char src[40] = "This is a fault injection experiment!! ";
 //  char dest[40]= "a memory array for memory copying!";
    

    char* src= malloc (40);
     int n, size;
     printf("Enter number of elements: ");
       scanf("%d",&n); 
       size= n*sizeof(char);
      char* dest= malloc (size);
   
   src = "This is a fault injection experiment!! ";
   printf(" memcpy src = %s\n", src);
   printf("Before memcpy dest = %s\n", dest);

int i;
for (i=0; i<=10; i++)
{
   memmove(dest, src,40);
}
   printf("After memcpy dest = %s\n", dest);
   
   return(0);
}
