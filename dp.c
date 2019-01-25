#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ds.h"
#include "dp.h"

void test_mm(void );
/*
   * longest common subsequnece. 
   * c[i][j]: rows = elements in a, columns = elements in b
    */
#define RMAX 10
#define MAX 3
#define MATCH 2
#define LEFT 1
#define RIGHT 0
int max(int a , int b)
{
    if (a>b) return a; 
    return b;
}
int min(int a, int b)
{
    if (a>b) return b; 
    return b;
}
int pm( const char *a, int size_a, const char* b, int size_b)
{
    int i = size_a-1 , j = size_b-1;      
    static int match= 0;

    if (0 == size_a || 0 == size_b) return match;
    else if ( size_a < size_b) return 0;

    if (a[i] == b[j] ) {
        match = pm(a, size_a-1, b, size_b-1);
    } else { 
        match = pm(a, size_a-1, b, size_b);
    }
    return match;
}

int lcs( const char *a, int size_a, const char* b, int size_b)
{
    int i = size_a-1 , j = size_b-1;      
    int c[size_a][size_b] ; 
    int res[size_a][size_b];
    int left, right;

    if (0 == size_a || 0 == size_b) return 0;
    if (a[i] == b[j] ) {
        c[i][j] = 1+lcs(a, size_a-1, b, size_b-1);
        res[i][j] = MATCH;
    } else { 
        left = lcs (a, size_a-1, b, size_b);
        right = lcs (a, size_a, b, size_b-1);
        if ( left > right) {
            c[i][j] = left;
            res[i][j] = LEFT;
        } else {
            c[i][j] = right;
            res[i][j] = RIGHT;
        }
    }
    return c[i][j];
}

int lcs_dp( const char *a, int size_a, const char* b, int size_b)
{
    int i = 0, j = 0;
    int out = max(size_a, size_b);
    int c[size_a+1][size_b+1];
    int res[out+1];
   
    out = 0;
    for (i = 0 ; j < size_b+1; j++) c[i][j] = 0;
    for (j = 0 ; i < size_a+1; i++) c[i][j] = 0;

    for ( i = 1; i <= size_a; i++) { 
        for ( j = 1; j <= size_b; j++) {
            if ( a[i-1] == b[j-1] ) {
                c[i][j] = 1+ c[i-1][j-1];
                res[out++] = i-1;
            } else {
                c[i][j] = max (c[i][j-1], c[i-1][j]);
            }
        }
    }
    printf(" length of LCS:%d\n", c[size_a][size_b]);
    for ( i = 0 ; i < out; i++ ) {
        printf("%c", a[res[i]]);
    }
}

//void display_lcs(int *a, int size_a)
void test1_lcs(int argc, char* argv[])
{
    int len = 0;
    if ( 5== argc) {
        len = lcs_dp(argv[3], strlen(argv[3]), argv[4], strlen(argv[4]));
    }
    //printf("LCS length: %d\n", len);
}

void test2_pm(int argc, char* argv[])
{
    int len = 0;
    if ( 5== argc) {
        len = pm(argv[3], strlen(argv[3]), argv[4], strlen(argv[4]));
    }
    printf("pattern match: %d\n", len);
}

typedef struct obst_ {
    int root_index; 
    int cost;
}obst_node;

