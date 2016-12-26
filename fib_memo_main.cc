// g++ fib_memo.cc fib_memo_main.cc

#include <stdio.h>
#include <time.h>
#include "fib_memo.hh"

int main() {
    int N;
    scanf("%d",&N);
    int N0=N;  // to make it easy to change the loops
    clock_t start = clock();
    for (int i=N0; i <= N; i++)
        printf("C array fib %d is %lld\n",i,fib_c(i));
    printf("%g\n", (1.0*clock()-start)/CLOCKS_PER_SEC);
    start = clock();
    for (int i=N0; i <= N; i++)
        printf("vector::resize fib %d is %lld\n",i,fib_v_res(i));
    printf("%g\n", (1.0*clock()-start)/CLOCKS_PER_SEC);
    start = clock();
    for (int i=N0; i <= N; i++)
        printf("vector::insert fib %d is %lld\n",i,fib_v_ins(i));
    printf("%g\n", (1.0*clock()-start)/CLOCKS_PER_SEC);
    start = clock();
    for (int i=N0; i <= N; i++)
        printf("vector::push_back fib %d is %lld\n",i,fib_v_push(i));
    printf("%g\n", (1.0*clock()-start)/CLOCKS_PER_SEC);

    //comment this out to try inputs larger than 40 or so; it gets slow
    start = clock();
    for (int i=N0; i <= N; i++)
        printf("recursive fib %d is %lldd\n",i,recfib(i));
    printf("%g\n", (1.0*clock()-start)/CLOCKS_PER_SEC);

}
