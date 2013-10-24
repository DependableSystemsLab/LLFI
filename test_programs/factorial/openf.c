#include <stdio.h>
#include <stdlib.h>


int main()
{
   char ch, file_name[25];
   FILE *fp;
   printf("Enter the name of file you wish to see\n");
   fgets(char *string, int length, FILE * stream));
   fp = fopen(file_name,"r"); // read mode
   if( fp == NULL )
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
   printf("The contents of %s file are :\n", file_name);
   while( ( ch = fgetc(fp) ) != EOF )
      printf("%c",ch);
   fclose(fp);
   return 0;
}
