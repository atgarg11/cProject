#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sort.h"
#include "util.h"
#include <vector> 
#include <iostream>

using namespace std;

void test_merge_sort()
{
    int arr[] = {3,5, 1, 6, 2, 4};
    print_array(arr, sizeof(arr)/sizeof(int));
    merge_sort(arr, sizeof(arr)/sizeof(int));
    print_array(arr, sizeof(arr)/sizeof(int));
}
void test_count_inversion()
{
    int arr[] = { 1, 20, 6, 4, 5 }; //{3,5, 1, 6, 2, 4};
    int ci = 0;
    merge_sort_with_ci(arr, sizeof(arr)/sizeof(int), &ci);
    printf(" Count inversion:%d\n", ci);
}
/*  Oct 2019 */
int partition(vector<Interval>& input, int start, int end) 
{
    int pivot = input[end].start; 
    int i, j, k;
    i = start-1; j = start-1, k = start;
    while ( k < end) {
        if (input[k].start <= pivot) {
            i++; j++;
            Interval::swap(input[i], input[k]);  
        } else {
            j++;
        }
        k++;
    }
    Interval::swap(input[i+1], input[end]);
    return i+1;
}
void qsort(vector<Interval> & input, int x, int y)
{
    int p = 0;
    if (x >=y) return ;
    p = partition(input, x, y);
    qsort(input, x, p-1);
    qsort(input, p+1, y);
}

void merge_intervals(vector<Interval>& input) 
{
    int num = input.size();
    int i=0, j=0, p=num-1;
    qsort(input, i, p);
    for (auto interval : input) {
        cout << "[" <<interval.start << "," << interval.end<< "] ";
    }
    cout << "\n";
}
void test_intervals(int tc)
{
    vector<Interval> input = { {1,2}, {9,16}, {7,8}, {3,4}};
    for (auto interval : input) {
        cout << "[" <<interval.start << "," << interval.end<< "] ";
    }
    cout << "\n";
    switch (tc) {
        case 1: 
            merge_intervals(input);
    }
}
void practise_sort(int tc, int argc, char* argv[])
{
    switch(tc) {
        case 1:
            test_merge_sort();
            break;
        case 2:
            test_count_inversion();
            break;
        case 3:
            test_intervals(1);
            break;
       default: 
            break;
    };
}
/*  Merge two sorted arrays 
 *  one: first array, size1: size of first array
 *  two: second array, size2: size of second array
 */
int* merge_sort_merge(int *one, int* two, int size1, int size2) 
{
    int tmp[32] = {0}; // temporeary storage to save the merge operation
    int i, j , loop;
    int max = 0;

    for (i = 0, j = 0, loop = 0; loop < (size1 + size2); ) {
        if ( size1 == i) {
            max = two[j++];
        }
        else if (size2 == j) {
            max = one[i++];
        }
        else if (one[i] < two[j]) {
            max = one[i++];
        }
        else {      // count inversion leg 
            max = two[j++];
        }
        tmp[loop++] = max;
    }
    memcpy(one, tmp, (size1+size2)*sizeof(int));
    return one;
}
int* merge_sort(int *in, int size)
{
    int *first, *sec;
    int i = 0, j = 0;

    if ( 1 == size) return in;

    i = size/2;

    first = merge_sort(in,i);
    sec = merge_sort(in+i, size-i);

    return ( merge_sort_merge(first, sec, i, size-i));
}

int*    merge_merge_sort(int a1[], int a2[], int s1, int s2, int res[])
{
    return NULL;
}

int* merge_sort_merge_with_count_inversion(int *one, int* two, int size1, 
        int size2, int *ci) 
{
    int tmp[32] = {0}; // temporeary storage to save the merge operation
    int i, j , loop;// i : index in to 1st array, j in 2nd, loop in final
    int max = 0;

    for (i = 0, j = 0, loop = 0; loop < (size1 + size2); ) {
        if ( size1 == i) {
            max = two[j++];
        }
        else if (size2 == j) {
            max = one[i++];
        }
        else if (one[i] < two[j]) {
            max = one[i++];
        }
        else {      // count inversion leg 
            max = two[j++];
            *ci += size1-i;
        }
        tmp[loop++] = max;
    }
    memcpy(one, tmp, (size1+size2)*sizeof(int));
    return one;
}
int* merge_sort_with_ci(int *in, int size, int *ci)
{
    int *first, *sec;
    int i = 0, j = 0;

    if ( 1 == size) return in;

    i = size/2;

    first = merge_sort_with_ci(in,i, ci);
    sec = merge_sort_with_ci(in+i, size-i, ci);

    return ( merge_sort_merge_with_count_inversion(
                first, sec, i, size-i, ci));
}


