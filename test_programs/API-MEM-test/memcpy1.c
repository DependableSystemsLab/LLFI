#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main ()
{
     
   int size=50;
    char* src= malloc (size);
       char* dest= malloc (size);
   
        FILE *fp;
         fp=fopen("sample.txt","r");
	  if (fp == NULL)
	   printf("ERROR!");
            fread(src,sizeof(char),size ,fp);
              fclose (fp);
    
          printf("The content of input file is:  %s\n", src);

             int i;
             // for (i=0; i<=10; i++)
                memmove(dest, src,50); 
                  printf("The content of buffer is: %s\n", dest);
                   fp=fopen("output.txt","w");
	             if (fp != NULL)
		       fwrite(dest,sizeof(char),size ,fp);
                         fclose (fp);

                          char ch;
                          fopen("output.txt","r");
                             printf (" the content of file are :\n" );
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
