#ifndef _DP_H_ 
#define _DP_H_ 

/*  struct to store result of mm    */
typedef struct mm_result_ {
    int i;  /*  (i,k) represent the prefix matrix   */ 
    int k;  /*  (k+1, j) represent the suffix matrix    */
    int j;
}mm_result;

void egg_drop(int eggs, int floors);
#endif
