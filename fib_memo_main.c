// gcc fib_memo.c fib_memo_main.c

#include <stdio.h>
#include <time.h>
#include "fib_memo.h"

int main() {
    unsigned long long N;
    scanf("%d",&N);
  //printf("fib 13 is %d\n",fib(13));
  //for (int i=10; i > 0; i--)
    clock_t start = clock();
  for (int i=1; i <= N; i++)
      printf("fib %d is %d\n",i,fib(i));
  printf("%g\n", (1.0*clock()-start)/CLOCKS_PER_SEC);
    start = clock();
  for (int i=1; i <= N; i++)
      printf("fib %d is %d\n",i,recfib(i));
  printf("%g\n", (1.0*clock()-start)/CLOCKS_PER_SEC);
}
