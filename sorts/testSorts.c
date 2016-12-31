#include "sorts.h"
#include <stdio.h>

#define N 21  // num values
#define M 7 // 1+max value

int array[N];

/* utility functions */

void fill(int *array, int size, int mod, int mode) {
  //fills a test array with random or sequential numbers
  int i;
  for (i=0; i<size; i++) {
    if (mode == randFill)
      array[i]=random() % mod;
    else if (mode == incFill)
      array[i]=i%M;
    else
      array[i]=(size-i)%mod;
  }
}

int checkarray(int * array, int size) {
  // verify sortedness
  if (N<2) return 1;
  for (int i=0; i<size-1; i++) {
    if (array[i] > array[i+1])
      return 0;
  }
  return 1;
}

void parray(int * array, int size) {
  // prints an array
  int i;
  for (i=0; i<size; i++) {
    printf("%d ",array[i]);
  }
  printf("\n");
  printf("sorted: %d\n",checkarray(array, N));
}


int main() {
  int seed=time(0);
  printf("\n");
  srandom(seed);

  srandom(seed);
  fill(array, N, M, randFill);
  parray(array, N);
  bsort(array, N);
  parray(array, N);
  printf("\n");

  srandom(seed);
  fill(array, N, M, randFill);
  parray(array, N);
  isort(array, N);
  parray(array, N);
  printf("\n");

  srandom(seed);
  fill(array, N, M, randFill);
  parray(array, N);
  ssort(array, N);
  parray(array, N);
  printf("\n");

  srandom(seed);
  fill(array, N, M, randFill);
  parray(array, N);
  hsort(array, N);
  parray(array, N);
  printf("\n");

  srandom(seed);
  fill(array, N, M, randFill);
  parray(array, N);
  hsort2(array, N);
  parray(array, N);
  printf("\n");


  srandom(seed);
  fill(array, N, M, randFill);
  parray(array, N);
  countsort(array, N, M);
  parray(array, N);
  printf("\n");


  srandom(seed);
  fill(array, N, M, randFill);
  parray(array, N);
  qusort(array, 0, N-1);
  parray(array, N);
  printf("\n");

  srandom(seed);
  fill(array, N, M, randFill);
  parray(array, N);
  printf("count median value is %d\n", countselect(array, N, M, N/2+1));
  printf("quick median value is %d\n",quickselect(array, N/2, 0, N-1));
  printf("\n");

  seed = 1;
  srandom(seed);
  fill(array, N, M, randFill);
  parray(array, N);
  printf("searching for 6...\n");
  printf("linear search gives %d\n",linear_search(array, 6, 0, N-1));
  qusort(array, 0, N-1);
  parray(array, N);
  printf("linear search gives %d\n",linear_search(array, 6, 0, N-1));
  printf("binary search gives %d\n",binary_search(array, 6, 0, N-1));
}