BTNode  *obst(void)
{
    int i = 0, j = 0, k;
    int ar[] = {10, 12, 16, 21};
    int freq[] = {4,2,6,3};
    int len = sizeof(ar)/sizeof(int);
    BTNode  *root = NULL;

    obst_node    r[len][len] ; // r denotes the root for tree of i to j keys
    for ( i = 0; i < len; i++ ) { 
        for (j= 0; j < len; j++) {
            r[i][j].root_index = 0; r[i][j].cost = 0;
        }
    }
    for ( k = 0; k < len; k++) {
        for ( i = 0, j = i+k; i < len && j < len; i++, j++) {
            if ( 0 == k) {
                r[i][j].root_index = i;
                r[i][j].cost = freq[i];
            } else {
                r[i][j].cost = r[i][j-1].cost + r[i+1][j].cost;
                if( r[i][j-1].cost < r[i+1][j].cost) {
                    r[i][j].cost += r[i][j-1].cost;
                    r[i][j].root_index = r[i+1][j].root_index;
                } else {
                    r[i][j].cost += r[i+1][j].cost;
                    r[i][j].root_index = r[i][j-1].root_index;
                } 
            }
        }
    }
    for ( i = 0 ; i < len; i ++) {
        for ( j = len-1 ; j >=i ; j--) {
            root = insert_bt_node(root, ar[r[i][j].root_index]);
        }
    }
    print_bt_level_order(root);
}
void practise_dps(int tc, int argc, char* argv[])
{
    int inar[] = {7,6,5,4,3,2,1}; 

    
    switch (tc) {
        case 1: 
            test1_lcs(argc, argv);
            break;
        case 2: 
            test2_pm(argc, argv);
            break;
        case 3: 
            obst();
            break;
        case 4: 
            test_mm();
            break;
        case 5: 
            egg_drop(atoi(argv[0]), atoi(argv[1]));
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        default :
            break;
    };
    printf("\n");
}
/*  Jan 3, 2019 Matrix M*/
#define NUMM 6
void print_matrix_order(mm_result   res[][NUMM], int start, int end)
{
    int i = start,j = end, k ;
    if (end == start || start == end-1) { 
        printf("Matrices order: (%d,%d)\n", start, end);
        return;
    }
    i = res[i][j].i;
    k = res[i][j].k;
    j = res[i][j].j;
    print_matrix_order(res, i, k); 
    print_matrix_order(res, k+1, j); 
    printf("Matrices order: (%d,%d),%d)\n", i, k, j);
}
void test_mm(void )
{
    int rows[] = {30, 35, 15, 5, 10, 20};
    int cols[] = {35, 15, 5, 10, 20, 25};
    int total = 0;
    total = mm(rows, cols, NUMM);
    printf("%s, total computations:%d\n", __FUNCTION__, total);
}

int mm(int rows[], int cols[], int num_matrices)
{
    int tmp = 0x1FFFFFFF;
    int i , j, k ;
    int b[NUMM][NUMM]; /*   minimum number of operations for i->j matrices*/ 
    mm_result o[NUMM][NUMM];
    memset(o, -1, sizeof(o));

    /*  Diagonal solution */
    for ( i = 0 ; i < num_matrices; i++) {
        b[i][i] = 0;
    }
    /*  
     First loop:    To track how much entries you want to consider 
     Second loop:   to iterate over the entries 
     third loop:    */
    for ( j = 2; j <=num_matrices ; j++) { 
        for ( i = 0; i+j <= num_matrices; i++) {
            tmp = 0x1FFFFFFF;
            for ( k = i; k < i+j-1; k++) { 
                b[i][i+j-1] = b[i][k] + b[k+1][i+j-1] + rows[i]* cols[k]* cols[i+j-1];
                if ( tmp < b[i][i+j-1] ) { 
                    b[i][i+j-1] = tmp;
                } else { 
                    tmp = b[i][i+j-1]; 
                    o[i][i+j-1].i = i;
                    o[i][i+j-1].j = i+j-1;
                    o[i][i+j-1].k = k;
                }
            }
        }
    }
    print_matrix_order(o, 0, NUMM-1);
    return b[0][NUMM-1];
}
#define EGG_MAX 10
void egg_drop(int eggs, int floors)
{
    int i, j, k;
    int tmp = 0;
    int b[EGG_MAX][EGG_MAX]; // Min no (best) drop for i eggs and k floors
    int r[EGG_MAX][EGG_MAX];
    printf("%s: no of eggs:%d, floors:%d\n", __FUNCTION__, eggs, floors);
    for ( i = 0; i < EGG_MAX; i++) {
        b[1][i] = i;
        b[i][1] = 1;
        b[0][i] = 0;
        b[i][0] = 0;
    }
    if (b[eggs][floors]) {
        printf("%s, no of trials:%d\n", __FUNCTION__, b[eggs][floors]);
        return;
    }
    for (k=2; k <=floors; k++) {
        for ( i = 2 ; i <= eggs; i++) {
            tmp = 0x1FFFFF;
            // for eggs starting from 2, try all the cobinations
            for ( j = 1; j <=k; j++) {
                b[i][k] = 1 + max(b[i-1][j-1], b[i][k-j]); 
                if (b[i][k] < tmp) {
                    tmp = b[i][k];
                    r[i][k] = j;
                } else b[i][k] = tmp;
            }
        }
    }
    printf("%s, no of trials:%d\n", __FUNCTION__, tmp);
}
