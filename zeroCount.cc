// sample coding problem.  count largest span of zeros, between two
// ones, in the binary representation of a number.  So zeroCount(1001)
// is 2 but zeroCount(1000) is 0

#include <cstdio>

unsigned int zeroCount (unsigned int n) {
  int zc=0;
  int max_zc=0;
  bool no_ones = true;
  while (n>0) {
//    printf(" %d %d %d\n",n, n&1, zc);
    if ((n&1) == 0) {
      if (no_ones)
        ;
      else 
        zc++;
    }
    else {
      no_ones = false;
      if (zc > max_zc)
        max_zc = zc;
      zc = 0;
    }
    n >>= 1;
 //   printf(" %d %d %d\n",n, n&1, zc);
  }
  return max_zc;
}

int main() {
  printf("%d\n", zeroCount(0));
  printf("%d\n", zeroCount(7));
  printf("%d\n", zeroCount(2));
  printf("%d\n", zeroCount(4));
  printf("%d\n", zeroCount(5));
  printf("%d\n", zeroCount(9));
  printf("%d\n", zeroCount(8));
  printf("%d\n", zeroCount(529));
  printf("%d\n", zeroCount(20));
}
