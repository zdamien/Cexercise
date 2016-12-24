/* practice implementation of various sorting algorithms, with O(n)
 counting code */

#include "sorts.h"

#include <limits.h>

#define SWAP(A,B) { int tmp; tmp=(A); (A)=(B); (B)=tmp; }

void bsort(int *array, int N) { 
  //bubble
  int i, j;
  for (i=0; i<N; i++) {
    for (j=i+1; j<N; j++) {
      if (array[j] < array[i]) {
        SWAP(array[i], array[j]);
      }
    }
  }
}


void isort(int *array, int N) { // insertion
  int i, j, tmp, unsorted_start=0;
  for (unsorted_start=1; unsorted_start<N; unsorted_start++) {
    tmp = array[unsorted_start];
    for (i=unsorted_start-1; array[i] > tmp; i--) {
    // go back through sorted elements until one is < tmp
      ;
    }
    i++; // we want to insert *after* that one

    // shuffle elements to the right
    if (i != unsorted_start) { // if == no need to do anything
      for (j=unsorted_start; j>i; j--) { 
        array[j] = array[j-1];
      }
      // finally insert the element in its place
      array[i]=tmp;
    }
  }
}

void ssort(int *array, int N) {  
  //selection: find minimum on each pass, insert it
  int i, insert=0; // loop counter, insertion point
  int mindex = -1; // index of the minimum
  for (insert=0; insert < N-1; insert++) { 
    // array=[0,N-1], inser=[0,N-2] no need to do the last element
    int min=INT_MAX;
    for (i=insert; i<N; i++) { // find next minimum
      if (array[i] < min) {
        min = array[i];
        mindex = i;
      }
    }
    if (mindex != insert) {
      array[mindex] = array[insert];
      array[insert] = min;
    }
  }
}

void countsort(int *array, int N, int M) { 
  int i, j;
  int buckets[M];
  // init buckets
  for (i=0; i<M; i++) {
    buckets[i] = 0;
  }

  //build histogram while clearing data array
  for (i=0; i<N; i++) {
    buckets[array[i]]++;
    array[i]=0;
  }

  //repopulate array from histogram
  // i loops over buckets, j over array
  j=0;
  for (i=0; i<M; i++) {
    while (buckets[i]--) {
      array[j++]=i;
    }
  }
}

int countselect(int *array, int N, int M, int k) {
  // k=desired index, e.g. that of the median
  if (N<1)
    return -1;
  int i;

  //init buckets
  int buckets[M];
  for (i=0; i<M; i++) {
    buckets[i] = 0;
  }

  //build historgram
  for (i=0; i<N; i++) {
    buckets[array[i]]++;
  }

  int j=0;
  for (i=0; i<M; i++) {
    j+=buckets[i];
    if (j >= k) {
      return i;
    }
  }
  return i;
}


// max heap stuff
// if node is n, children are at 2n+1 and 2n+2
// if node is n, parent is (n-1)/2

void siftDown(int *array, int start, int end) {
  //sifts a value down into a max heap
  //end is last element of array, not one beyond it

  // indices
  int child, swap, tmp; 
  int root=start;

  while (root*2+1 <= end) { // while root has at least one child
    child = root*2+1;
    swap=root;
    if (array[swap] < array[child])
      swap = child;
    if (child+1 <= end && array[swap] < array[child+1])
      swap=child+1;
    if (swap == root)
      return;
    else {
      SWAP(array[root], array[swap]);
      root=swap;
    }
  }
}

void make_max_heap(int * array, int count) {
  // heapify an array the O(N) way, by starting at the bottom, sifting
  // down, then moving up and repeating.  1*N/2+2*N/4+4*N/8... steps

  int start = ((count-2)/2);
  // e.g. count = 8, array=[0,7], start=3 with children 7 and (not
  // really) 8
  while (start >= 0) {
    siftDown(array, start, count-1);
    start--;
  }
}

void hsort(int *array, int N) { //heap
  // code inlined for complexity counting
  int insert, end;

  make_max_heap(array, N);

  for (insert=0, end=N-1; insert<N; insert++) {
    SWAP(array[end], array[0]); // move max value to end
    end--;  //remove end from heap consideration
    siftDown(array,0,end); //fix heap
  }
}


void siftUp(int * array, int root, int child) {
  // adding child element to an existing heap
  // compare end element to parent, if greater move it up, repeat
  int parent, tmp;

  while (child > root) { // *index* comparison
    parent = (child-1)/2;
    if (array[parent] < array[child]) {
      SWAP(array[parent], array[child]);
      child = parent;
    }
    else return; //heap condition met: array[parent] >= array[child]
  }
}

void maxheapify(int* array, int n) {
  // turn an array into a max heap, by calling siftUp on the first i
  // elements as i increases
  int end=0;
  while (end<n) {
    siftUp(array, 0, end++);
  }
}

void sdown(int * array, int root, int end) {
  // older version of siftDown
  // root has been filled with a leaf element after selection, push down
  // pushing up the greatest child, of course
  int lchild, rchild; 
  int tmp;

  while (end >= root*2+1) { // while root has at least one child
    lchild = root*2 +1;
    rchild = root*2 +2;
    if (rchild>end) rchild=end; // make sure not to exceed array

    if (array[root] < array[lchild] && array[lchild] > array[rchild]) {
      SWAP(array[root], array[lchild]);
      root = lchild;
    }
    else if (array[root] < array[rchild]) {
      SWAP(array[root], array[rchild]);
      root = rchild;
    }
    else break; //heap condition met
  }
}

void hsort2(int *array, int N) { //heap
  //slower heap sort
  maxheapify(array,N);
  
  int max, end, tmp;
  end = N-1;

  while (end>0) {
    SWAP(array[end], array[0]);
    end--;
    sdown(array,0, end);  //find next biggest element
  }
}

//end heap


int partition(int *array, int pivot, int start, int end) {
  int i, tmp, storage=start;

  if (start > end) return -1;

  SWAP(array[pivot], array[end]);

  for (i=start; i<end; i++) {
    if (array[i] < array[end]) {
      if (i == storage) storage++;
      else {
        SWAP(array[storage], array[i]);
        storage++;
      }
    }
  }
  SWAP(array[storage], array[end]);
  return storage;
}

int linear_search(int *array, int target, int start, int end) {
  int i;
  for (i=start; i<end; i++) {
    if (target == array[i])
      return i;
  }
  return -1;
}

int binary_search(int *array, int target, int start, int end) {
  //returns index of leftmost location of target, or where target could
  //be inserted if not present
  int mid;

  if (start >= end) return start;

  mid = (start + end) / 2;

  if (array[mid] < target) {
    binary_search(array, target, mid+1, end);
  }
  else {
    binary_search(array, target, start, mid);
  }
}

int quickselect(int *array, int index, int start, int end) {
  int med, pivot;

  if (start > end)
    return -1;
  pivot=partition(array, index, start, end);
  if (pivot<index) {
    return quickselect(array, index, pivot+1, end);
  }
  else if (pivot>index) {
    return quickselect(array, index, start, pivot);
  }
  else return array[pivot];
}

void qusort(int *array, int start, int end) {
  int med, k;

  if (start<end) {
    med = (start+end)/2;
    k=partition(array, med, start, end);
    qusort(array, k+1, end);
    qusort(array, start, k);
  }
}


