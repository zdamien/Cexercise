// Prompted by a sample coding exercise.  Fast array rotation.

#include <vector>
#include <cstdio>
#include <experimental/numeric>

using std::vector;

// helper for solution()
inline int rot (int i, int K, int N) {
  return (i+K) % N;
}

// O(N) time, O(N) space.
vector<int> solution(vector<int> &A, int K) {
  int N = A.size();
  vector<int> B(N);
  for (int i=0; i<N; i++) {
    B.at( rot(i, K, N) ) = A.at(i);
  }
  return B;
}

// O(N) time, O(1) space, with a bit of math to make it work  
void fastrot (vector<int> &A, int k) {
  int N = A.size();
  if (N==0) return;
  int g = std::experimental::gcd(N,k);

  for (int i=0; i<g; i++) {
    int oldtmp=A[i];
      int newtmp=0;
    for (int j=0; j<N/g; j++) {
      int next = (i+k)%N;
      newtmp = A[next];
      A[next]=oldtmp;
      oldtmp=newtmp;
      i=next;
    }
  }
}

int main() {
  vector<int> A = {3, 8, 9, 7, 6};

  //A = solution(A,6);
  fastrot(A,3);

  for (auto el : A)
    printf("%d ", el);
  printf("\n");
}
