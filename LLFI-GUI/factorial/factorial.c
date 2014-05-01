#include<stdio.h>
main(argc, argv)
int argc;
char *argv[];
{
  int i,fact, n;
  n = atoi(argv[1]);        
  fact = 1;
  for(i=1;i<=n;i++)
  {
    fact = fact * i;
  }
  printf("%d\n",fact);
}
