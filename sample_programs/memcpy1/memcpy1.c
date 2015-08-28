#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main ()
{
  int size=50;
  char* src= malloc (size);
  if (src==NULL)
  { 
    printf (" src can't be created;The system is ran out of memory :\n" );
    return  (0);
  }
     
  char* dest= malloc (size);
  if (dest==NULL)
  { 
    printf (" dest can't be created;The system is ran out of memory :\n" );
    return  (0);
  }
        
  FILE *fp;
  fp=fopen("sample.txt","r");
  if (fp == NULL)
  printf("ERROR!");
  fread(src,sizeof(char),size ,fp);
  fclose (fp);
    
  printf("The content of input file is:  %s\n", src);
  int i;
  memmove(dest, src,50); 
  printf("The content of buffer is: %s\n", dest);
  fp=fopen("output.txt","w");
  if (fp != NULL)
    fwrite(dest,sizeof(char),size ,fp);
  fclose (fp);
  char ch;
  fopen("output.txt","r");
  printf (" the content of OUTPUT file is :\n" );
  ch = fgetc(fp);
  while(ch != EOF)
  {
    printf("%c", ch);
    ch = fgetc(fp);
  }
  fclose (fp);
  free(src);
  free(dest);    
  return(0);
}
