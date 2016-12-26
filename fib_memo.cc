// memoized fibonacci.  not thread-safe.  Pure C.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>

/*
[Zefiris:0] ./a.out
100
C array fib 100 is 3736710778780434371
5.5e-05
vector::resize fib 100 is 3736710778780434371
7.2e-05
vector::insert fib 100 is 3736710778780434371
1.9e-05
vector::push_back fib 100 is 3736710778780434371
3.5e-05
*/

typedef unsigned long long ull;

// memoized fib function, using a vector.  Either I'm doing something
// wrong or it's much slower than int*.
// note: rather simpler code than the C-array version fib_c.
extern ull fib_v_res (ull n) {
  static std::vector<ull> fibt{0,1};
  int i;

  if (n+1 > fibt.size()) {
      int oldsize=fibt.size();
      fibt.resize(n+1,-1);
  }

  //printf("before rec: n %d size %d\n", n, fibt.size());
  if (fibt[n] == -1) fibt[n] = fib_v_res(n-1)+fib_v_res(n-2);
  return fibt[n];
}
extern ull fib_v_ins (ull n) {
  static std::vector<ull> fibt{0,1};
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

extern ull fib_v_push (ull n) {
  static std::vector<ull> fibt{0,1};
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

int recfib(ull n) {
    if (n==0 || n==1) return n;
    else return recfib(n-1)+recfib(n-2);
}




extern ull fib_c (ull n) {
  static ull* fibt=0;
  static ull tablesize = 0;
  int i;

  if (!fibt) {
// no table, so make one.
      // guarantee enough space for first two values
    tablesize = n>0 ? n+1 : 2;
    fibt=(ull*) malloc(tablesize*sizeof(ull));
    fibt[0]=0;
    fibt[1]=1;
    for (i=2; i<=n; i++) {
      fibt[i]=-1;
    }
  }
  else if (n+1 > tablesize) {
      fibt = (ull*) realloc(fibt, (n+1)*sizeof(ull));
      for (i=tablesize; i<=n; i++) 
          fibt[i]=-1;
      tablesize = n+1;
  }

  if (fibt[n] == -1) fibt[n] = fib_c(n-1)+fib_c(n-2);
  return fibt[n];
}
