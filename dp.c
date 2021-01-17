#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dp.h"
#include "tree.h"

void print_bt_level_order(BTNode    *root, int level );
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
    return a;
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

/*  lcs: Longest common subseauence */
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
    //print_bt_level_order(root);
}
/*  April 2019 
    optimal Binary Search Tree  */

void test_obst()
{
    int ar[] = {10, 12, 16, 21};
    int freq[] = {4,2,6,3};
    int len = sizeof(ar)/sizeof(int);

    obst_new(ar, freq, len);
 
}
/*  optimal Binary Search Tree */
void obst_new(int *keys, int   *freq, int count)
{
    int i , j, l, tmp, k; 
    int len = count;
    int lcost, rcost, fsum;
    obst_node    r[4][4] = {0} ; // r denotes the root for tree of i to j keys
    if (NULL == keys || NULL == freq || count == 0) {
        printf("no information\n");
        return ;
    }
    for ( i=0; i < count; i++) {
        r[i][i].root_index = i;
        r[i][i].cost = freq[i];
    }
    for ( len=2;len <= count; len++) {  // how many nodes to consider
        for ( i = 0; i+len<=count; i++) {   // From which position to consider
            fsum = 0;
            for ( k = i; k < i+len; k++) fsum+=freq[k];
            for ( j = i; j < i+len; j++) { // which node is root
                lcost = rcost  = 0;
                if ( j-1 >= 0) { lcost = r[i][j-1].cost;}
                if (j+1 < i+len) { rcost = r[j+1][i+len-1].cost;}
                tmp = lcost+rcost+fsum;
                if (r[i][i+len-1].cost == 0) {
                    r[i][i+len-1].cost = tmp;
                    r[i][i+len-1].root_index = j;
                } else if ( tmp < r[i][i+len-1].cost) {
                    r[i][i+len-1].cost = tmp; 
                    r[i][i+len-1].root_index = j;
                }
            }
        }
    }
    printf("OBST cost is:%d\n", r[0][count-1].cost);
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
            test_max_money();
            break;
        case 7:
            test_obst();
            break;
        case 8:
            test_knapsack01(5);
            break;
        case 9:
            test_subset_sum(atoi(argv[0]));
            break;
        case 10:
            test_pp(argv[0]);
            break;
        case 11:
            test_ww(argv[0], atoi(argv[1]));
            break;
        case 12: 
            test_steps(atoi(argv[0]));
        case 13: 
            test_binary_parenthisation(argv[0], atoi(argv[1]));
            break;
        case 14: 
            printf(" LIS length :%d\n", test_longest_inc_sub());
        case 15: 
            test_box_stack();
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

/*  Matric Multiplication   */
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

void test_max_money()
{
    int money[] = //{5, 3, 4, 11, 2};
    {6, 7, 1, 3, 8, 2, 4};
    int houses = sizeof(money) / sizeof(int);
    int *mm = (int*)malloc(sizeof(money));
    int i = 0, best = 0;
    mm[0] = money[0];
    mm[1] = max(money[0], money[1]);
    for ( i = 2; i < houses; i++) {
        mm[i] = max(money[i]+mm[i-2], mm[i-1]); 
    }
    printf("Max Money :%d\n", mm[i-1]);
}
#define MAXWT   5
#define NOITEMS 3
/*  June 2019   */
int getwt(int j)
{
    return j+1;
}
void knapsack01(int* wt, int *value, int no, int maxwt)
{
    int new_val = 0;
    int i = 0, j = 0;
    // represent the max value that can be carried
    int val[NOITEMS][MAXWT] = {0 };

    // for i items and jth max wt.
    int weight[NOITEMS][MAXWT] = { 0 }; // wts for max value
    /*
       For the first item, max value that can be picked
       is value of the item. if wt of item is <= max jth weight. 
     */
    for ( j = 0; j < maxwt; j++) {
        val[0][j] = (wt[0] <= getwt(j)) ? value[0] : 0; 
        weight[0][j] = (wt[0] <= getwt(j)) ? wt[0] : 0;
    }
    for ( i = 1; i < no; i++) { // For i Items
        for ( j = 0; j < maxwt; j++) { // For jth Max weight 
            new_val = value[i];
            // At this point max wt is wt[j] 
            //   and the items available are 0->i
            if (wt[i] > getwt(j)) { // There is a fn() to derive wt from j
                // and in our case j is wt itself
                val[i][j] = val[i-1][j];
                weight[i][j] = weight[i-1][j];
            } else if (wt[i] + weight[i-1][j] <= getwt(j)) {
                val[i][j] = val[i-i][j]+value[i];
                weight[i][j] = weight[i-1][j] + wt[i];
            } else {
                if (getwt(j)-wt[i]>0)
                    new_val = value[i] + val[i][j-wt[i]];
                val[i][j] =(val[i-1][j] > new_val) ? 
                    val[i-1][j] : new_val ;
                weight[i][j] =  (val[i-1][j] > new_val) ?
                    weight[i-1][j] : wt[i] + weight[i][j-wt[i]];
            }
        }
    }
    printf("knapsack 0/1. max value:%d\n", val[i-1][j-1]);
}
void test_knapsack01(int maxwt)
{
    int wt[NOITEMS] =     { 1, 2, 3 } ;
    int values[NOITEMS] =  { 60, 100, 120 } ;
    knapsack01(wt, values, NOITEMS, maxwt);
}
#define SSSIZE 6 
#define SSSUM  9
int subset_sum(int  *set, int size, int sum)
{
    int i, j;
    int found[SSSIZE][SSSUM+1] = {0};

    // For all the elements sum of 0 is true
    for (i=0; i < size; i++) {
        found[i][0] = 1;    
    }   

    // for the first element, only column with wt == element wt is T
    for (j=1; j<=sum; j++) {
        if (set[0] == sum) return 1;
        if (j == set[0] ) found[0][j] = 1; // condition 1
    }

    for ( i=1; i < size; i++) {
        //  any item weight equals given wt, return it 
        if (set[i] == sum) return 1;
        for (j=1; j <= sum; j++) {
            found [i][j] = found[i-1][j];   // initialize to previous row
            if (set[i] == j) found[i][j] = 1;// same as condition 1
            if ((j > set[i]) && found[i-1][j-set[i]]) { 
                found[i][j] = 1;
            }
        }
    }
    return found[size-1][sum];
}
/*  June 2019   
    Find if the given set has any subset with given sum */
void test_subset_sum(int sum)
{
    int res = 0;
    int set[] = {3, 34, 4, 12, 15, 2 };
    int ssize = sizeof(set) / sizeof(int);
    res = subset_sum(set, ssize, sum);
    printf(" Subset with sum %d %s found\n", sum, res ? "": "not");
}

/*  Palindrom Partitioning. 
    Determine the minimum number of cuts required to partitin the 
    given strings in to palindrome strings
    July 2019   */

#define MINCUTS 16

bool palindrome(char    *str, int i, int j) 
{
    int tmp = 0, len = j-i+1;
    int x, y;

    if ( i == j) return 1;
    for ( x = 0; x <= j-i ; x++) {
        if (str[i+x] == str[j-x]) ;
        else return 0;
    }
    return 1;
}

/*  Minimum Cut required. Partitioning Problem  */
int pp(char *str)
{
    int length = strlen(str);
    int i, j , k, len, tmp;
    int minCuts[MINCUTS][MINCUTS] = {0};
    int palin[MINCUTS][MINCUTS] = {0};

    for ( i = 0; i < length; i++) { 
        minCuts[i][i] = 0;
        palin[i][i] = 1;
    }
    for (len = 2; len <= length; len++) {
        for ( i = 0; i < length-len+1; i++) {
            j = i+len-1;
            minCuts[i][j] = 0xFFFFFFF;
            /*  We now have a string from i - j
                if this is palindrom mincuts = 0
                else minCuts is min */
            if (palindrome(str, i, j)) {
                minCuts[i][j] = 0;
            } else {
                for ( k = i; k < j; k++) {
                    tmp = 1 + minCuts[i][k] + minCuts[k+1][j];
                    if (tmp < minCuts[i][j]) {
                        minCuts[i][j] = tmp;
                    }
                }
            }
        }
    }
    return minCuts[0][length-1];
}

void test_pp(char *str)
{
    int cuts = 0;
    cuts = pp(str);
    printf("Minimum cuts required to partition :%d\n", cuts);

}
#define WW_MINCOST 8
int parse_string(char* str, int *res) 
{
    char    *token = NULL;
    int     i = 0;

    while ((token = strsep(&str, " ")) != NULL) {
        res[i] = strlen(token);
        i++;
    }
    return i;
}
int word_wrap(char  *str, int line_width)
{
    int i, j, k, length, str_length;
    int tmp;
    int cost[WW_MINCOST][WW_MINCOST] = {0};
    int slength[WW_MINCOST][WW_MINCOST] = {0};
    int wlength[WW_MINCOST] = {3, 2, 2, 5, 0,0,0,0};
    str_length = parse_string(str, wlength);

    for ( i = 0; i < str_length; i++) { 
        cost[i][i] = ( line_width - wlength[i])  * 
                     ( line_width - wlength[i]);
        slength[i][i] = wlength[i];
    }

    for (length = 2; length <= str_length; length++) {
        for ( i = 0; i < str_length-length+1; i++) { 
            j = i+length-1;
            slength[i][j] = slength[i][j-1]+
                            slength[i+1] [j] - 
                            slength[i+1] [j-1];
            if (length ==2) slength[i][j]++;
            if (slength[i][j] <= line_width) {
                cost[i][j] =( line_width - slength[i][j]) * 
                            ( line_width - slength[i][j]);
            } else {
                cost[i][j] = 0xFFFFFFF;
                for ( k = i; k < j; k++ ) {
                    tmp = cost[i][k] + cost[k+1][j];
                    if ( tmp < cost[i][j] ) cost[i][j] = tmp;
                }
            }
        }
    }
    return cost[0][str_length-1];
}
void test_ww(char *str, int width)
{
    int cost = 0; 
    cost = word_wrap(str, width);
    printf("Minimum cost : %d\n", cost);
}
#define MAX_STEPS   10
void test_steps(int steps)
{
   int n[MAX_STEPS+1] = {0}; 
   int i = 0;

   /*   initialisation  */
   n[0] = 1;
   n[1] = 1;
   n[2] = 2;
    
   for ( i = 3; i <= steps; i ++) { 
        n[i] = n[i-1]+ n[i-2]+ n[i-3];
   }
    printf("Number of ways: %d\n", n[steps]);
}
/*  July 2019   */
#define BMAX 10
int number_of_ways(char *str, int start, int end, int val)
{
    int i, j, k, length; 
    int digit;
    int op; 
    int nw[BMAX][BMAX][2] = { 0 };
    int lt, lf, rt, rf;
    
    if (end <= start) {
       return 0; 
    }
    for ( i = start; i < end; i++ ) {
        if (str[i] == '0') { 
            digit = 0;
        } else if (str[i] == '1') {
            digit = 1;
        } else {
            digit = 0xFF;
        }
        nw[i][i][0] = digit == 0 ? 1 : 0; 
        nw[i][i][1] = digit == 1 ? 1 : 0; 
    }

    for ( length = 3; length <=end ; length+= 2) {
        for ( i = 0; i < end+1-length; i++ ) { 
            j = i+length-1; // find the value of string from i to j
            for ( k = i+1; k<j; k+=2) {
                // i pointing to first digit, k points to operators only
                lt = nw[i][k-1][1];
                lf = nw[i][k-1][0];
                rt = nw[k+1][j][1];
                rf = nw[k+1][j][0];
                if ( str[k] == '^') {
                    nw[i][j][0] = nw[i][j][0] + lf*rf + lt*rt;
                    nw[i][j][1] = nw[i][j][1] + lf*rt + lt*rf;
                } else if (str[k] == '|') {
                    nw[i][j][0] = nw[i][j][0] + lf*rf;
                    nw[i][j][1] = nw[i][j][1] + lf*rt + lt*rf + lt*rt;
                } else if (str[k] == '&') {
                    nw[i][j][0] = nw[i][j][0] + lf*rf + lt*rf + lf*rt;
                    nw[i][j][1] = nw[i][j][1] + lt*rt;
                }
            }
        }
    }
    return nw[start][end-1][val];
}
void test_binary_parenthisation(char *str, int val)
{
    int d = 0;
    d = number_of_ways(str, 0, strlen(str), val);
    printf("Number of ways to parenthise: %d\n", d);
}
#define LIS_32 32
/*  Longest Increasing subsequence  */
int test_longest_inc_sub() 
{
    //int string[] = { 50, 20, 30, 10, 24, 80};
    int string[] = {3, 4, -1, 0, 6, 2, 3}; 
    int length = sizeof(string) / sizeof(int);
    int i = 0, j = 0;
    int     len[LIS_32] = {1};
    char    seq[LIS_32] = {'0'};
    int     maxl = 1;
    if (length == 0) return 0;

    seq[j] = string[0]; 

    for ( i = 0; i < length; i++) {
        len[i] = 1;
    }

    for ( i = 1; i < length; i++) {
        for (j = i-1;  j >= 0; j--) {
            if (string[i] > string[j]) {
                len[i] = len[j] + 1;
                if (len[i] > maxl) maxl = len[i];
                break;
            }
        }
    }
    return maxl; 
}
int compare(const void* i, const void   *i1)
{
    int *b1, *b2;
    b1 = (int*)i; 
    b2 = (int*) i1;
    if (*b2 > *b1) 
        return 1;
    return 0;
}
int compare_box(const void* i, const void   *i1)
{
    dp_box *b1, *b2;
    b1 = (dp_box*)i; 
    b2 = (dp_box*) i1;
    if (b2->h> b1->h) 
        return 1;
    return 0;
}
/**/
void test_box_stack()
{
    int maxh = 0;
    int string[] = {3, 4, -1, 0, 6, 2, 3};
    int i, j;
    int total_h[LIS_32] ={0};
    int pos[LIS_32] = {0};
    int len[LIS_32] = {0};
    dp_box boxes[] = { {1,2,3}, 
                        {2, 3, 4}, 
                        { 3,2,5},
                        {1,1,1}
    };
    int length = sizeof(boxes) / sizeof(dp_box);
    qsort(boxes, length, sizeof(dp_box), compare_box );
    printf("Max height is: %d\n", boxes[0].h);

    for ( i = 0; i < length; i++) { 
        len[i] = 1;
        total_h[i] = boxes[i].h;
        pos[i] = -1;
    }
    for ( i = 1; i < length; i++) { 
        for ( j = i-1; j>=0; j--) { 
            if ( (boxes[i].l < boxes[j].l) &&
                 (boxes[i].w < boxes[j].w)) {
                len[i] = len[j]+1;
                total_h[i] = total_h[j]+boxes[i].h;
                pos[i] = j;
                break;
            } 
        }
    }
    printf("Max count: %d, max_height:%d\n", len[3], total_h[3]);
    printf("boxes are:");
    j = len[3];
    for ( i = len[3] ; (i > 0 && j != -1); i--) { 
        printf("{ %d, %d, %d}, ", boxes[j].h, boxes[j].w, boxes[j].l);
        j = pos[i];
    }
}
