#ifndef _DP_H_ 
#define _DP_H_ 

/*  struct to store result of mm    */
typedef struct mm_result_ {
    int i;  /*  (i,k) represent the prefix matrix   */ 
    int k;  /*  (k+1, j) represent the suffix matrix    */
    int j;
}mm_result;

typedef struct dp_box_ {
    int h;
    int w; 
    int l;
}dp_box;

void    practise_dps(int tc, int argc, char* argv[]);
void    egg_drop(int eggs, int floors);
int     mm(int rows[], int cols[], int num_matrices);
void    test_max_money();
void    test_obst();
void    obst_new(int *keys, int   *freq, int count);
void    test_knapsack01(int maxwt);
void    test_subset_sum(int sum);
void    test_pp(char *str);
int     parse_string(char* str, int *res);
void    test_ww(char *str, int width);
void    test_steps(int steps);
void    test_binary_parenthisation(char *str, int val);
int     test_longest_inc_sub();
void    test_box_stack();
#endif
