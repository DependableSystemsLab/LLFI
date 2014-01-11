
#include <stdlib.h>
#include <stdio.h>

int sum(int N)
{
  int i;
  int s = 0;
  for(i = 1; i <= N; ++i) {
    s += i;
  }
  return s;
}

int sum2(int N)
{
  return N*(N+1)/2;
}

int main(int argc, char **argv)
{
  if(argc == 1) {
    printf("usage: %s <int>\n", *argv);
    return 1;
  }
  int N = atoi(argv[1]);
  int gold = sum2(N);
  int s = sum(N);

  if(s != gold) {
    printf("Error: got %d expected %d\n", s, gold);
    return 2;
  }

  printf("Success: sum(%d) = %d\n", N, s);
  return 0;
}
