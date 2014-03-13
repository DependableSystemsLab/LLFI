#include <stdio.h>
#include <string.h>
#include <stdlib.h>



    void  PrintHello(void)
  {  
     printf("Hello World! ");
  }

        void  PrintBye(void)
         {  
          printf("bye World! ");
          }

            int sum (int a,int b)
             {
              int d= a+b;
             // printf("sum returns: %d\n",d);
		return d;
             }


          int main ()
        {
           PrintHello() ;  
            sum(10,20);
                 PrintBye();


       return;
  }
