// memoized fibonacci.  not thread-safe.  Pure C.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// memoized fib function, using a static int* that can be reallocated.
// Getting the indices right is playing with fire.
extern int fib (int n) {
  static int* fibt=0;
  static int tablesize = 0;
  int i;

  if (!fibt) {
// no table, so make one.
      // guarantee enough space for first two values
    tablesize = n>0 ? n+1 : 2;
    fibt=malloc(tablesize*sizeof(int));
    fibt[0]=0;
    fibt[1]=1;
    for (i=2; i<=n; i++) {
      fibt[i]=-1;
    }
  }
  else if (n+1 > tablesize) {
      int * oldt = fibt;
      fibt = realloc(fibt, (n+1)*sizeof(int));
      if (fibt == NULL) fibt = oldt;
      // ^ fixes a realloc bug caught by cppcheck, where the realloc
      // failed.  Of course in that case we can't grow the table.  For
      // code like this, I don't care, and added the check just to try
      // quieting cppcheck.
      for (i=tablesize; i<=n; i++) 
          fibt[i]=-1;
      tablesize = n+1;
  }

  if (fibt[n] == -1) fibt[n] = fib(n-1)+fib(n-2);
  return fibt[n];
}

extern int test() {
  return fib(13) == 233;
}

int recfib(int n) {
    if (n==0 || n==1) return n;
    else return recfib(n-1)+recfib(n-2);
}
