// memoized fibonacci.  not thread-safe.  Pure C.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>

/*
[Zefiris:0] ./a.out
42
C array fib 42 is 267914296
4.4e-05
vector::insert fib 42 is 267914296
6.3e-05
vector::push_back fib 42 is 267914296
2.7e-05
recursive fib 42 is 267914296
2.36759
*/

// memoized fib function, using a vector.  Either I'm doing something
// wrong or it's much slower than int*.
extern int fib_v_ins (int n) {
  static std::vector<int> fibt{0,1};
  int i;

  if (n+1 > fibt.size()) {
      int oldsize=fibt.size();
      fibt.reserve(n+1);  // doesn't make much difference
      //for (i=oldsize; i<=n; i++) 
          //fibt[i]=-1;  // doesn't change size
          //fibt.at(i)=-1; // bounds error
          //fibt.push_back(-1);  //works.  And fastest.
          ;
      fibt.insert(fibt.end(),n-oldsize+1,-1); // more C++ idiom
  }

  //printf("before rec: n %d size %d\n", n, fibt.size());
  if (fibt[n] == -1) fibt[n] = fib_v_ins(n-1)+fib_v_ins(n-2);
  return fibt[n];
}

extern int fib_v_push (int n) {
  static std::vector<int> fibt{0,1};
  int i;

  if (n+1 > fibt.size()) {
      int oldsize=fibt.size();
      fibt.reserve(n+1);
      for (i=oldsize; i<=n; i++) 
          fibt.push_back(-1);  //works
  }

  if (fibt[n] == -1) fibt[n] = fib_v_push(n-1)+fib_v_push(n-2);
  return fibt[n];
}
int recfib(int n) {
    if (n==0 || n==1) return n;
    else return recfib(n-1)+recfib(n-2);
}




extern int fib_c (int n) {
  static int* fibt=0;
  static int tablesize = 0;
  int i;

  if (!fibt) {
// no table, so make one.
      // guarantee enough space for first two values
    tablesize = n>0 ? n+1 : 2;
    fibt=(int*) malloc(tablesize*sizeof(int));
    fibt[0]=0;
    fibt[1]=1;
    for (i=2; i<=n; i++) {
      fibt[i]=-1;
    }
  }
  else if (n+1 > tablesize) {
      fibt = (int*) realloc(fibt, (n+1)*sizeof(int));
      for (i=tablesize; i<=n; i++) 
          fibt[i]=-1;
      tablesize = n+1;
  }

  if (fibt[n] == -1) fibt[n] = fib_c(n-1)+fib_c(n-2);
  return fibt[n];
}
