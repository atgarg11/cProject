#ifndef _SORT_H_
#define _SORT_H_

class Interval {
    public:
    int start, end;
    Interval(int i, int j) {
        start = i;
        end = j;
    }
    static void swap(Interval& x, Interval& y) {
        int tmp = x.start;
        x.start = y.start;
        y.start = tmp;
        tmp = x.end;
        x.end = y.end;
        y.end = tmp;
    }
};

int* merge_sort_merge(int *one, int* two, int size1, int size2);
int* merge_sort(int *in, int size);
void test_quick_sort();
int quick_pivot(int array[], int start, int end);
void quick_sort(int array[], int start, int end);
int*    merge_merge_sort(int a1[], int a2[], int s1, int s2, int res[]);
void practise_sort(int tc, int argc, char* argv[]);

int* merge_sort_merge_with_count_inversion(int *one, int* two, int size1, 
        int size2, int *ci) ;
int* merge_sort_with_ci(int *in, int size, int *ci);
#endif
