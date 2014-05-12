#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void *banking(void *);

int main(){
   int accounts[2]={0,0};
   pthread_t tid1,tid2;

     if(pthread_create(&tid1,NULL,banking,(void *)accounts))
     {
         perror("pthread_create");
          return 1;
     }


     if(pthread_create(&tid2,NULL,banking,(void *)accounts))
     {
          perror("pthread_create");
           return 1;
     }
     pthread_join(tid1, NULL);
     pthread_join(tid2, NULL);//program now goes into infinite loop.
    return 0;
    }

   void *banking(void * accounts){
        int *ptr=accounts;
        int count=0;
         do{
           int temp1=ptr[0];
           int temp2=ptr[1];
           int amount=rand();
             ptr[0]=temp1-amount;
             ptr[1]=temp2+amount;
              //printf("%d \n %d\n",ptr[0],ptr[1]);
           count++;
            }while((ptr[0]+ptr[1])==0);
         printf("%d\n",count);
            //return NULL;
           exit(0);
           }
