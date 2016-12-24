#ifndef SORTS_H
#define SORTS_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define randFill 0
#define incFill 1
#define decFill 2

void bsort(int *array, int N);
void isort(int *array, int N);
void ssort(int *array, int N);
void countsort(int *array, int N, int M);
int countselect(int *array, int N, int M, int k);
void countsort(int *array, int N, int M);
void hsort(int *array, int N);
void hsort2(int *array, int N);
int linear_search(int *array, int target, int start, int end);
int binary_search(int *array, int target, int start, int end);
int quickselect(int *array, int index, int start, int end);
void qusort(int *array, int start, int end);

#endif
