#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ds.h"

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
            break;
        case 5: 
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
