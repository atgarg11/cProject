#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

void practise_sort(int tc, int argc, char* argv[])
{
    switch(tc) {
        case 1:
            break;
        default: 
            break;
    };
}
int* merge_sort_merge(int *one, int* two, int size1, int size2) 
{
    int tmp[32] = {0};
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
        else { 
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
