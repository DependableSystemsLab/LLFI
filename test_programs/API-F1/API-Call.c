#include <stdio.h>
#include <stdlib.h>
int main()
{
   char ch, file_name[25];
   FILE *fp;

   fp=fopen("sample.txt","r");

      if (fp==NULL)  {

 
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }

      printf (" the content of file are :\n" );
      ch = fgetc(fp);
      while(ch != EOF)
   {

      printf("%c", ch);
      ch = fgetc(fp);
   }
 
      fclose (fp);
      return 0;
}
