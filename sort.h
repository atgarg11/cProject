#ifndef _SORT_H_
#define _SORT_H_

int* merge_sort_merge(int *one, int* two, int size1, int size2);
int* merge_sort(int *in, int size);
void test_quick_sort();
int quick_pivot(int array[], int start, int end);
void quick_sort(int array[], int start, int end);
int*    merge_merge_sort(int a1[], int a2[], int s1, int s2, int res[]);
void practise_sort(int tc, int argc, char* argv[]);

#endif
