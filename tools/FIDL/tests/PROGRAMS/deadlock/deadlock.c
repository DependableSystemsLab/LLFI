#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void * PrintHello(void*ptr);
void * PrintBye(void*ptr);
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;


int main()
{          
  pthread_t thread1, thread2;
  const char *message1= "Thread1";
  const char *message2= "Thread2";
  int retval1 = pthread_create(&thread1,NULL, PrintHello,(void*) message1);
                      
  int retval2 = pthread_create(&thread2,NULL, PrintBye,(void*) message2) ;
        
  printf("Thread 1 returns: %d\n",retval1);
  printf("Thread 2 returns: %d\n",retval2);
  pthread_mutex_lock( &mutex1 ); 
  pthread_join(thread1,NULL);   
                            
  pthread_join(thread2,NULL);
  exit(0);
}


void * PrintHello(void*ptr)
{
  char*message;
  message= (char*) ptr;
  printf("Hello World! I am , %s\n",message);
}

void * PrintBye(void*ptr)
{
  char*message;
  message= (char*) ptr;
  printf("Bye World! I am , %s\n",message);

}
